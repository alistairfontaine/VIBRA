#include "vibra.hpp"
#include <iostream>

int main() {
    std::cout << "🧬 ======================================================== 🧬" << std::endl;
    std::cout << "🔥 VIBRA: Resilient Acoustic Signal Modulation Core Engine 🔥" << std::endl;
    std::cout << "🧬 ======================================================== 🧬" << std::endl;

    Vibra::AcousticTransceiver transceiver;
    std::string transmission_text = "VIBRA Genesis Code Frame. Direct acoustic transmission achieved.";
    std::vector<Vibra::AcousticSignalFrame> signal_container;

    std::cout << "📝 [Modulation Enqueue] Translating text to near-ultrasonic coordinate matrix..." << std::endl;
    if (transceiver.encode_text_to_signals(transmission_text, signal_container)) {
        std::cout << "✓ Mapped " << transceiver.get_total_processed_frames() << " alphanumeric characters to audio frame data structures." << std::endl;

        // Serialize the wave frames to our sovereign container format
        std::string container_path = "output_pulse.vibra";
        std::cout << "📦 [Serialization] Exporting raw 16-bit PCM blocks to " << container_path << "..." << std::endl;
        if (transceiver.export_signal_to_raw_audio(signal_container, container_path)) {
            std::cout << "✓ Binary .vibra transmission data chunk file successfully written to disk!" << std::endl;
        }

        // Symmetrically reverse the math to cross-examine data integrity
        std::string recovered_plaintext;
        if (transceiver.decode_signals_to_text(signal_container, recovered_plaintext)) {
            std::cout << "📖 [Symmetric Decode Check]: " << recovered_plaintext << std::endl;
        }
    }

    std::cout << "\n🚀 [Status Update] Milestone 1 core primitives operational on your device sectors!" << std::endl;
    std::cout << "🧬 ======================================================== 🧬" << std::endl;
    return 0;
}
