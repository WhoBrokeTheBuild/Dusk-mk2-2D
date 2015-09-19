#ifndef DUSK_LOGGING_CONSOLE_LOGGER_HPP
#define DUSK_LOGGING_CONSOLE_LOGGER_HPP

#include <Logging/ILogger.hpp>
#include <Utility/Types.hpp>

namespace Dusk
{

class ConsoleLogger :
    public ILogger
{
public:

	inline ConsoleLogger() { }
	virtual ~ConsoleLogger() { }

	virtual inline string GetClassName() const { return "Console Logger"; }

	virtual void Log(const string& line, const LogForegroundColor& fgColor, const LogBackgroundColor& bgColor);

}; // class ConsoleLogger

} // namespace Dusk

#endif // DUSK_LOGGING_CONSOLE_LOGGER_HPP
