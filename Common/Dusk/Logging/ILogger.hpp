#ifndef DUSK_LOGGING_LOGGER_HPP
#define DUSK_LOGGING_LOGGER_HPP

#include <Dusk/Tracking/ITrackedObject.hpp>
#include <Dusk/Logging/LogColors.hpp>

#include <string>

using std::string;

namespace dusk
{

class ILogger :
    public ITrackedObject
{
public:

    virtual inline ~ILogger()
    { }

    virtual void Log(const string& line, const LogForegroundColor& fgColor, const LogBackgroundColor& bgColor) = 0;

}; // class Logger

} // namespace dusk

#endif // DUSK_LOGGING_LOGGER_HPP
