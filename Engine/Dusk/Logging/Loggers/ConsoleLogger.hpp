#ifndef DUSK_LOGGING_CONSOLE_LOGGER_HPP
#define DUSK_LOGGING_CONSOLE_LOGGER_HPP

#include <Dusk/Logging/Logger.hpp>
#include <Dusk/Utility/Types.hpp>

namespace dusk
{

class ConsoleLogger :
    public Logger
{
public:

    ConsoleLogger() = default;
    ConsoleLogger(const ConsoleLogger&) = delete;
    ConsoleLogger& operator=(const ConsoleLogger&) = delete;
    virtual ~ConsoleLogger() = default;

    virtual inline string GetClassName() const override { return "Console Logger"; }

    virtual void Log(const string& line, const LogForegroundColor& fgColor, const LogBackgroundColor& bgColor);

}; // class ConsoleLogger

} // namespace dusk

#endif // DUSK_LOGGING_CONSOLE_LOGGER_HPP
