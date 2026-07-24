#include "shell.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

namespace Vibra {

void launch_interactive_shell(AcousticTransceiver& transceiver) {
    std::string line;
    std::cout << "\n🛡️ [VIBRA Acoustic Transceiver Prompt Engaged] Type 'help' to review command matrices." << std::endl;

    while (true) {
        std::cout << "vibra-cli> ";
        if (!std::getline(std::cin, line)) break;

        if (line.empty()) continue;

        // Tokenize input string fragments cleanly using standard string stream arrays
        std::stringstream ss(line);
        std::string command;
        ss >> command;

        std::vector<std::string> args;
        std::string arg;
        while (ss >> arg) {
            args.push_back(arg);
        }

        // --- COMMAND ROUTING INDEX MATRIX ---
        if (command == "exit" || command == "quit") {
            std::cout << "👋 Deactivating transceiver interfaces. System dropping offline." << std::endl;
            break;
        }
        else if (command == "help") {
            std::cout << "\n📋 Operational VIBRA Core Primitives:" << std::endl;
            std::cout << "  encode <text_payload>     - Modulates text strings into near-ultrasonic frequency matrices" << std::endl;
            std::cout << "  export  <file.vibra> <txt> - Compiles and serializes raw 16-bit PCM waves directly to disk" << std::endl;
            std::cout << "  decode  <file.vibra>       - Ingests a raw file container and applies bare-metal DFT scans" << std::endl;
            std::cout << "  kinetic <file.vibra> <txt> - Modulates bits into 50Hz square-wave solid-matter impact pulses" << std::endl;

            std::cout << "  status                    - Queries internal metrics tracking overall processed frame counts" << std::endl;
            std::cout << "  exit / quit               - Safely releases descriptors and terminates the shell context\n" << std::endl;
        }
        else if (command == "encode") {
            if (args.empty()) {
                std::cerr << "⚠️ Usage error: encode <text_payload_string>" << std::endl;
                continue;
            }

            // Re-aggregate token array back into a unified data payload text string
            std::string text_payload = args[0];
            for (size_t i = 1; i < args.size(); ++i) {
                text_payload += " " + args[i];
            }

            std::vector<AcousticSignalFrame> signal_out;
            if (transceiver.encode_text_to_signals(text_payload, signal_out)) {
                std::cout << "✓ Success: Modulated " << signal_out.size() << " data frames securely in memory." << std::endl;
                std::cout << "  Frequency spectrum range: " << signal_out[0].frequency_hz << "Hz to "
                          << signal_out[signal_out.size() - 1].frequency_hz << "Hz" << std::endl;
            }
        }
        else if (command == "export") {
            if (args.size() < 2) {
                std::cerr << "⚠️ Usage error: export <destination_path.vibra> <text_payload_to_encode>" << std::endl;
                continue;
            }
            std::string dest_path = "tests/" + args[0]; // Isolate binary outputs straight to tests/ directory

            // Extract and isolate remaining tokens for the data string payload
            std::string text_payload = args[1];
            for (size_t i = 2; i < args.size(); ++i) {
                text_payload += " " + args[i];
            }

            std::vector<AcousticSignalFrame> signal_out;
            if (transceiver.encode_text_to_signals(text_payload, signal_out)) {
                if (transceiver.export_signal_to_raw_audio(signal_out, dest_path)) {
                    std::cout << "✓ Success: Serialized signed 16-bit PCM stream to file: " << dest_path << std::endl;
                }
            }
        }
        else if (command == "decode") {
            if (args.empty()) {
                std::cerr << "⚠️ Usage error: decode <source_path.vibra>" << std::endl;
                continue;
            }
            std::string source_path = "tests/" + args[0];
            std::string recovered_text;

            std::cout << "📡 Ingesting file frames off storage. Executing Fourier transform spectrum scan..." << std::endl;
            if (transceiver.decode_raw_audio_to_text(source_path, recovered_text)) {
                std::cout << "📖 [Extracted Plaintext]: " << recovered_text << std::endl;
            } else {
                std::cerr << "❌ Extraction failure: Target container is corrupted or falls below magnitude thresholds." << std::endl;
            }
        }
        else if (command == "kinetic") {
            if (args.size() < 2) {
                std::cerr << "⚠️ Usage error: kinetic <destination_path.vibra> <text_payload_to_pulse>" << std::endl;
                continue;
            }
            std::string dest_path = "tests/" + args[0];

            // Re-aggregate token elements into a tight, unified data payload string
            std::string text_payload = args[1];
            for (size_t i = 2; i < args.size(); ++i) {
                text_payload += " " + args[i];
            }

            std::cout << "🔨 [Kinetic Core] Commencing binary Amplitude-Shift Keying bit conversion..." << std::endl;
            std::cout << "🔊 [Pulse Matrix] Generating low-frequency 50Hz mechanical square-wave rumbles..." << std::endl;
            if (transceiver.export_kinetic_pulses_to_file(text_payload, dest_path)) {
                std::cout << "✓ Success: Mapped and serialized kinetic structural impact file to: " << dest_path << std::endl;
            }
        }

        else if (command == "status") {
            std::cout << "📊 VIBRA Engine Telemetry Status:" << std::endl;
            std::cout << "  Processed Signal Frame Footprints: " << transceiver.get_total_processed_frames() << " records." << std::endl;
        }
        else {
            std::cerr << "❌ Unknown primitive: Type 'help' to review structural command arrays." << std::endl;
        }
    }
}

} // namespace Vibra
