#include "vibra.hpp"
#include "shell.hpp"
#include <iostream>

int main() {
    std::cout << "🧬 ======================================================== 🧬" << std::endl;
    std::cout << "🔥 VIBRA: Resilient Acoustic Signal Time-Slice Prompt Core 🔥" << std::endl;
    std::cout << "🧬 ======================================================== 🧬" << std::endl;

    Vibra::AcousticTransceiver transceiver;

    // Launch the interactive interpretation command loop on bare metal
    Vibra::launch_interactive_shell(transceiver);

    return 0;
}
