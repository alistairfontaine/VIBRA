#include "vibra.hpp"
#include <iostream>

int main() {
    std::cout << "🧬 ======================================================== 🧬" << std::endl;
    std::cout << "🔥 VIBRA: Resilient Acoustic Signal Modulation Core Engine 🔥" << std::endl;
    std::cout << "🧬 ======================================================== 🧬" << std::endl;

    Vibra::AcousticTransceiver transceiver;
    std::string transmission_text = "PURE HARDWARE CODES NO LIBRARIES";
    std::vector<Vibra::AcousticSignalFrame> signal_container;
    std::string target_vibra_file = "tests/test_run.vibra";

    // 1. Modulate the ASCII string characters to near-ultrasonic frequencies
    std::cout << "📝 [Modulator] Converting message to acoustic frames..." << std::endl;
    if (!transceiver.encode_text_to_signals(transmission_text, signal_container)) {
        std::cerr << "❌ System Fault: Signal array modulation failed." << std::endl;
        return 1;
    }

    // 2. Serialize the frames straight into 16-bit raw mono PCM audio data blocks on disk
    std::cout << "📦 [Serializer] Emitting signed 16-bit PCM buffer blocks to: " << target_vibra_file << std::endl;
    if (!transceiver.export_signal_to_raw_audio(signal_container, target_vibra_file)) {
        std::cerr << "❌ System Fault: Binary .vibra stream write exception." << std::endl;
        return 1;
    }
    std::cout << "✓ Raw binary storage allocation successful." << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;

    // 3. Ingest and demodulate the raw binary file off your disk partition using pure DFT math loops
    std::cout << "📡 [Receiver Ingest] Reading binary file data directly off disk..." << std::endl;
    std::cout << "🔍 [Fourier Engine] Running bare-metal Discrete Fourier Transform spectral scans..." << std::endl;

    std::string extracted_text;
    if (transceiver.decode_raw_audio_to_text(target_vibra_file, extracted_text)) {
        std::cout << "\n📖 [Extracted Plaintext Payload]: " << extracted_text << std::endl;
    } else {
        std::cerr << "❌ Extraction Failure: Fourier correlation magnitude bounds fell below threshold." << std::endl;
        return 1;
    }

    std::cout << "\n🚀 [Status Update] Milestone 2 binary audio demodulation fully operational!" << std::endl;
    std::cout << "🧬 ======================================================== 🧬" << std::endl;
    return 0;
}
