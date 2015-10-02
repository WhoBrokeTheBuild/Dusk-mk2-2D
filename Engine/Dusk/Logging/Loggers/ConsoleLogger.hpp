#ifndef DUSK_LOGGING_CONSOLE_LOGGER_HPP
#define DUSK_LOGGING_CONSOLE_LOGGER_HPP

#include <Dusk/Logging/ILogger.hpp>
#include <Dusk/Utility/Types.hpp>

namespace dusk
{

class ConsoleLogger :
    public ILogger
{
public:

    inline ConsoleLogger()
    { }

    virtual ~ConsoleLogger()
    { }

    virtual inline string GetClassName() const
    {
        return "Console Logger";
    }

    virtual void Log(const string& line, const LogForegroundColor& fgColor, const LogBackgroundColor& bgColor);

}; // class ConsoleLogger

} // namespace dusk

#endif // DUSK_LOGGING_CONSOLE_LOGGER_HPP
