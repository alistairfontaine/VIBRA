#ifndef SHELL_HPP
#define SHELL_HPP

#include "vibra.hpp"

namespace Vibra {

/**
 * 💻 THE OFFICIAL INTERACTIVE TERMINAL SHELL LOOP 💻
 * Hooks directly into standard input/output streams to spin an ultra-minimalist CLI workspace.
 * Parses user command strings and maps inputs straight onto low-level transceiver methods.
 */
void launch_interactive_shell(AcousticTransceiver& transceiver);

} // namespace Vibra

#endif // SHELL_HPP
