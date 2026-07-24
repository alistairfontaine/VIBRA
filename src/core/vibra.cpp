#include "vibra.hpp"
#include <fstream>
#include <iostream>
#include <cstring>
#include <cmath>

namespace Vibra {

AcousticTransceiver::AcousticTransceiver() : processed_frames_count_(0) {}

AcousticTransceiver::~AcousticTransceiver() {}

/**
 * 🔬 ALPHANUMERIC SIGNAL MODULATION ENCODER 🔬
 * Translates character strings into a sequence of packed frequency coordinate frames.
 * Uses an 18kHz floor baseline + a 20Hz step index multiplier per ASCII tracking character.
 */
bool AcousticTransceiver::encode_text_to_signals(const std::string& input_text, std::vector<AcousticSignalFrame>& out_signal) {
    if (input_text.empty()) return false;

    out_signal.clear();
    out_signal.reserve(input_text.length());

    for (char c : input_text) {
        AcousticSignalFrame frame;
        // Transform the alphanumeric byte value straight into its mathematical frequency tier
        frame.frequency_hz = BASE_FREQUENCY + (static_cast<uint8_t>(c) * FREQ_STEP);
        frame.duration_ms = TONE_DURATION_MS;
        frame.ascii_char = static_cast<uint8_t>(c);

        out_signal.push_back(frame);
    }

    processed_frames_count_ += out_signal.size();
    return true;
}

/**
 * 📡 INDUSTRIAL FREQUENCY SYMMETRIC DECODER 📡
 * Reverses the modulation math to translate acoustic frame parameters straight back into text.
 */
bool AcousticTransceiver::decode_signals_to_text(const std::vector<AcousticSignalFrame>& input_signal, std::string& out_text) {
    if (input_signal.empty()) return false;

    out_text.clear();
    out_text.reserve(input_signal.size());

    for (const auto& frame : input_signal) {
        // Reverse calculation to extract the alphanumeric state via direct subtraction
        uint32_t char_delta = frame.frequency_hz - BASE_FREQUENCY;
        char parsed_char = static_cast<char>(char_delta / FREQ_STEP);
        out_text.push_back(parsed_char);
    }

    return true;
}

/**
 * 📦 .VIBRA CONTAINER SERIALIZATION PIPELINE 📦
 * Generates raw 16-bit mono Pulse-Code Modulation (PCM) audio wave bytes from the signal frames,
 * and serializes them straight onto the host drive storage sectors under our sovereign format extension.
 */
bool AcousticTransceiver::export_signal_to_raw_audio(const std::vector<AcousticSignalFrame>& signal, const std::string& host_path) {
    if (signal.empty()) return false;

    // Enforce exclusive raw binary stream writes
    std::ofstream out_file(host_path, std::ios::binary | std::ios::out | std::ios::trunc);
    if (!out_file.is_open()) {
        std::cerr << "❌ Data Write Exception: Failed to secure file allocation descriptor locks on: " << host_path << std::endl;
        return false;
    }

    // Process every modulated frame step into an actual contiguous digital audio wave block
    for (const auto& frame : signal) {
        // Calculate the total counts of 16-bit audio sample blocks needed for this duration segment
        size_t total_samples = (SAMPLE_RATE * frame.duration_ms) / 1000;

        for (size_t i = 0; i < total_samples; ++i) {
            // Generate standard sinusoidal waveform wave loops using pure bedrock math
            double time_t = static_cast<double>(i) / SAMPLE_RATE;
            double angle_omega = 2.0 * M_PI * frame.frequency_hz * time_t;

            // Map the float wave amplitude safely onto signed 16-bit integer boundaries (Max: 32767)
            int16_t signed_16bit_pcm_sample = static_cast<int16_t>(std::sin(angle_omega) * 32767.0);

            out_file.write(reinterpret_cast<const char*>(&signed_16bit_pcm_sample), sizeof(int16_t));
        }
    }

    out_file.flush();
    out_file.close();
    return true;
}

/**
 * 🔒 ZERO-DEPENDENCY DISCRETE FOURIER TRANSFORM COEFFICIENT SCANNER 🔒
 * Correlates raw sample windows against targeted trigonometric sine and cosine waves.
 * Returns the raw magnitude coefficient representing spectral energy at target_freq.
 */
float AcousticTransceiver::analyze_frequency_magnitude(const std::vector<int16_t>& samples, uint32_t target_freq) const {
    double real_component = 0.0;
    double imag_component = 0.0;
    size_t N = samples.size();

    for (size_t n = 0; n < N; ++n) {
        // Compute discrete sample phase tracking angles off bedrock physics principles
        double angle_theta = 2.0 * M_PI * target_freq * static_cast<double>(n) / SAMPLE_RATE;

        double sample_val = static_cast<double>(samples[n]) / 32767.0;

        real_component += sample_val * std::cos(angle_theta);
        imag_component -= sample_val * std::sin(angle_theta);
    }

    return static_cast<float>(std::sqrt(real_component * real_component + imag_component * imag_component));
}

/**
 * 📡 BINARY AUDIO SIGNAL INGEST DEMODULATOR 📡
 * Streams a raw 16-bit mono PCM .vibra container file off your storage partition,
 * segments the raw audio samples into distinct clock tone windows, and extracts text.
 */
bool AcousticTransceiver::decode_raw_audio_to_text(const std::string& host_path, std::string& out_text) {
    std::ifstream file_in(host_path, std::ios::binary | std::ios::ate);
    if (!file_in.is_open()) {
        std::cerr << "❌ Ingest Exception: Failed to open target audio data file: " << host_path << std::endl;
        return false;
    }

    std::streamsize file_size = file_in.tellg();
    file_in.seekg(0, std::ios::beg);

    size_t total_16bit_samples = file_size / sizeof(int16_t);
    std::vector<int16_t> audio_buffer(total_16bit_samples);
    file_in.read(reinterpret_cast<char*>(audio_buffer.data()), file_size);
    file_in.close();

    out_text.clear();

    // Compute the sizing layout footprint of samples contained within a single discrete tone duration window
    size_t samples_per_tone_window = (SAMPLE_RATE * TONE_DURATION_MS) / 1000;
    size_t processed_samples_offset = 0;

    // Segment data tracks window by window across the entire audio buffer loop
    while (processed_samples_offset + samples_per_tone_window <= audio_buffer.size()) {
        std::vector<int16_t> tone_window(audio_buffer.begin() + processed_samples_offset,
                                         audio_buffer.begin() + processed_samples_offset + samples_per_tone_window);

        uint8_t best_ascii_match = 0;
        float highest_magnitude_coefficient = -1.0f;

        // 🔒 INTELLECTUAL SPEC SPECTRUM SCANNER: Evaluate every potential valid ASCII character slot
        for (uint16_t ascii_candidate = 0; ascii_candidate < 256; ++ascii_candidate) {
            uint32_t target_frequency = BASE_FREQUENCY + (ascii_candidate * FREQ_STEP);
            float magnitude = analyze_frequency_magnitude(tone_window, target_frequency);

            if (magnitude > highest_magnitude_coefficient) {
                highest_magnitude_coefficient = magnitude;
                best_ascii_match = static_cast<uint8_t>(ascii_candidate);
            }
        }

        if (highest_magnitude_coefficient > 0.1f) {
            out_text.push_back(static_cast<char>(best_ascii_match));
        }

        processed_samples_offset += samples_per_tone_window;
    }

    return !out_text.empty();
}

/**
 * 🔨 MILESTONE 4: SOLID-MATTER KINETIC IMPULSE ENGINE 🔨
 * Serializes text strings into a raw 16-bit binary BASK mechanical wave format.
 * Encodes individual bit states as high-intensity low-frequency 50Hz impact pulses.
 */
bool AcousticTransceiver::export_kinetic_pulses_to_file(const std::string& input_text, const std::string& host_path) {
    if (input_text.empty()) return false;

    std::ofstream out_file(host_path, std::ios::binary | std::ios::out | std::ios::trunc);
    if (!out_file.is_open()) {
        std::cerr << "❌ Data Write Exception: Failed to secure kinetic file allocation locks on: " << host_path << std::endl;
        return false;
    }

    // Allocate a tight 50ms duration threshold per discrete bit block window to maximize transmission speed
    size_t samples_per_bit_window = (SAMPLE_RATE * 50) / 1000;

    for (char c : input_text) {
        uint8_t byte_value = static_cast<uint8_t>(c);

        // 🔒 BIT-SLICING MATRIX: Extract all 8 structural data bits sequentially from MSB to LSB
        for (int bit_index = 7; bit_index >= 0; --bit_index) {
            bool active_bit_state = (byte_value >> bit_index) & 1;

            for (size_t i = 0; i < samples_per_bit_window; ++i) {
                int16_t raw_pcm_sample = 0;

                if (active_bit_state) {
                    // Generate a high-intensity, flat-topped square wave cycle to drive maximum kinetic rumble force
                    double time_t = static_cast<double>(i) / SAMPLE_RATE;
                    double sine_wave_reference = std::sin(2.0 * M_PI * KINETIC_FREQ_HZ * time_t);

                    // Direct mathematical threshold clamp to construct the sharp square boundaries
                    raw_pcm_sample = (sine_wave_reference >= 0.0) ? 32767 : -32767;
                } else {
                    // Emit a crisp dead interval silence window to distinguish boundaries clearly
                    raw_pcm_sample = 0;
                }

                out_file.write(reinterpret_cast<const char*>(&raw_pcm_sample), sizeof(int16_t));
            }
        }
    }

    out_file.flush();
    out_file.close();
    processed_frames_count_ += input_text.length();
    return true;
}

} // namespace Vibra


