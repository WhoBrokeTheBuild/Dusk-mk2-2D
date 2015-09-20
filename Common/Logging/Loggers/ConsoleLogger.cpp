#include "ConsoleLogger.hpp"

#include <Utility/Platform.hpp>

namespace dusk
{

void ConsoleLogger::Log(const string& line, const LogForegroundColor& fgColor, const LogBackgroundColor& bgColor)
{
#ifndef DUSK_OS_WINDOWS
    printf("\033[%dm\033[%dm", fgColor, bgColor);
#endif

    printf("%s\n", line.c_str());

#ifndef DUSK_OS_WINDOWS
    printf("\033[%dm\033[%dm", LOG_FG_DEFAULT, LOG_BG_DEFAULT);
#endif
}

} // namespace dusk
