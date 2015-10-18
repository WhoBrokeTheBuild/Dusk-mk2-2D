#ifndef DUSK_LOGGING_LOGGER_HPP
#define DUSK_LOGGING_LOGGER_HPP

/// \cond HIDDEN

#include <Dusk/Tracking/TrackedObject.hpp>
#include <Dusk/Logging/LogColors.hpp>

#include <string>

using std::string;

namespace dusk
{

class Logger :
    public TrackedObject
{
public:

    virtual void Log(const string& line, const LogForegroundColor& fgColor, const LogBackgroundColor& bgColor) = 0;

}; // class Logger

} // namespace dusk

/// \endcond

#endif // DUSK_LOGGING_LOGGER_HPP
