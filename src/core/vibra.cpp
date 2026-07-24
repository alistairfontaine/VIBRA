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

} // namespace Vibra
