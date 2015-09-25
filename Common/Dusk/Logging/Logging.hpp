/// \file 

#ifndef DUSK_LOGGING_LOGGING_HPP
#define DUSK_LOGGING_LOGGING_HPP

/// \cond HIDDEN

#include <Dusk/Collections/Map.hpp>
#include <Dusk/Collections/ArrayList.hpp>
#include <Dusk/Logging/LogColors.hpp>
#include <Dusk/Utility/Types.hpp>

#include <lua.hpp>
#include <chrono>

#define DUSK_LOGGING_MAX_BUFFER_SIZE 4096

#ifdef _WIN32
#define snprintf _snprintf
#endif

/// \endcond

namespace dusk
{

class ILogger;

////////////////////////////////////////////////////////////
/// \class Logging Logging.hpp <Dusk/Logging/Logging.hpp>
///
/// \brief The static Logging container
///
/// To log messages use either #DuskLog or #DuskExtLog
///
////////////////////////////////////////////////////////////
class Logging
{
public:

    ////////////////////////////////////////////////////////////
    /// \brief Initialize the Logging setup, required before any logging calls are made
    ///
    ////////////////////////////////////////////////////////////
    static void Init();

    ////////////////////////////////////////////////////////////
    /// \brief Add a logging level with an index
    ///
    /// \param index The index of the logging level
    /// \param level The name of the logging level
    ///
    /// \returns True if the level was added, false otherwise
    ///
    ////////////////////////////////////////////////////////////
    static bool AddLevel(const int& index, const string& level);

    ////////////////////////////////////////////////////////////
    /// \brief Check if a logging level exists
    ///
    /// \param level The name of the level to check
    ///
    /// \returns True if the level exists, false otherwise
    ///
    ////////////////////////////////////////////////////////////
    static inline bool HasLevel(const string& level)
    {
        return (s_Loggers.contains_key(level));
    }

    ////////////////////////////////////////////////////////////
    /// \brief Check if a logging level is shown, based on the current minimum logging level
    ///
    /// \param level The name of the level to check
    ///
    /// \returns True if the level is shown, false otherwise
    ///
    ////////////////////////////////////////////////////////////
    static inline bool IsLevelShown(const string& level)
    {
        return (s_Levels[level] >= s_CurrentLevel);
    }

    ////////////////////////////////////////////////////////////
    /// \brief Set the minimum logging level to be shown
    ///
    /// \param level The name of the level to set as the current minimum logging level
    ///
    ////////////////////////////////////////////////////////////
    static inline void SetLoggingLevel(const string& level)
    {
        s_CurrentLevel = s_Levels[level];
    }

    ////////////////////////////////////////////////////////////
    /// \brief Get the index of the current logging level
    ///
    /// \returns The index of the current logging level
    ///
    ////////////////////////////////////////////////////////////
    static inline int GetLoggingLevel()
    {
        return s_CurrentLevel;
    }

    ////////////////////////////////////////////////////////////
    /// \brief Add a new console logger for a given level
    ///
    /// \param level The name of the level to add the logger to
    ///
    /// \returns True if the logger was added, false otherwise
    ///
    ////////////////////////////////////////////////////////////
    static bool AddConsoleLogger(const string& level);

    ////////////////////////////////////////////////////////////
    /// \brief Add a new file logger for a given level
    ///
    /// \param level The name of the level to add the logger to
    /// \param filename The filename for the logger to log to
    ///
    /// \returns True if the logger was added, false otherwise
    ///
    ////////////////////////////////////////////////////////////
    static bool AddFileLogger(const string& level, const string& filename);

    ////////////////////////////////////////////////////////////
    /// \brief Set the foreground color for all console loggers in a given level
    ///        Colors will not be shown if the terminal doesn't support them
    ///
    /// \param level The name of the level to change the color for
    /// \param color The color to change the foreground to
    ///
    ////////////////////////////////////////////////////////////
    static void SetLevelForegroundColor(const string& level, const LogForegroundColor& color);

    ////////////////////////////////////////////////////////////
    /// \brief Set the background color for all console loggers in a given level
    ///        Colors will not be shown if the terminal doesn't support them
    ///
    /// \param level The name of the level to change the color for
    /// \param color The color to change the background to
    ///
    ////////////////////////////////////////////////////////////
    static void SetLevelBackgroundColor(const string& level, const LogBackgroundColor& color);

    ////////////////////////////////////////////////////////////
    /// \brief Close and remove all loggers
    ///
    ////////////////////////////////////////////////////////////
    static void CloseAllLoggers();

    ////////////////////////////////////////////////////////////
    /// \brief Log a message through all loggers for a given level
    ///        This is usually called by the DuskLog macro
    ///
    /// \param level The level to log the message to
    /// \param message The message to be logged
    /// \param file The source filename of the message
    /// \param line The source line number of the message
    ///
    ////////////////////////////////////////////////////////////
    static void Log(const string& level, const string& message, const string& file, const int& line);

    ////////////////////////////////////////////////////////////
    /// \brief Log a formatted message through all loggers for a given level. printf style
    ///        This is usually called by the DuskLog macro
    ///
    /// \param level The level to log the message to
    /// \param format The format of the message to be logged
    /// \param file The source filename of the message
    /// \param line The source line number of the message
    /// \param ... The arguments to be formatted into the log. printf style
    ///
    ////////////////////////////////////////////////////////////
    static void ExtLog(const string& level, const string& format, const string& file, const int line, ...);

private:

    static void Format(const char* level, const char* message, const char* file, const int& line);

    static void DispatchLog(const string& level);

    static std::chrono::high_resolution_clock::time_point s_StartTime;

    static char s_LogBuffer[DUSK_LOGGING_MAX_BUFFER_SIZE];

    static char s_FormatBuffer[DUSK_LOGGING_MAX_BUFFER_SIZE];

    static int s_CurrentLevel;

    static Map<string, int> s_Levels;

    static Map<string, LogForegroundColor> s_ForegroundColors;

    static Map<string, LogBackgroundColor> s_BackgroundColors;

    static Map<string, ArrayList<ILogger*>> s_Loggers;

public:

    /// \cond SCRIPTING

    static void Script_RegisterFunctions();

    static int Script_Log(lua_State* L);

    /// \endcond

}; // class Logging

////////////////////////////////////////////////////////////
/// \def DuskLog
///
/// \brief Log a message to a logging level
///
/// \param LVL The level to log to
/// \param MSG The message to log
///
////////////////////////////////////////////////////////////
#define DuskLog(LVL, MSG) \
Logging::Log(LVL, MSG, string(__FILE__), __LINE__)

////////////////////////////////////////////////////////////
/// \def DuskExtLog
///
/// \brief Log a formatted message to a logging level. printf style
///
/// \param LVL The level to log to
/// \param FMT The format of the message to log
/// \param ... The arguments to be formatted into the log. printf style
///
////////////////////////////////////////////////////////////
#define DuskExtLog(LVL, FMT, ...) \
Logging::ExtLog(LVL, FMT, string(__FILE__), __LINE__, __VA_ARGS__)

} // namespace dusk

#endif // DUSK_LOGGING_LOGGING_SYSTEM_HPP
