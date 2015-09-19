#ifndef DUSK_LOGGING_LOGGER_HPP
#define DUSK_LOGGING_LOGGER_HPP

#include <Tracking/ITrackedObject.hpp>
#include <Logging/LogColors.hpp>

#include <string>

using std::string;

namespace Dusk
{

class ILogger :
	public ITrackedObject
{
public:

	virtual inline ~ILogger() { }

	virtual void Log(const string& line, const LogForegroundColor& fgColor, const LogBackgroundColor& bgColor) = 0;

}; // class Logger

} // namespace Dusk

#endif // DUSK_LOGGING_LOGGER_HPP
