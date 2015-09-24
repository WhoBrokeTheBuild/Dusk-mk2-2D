#ifndef DUSK_UTILITY_CONSOLE_HPP
#define DUSK_UTILITY_CONSOLE_HPP

#include <iostream>
#include <string>

using std::string;

namespace dusk
{

inline void ConsolePause(const string& msg = "Press enter to continue...")
{
    std::cout << msg;
    std::cin.sync();
    std::cin.ignore();
}

} // namespace dusk

#endif // DUSK_UTILITY_CONSOLE_HPP
