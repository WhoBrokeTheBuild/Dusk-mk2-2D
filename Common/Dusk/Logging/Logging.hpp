#ifndef DUSK_LOGGING_LOGGING_HPP
#define DUSK_LOGGING_LOGGING_HPP

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

namespace dusk
{

class ILogger;

class Logging
{
public:

	static void Init();

	static bool AddLevel(const int& index, const string& level);

	static inline bool HasLevel(const string& level)
	{
		return (s_Loggers.contains_key(level));
	}

	static inline bool IsLevelShown(const string& level)
	{
		return (s_Levels[level] >= s_CurrentLevel);
	}

	static inline void SetLoggingLevel(const string& level)
	{
		s_CurrentLevel = s_Levels[level];
	}

	static inline int GetLoggingLevel()
	{
		return s_CurrentLevel;
	}

	static bool AddConsoleLogger(const string& level);

	static bool AddFileLogger(const string& level, const string& filename);

	static void SetLevelForegroundColor(const string& level, const LogForegroundColor& color);

	static void SetLevelBackgroundColor(const string& level, const LogBackgroundColor& color);

	static void CloseAllLoggers();

	static void Log(const string& level, const string& message, const string& file, const int& line);

	static void ExtLog(const string& level, const string& format, const string& file, const int line, ...);

	static void Script_RegisterFunctions();

	static int Script_Log(lua_State* L);

private:

    static void Format( const char* level, const char* message, const char* file,  const int& line );

    static void DispatchLog( const string& level );

	static std::chrono::high_resolution_clock::time_point s_StartTime;
	
	static char s_LogBuffer[DUSK_LOGGING_MAX_BUFFER_SIZE];

	static char s_FormatBuffer[DUSK_LOGGING_MAX_BUFFER_SIZE];

    static int s_CurrentLevel;

    static Map<string, int> s_Levels;

    static Map<string, LogForegroundColor> s_ForegroundColors;

    static Map<string, LogBackgroundColor> s_BackgroundColors;

    static Map<string, ArrayList<ILogger*>> s_Loggers;

}; // class Logging

#define DuskLog( LVL, MSG ) \
Logging::Log(LVL, MSG, string(__FILE__), __LINE__)

#define DuskExtLog( LVL, FMT, ... ) \
Logging::ExtLog(LVL, FMT, string(__FILE__), __LINE__, __VA_ARGS__)

} // namespace dusk

#endif // DUSK_LOGGING_LOGGING_SYSTEM_HPP
