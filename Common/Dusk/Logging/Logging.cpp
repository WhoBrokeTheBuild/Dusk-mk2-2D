#include "Logging.hpp"

#include <Dusk/Logging/ILogger.hpp>
#include <Dusk/Logging/Loggers/ConsoleLogger.hpp>
#include <Dusk/Logging/Loggers/FileLogger.hpp>
#include <Dusk/Scripting/Scripting.hpp>
#include <Dusk/Utility/Strings.hpp>

#include <cstdarg>
#include <chrono>
using namespace std::chrono;

namespace dusk
{

std::chrono::high_resolution_clock::time_point Logging::s_StartTime;

char Logging::s_LogBuffer[DUSK_LOGGING_MAX_BUFFER_SIZE];
char Logging::s_FormatBuffer[DUSK_LOGGING_MAX_BUFFER_SIZE];

int Logging::s_CurrentLevel = 0;

Map<string, int>
Logging::s_Levels = Map<string, int>();

Map<string, LogForegroundColor>
Logging::s_ForegroundColors = Map<string, LogForegroundColor>();

Map<string, LogBackgroundColor>
Logging::s_BackgroundColors = Map<string, LogBackgroundColor>();

Map<string, ArrayList<ILogger*>>
Logging::s_Loggers = Map<string, ArrayList<ILogger*>>();

void Logging::Init()
{
	s_StartTime = high_resolution_clock::now();
}

bool Logging::AddLevel(const int& index, const string& level)
{
	if (s_Loggers.contains_key(level) || s_Levels.contains_key(level))
		return false;

	s_Loggers.add(level, ArrayList<ILogger*>());
	s_Levels.add(level, index);
	s_ForegroundColors.add(level, LOG_FG_DEFAULT);
	s_BackgroundColors.add(level, LOG_BG_DEFAULT);

	return true;
}

void Logging::CloseAllLoggers()
{
	for (auto& level : s_Loggers)
	{
		ArrayList<ILogger*>& loggers = level.second;

		for (auto logger : loggers)
			delete logger;

		loggers.clear();
	}
	s_Loggers.clear();
}

void Logging::SetLevelForegroundColor(const string& level, const LogForegroundColor& color)
{
	if (!HasLevel(level)) return;

	s_ForegroundColors[level] = color;
}

void Logging::SetLevelBackgroundColor(const string& level, const LogBackgroundColor& color)
{
	if (!HasLevel(level)) return;

	s_BackgroundColors[level] = color;
}

void Logging::Log(const string& level, const string& message, const string& file, const int& line)
{
	if (!IsLevelShown(level)) return;

	Format(level.c_str(), message.c_str(), Basename(file).c_str(), line);
	DispatchLog(level);
}

void Logging::ExtLog(const string& level, const string& format, const string& file, const int line, ...)
{
	if (!IsLevelShown(level)) return;

	va_list args;

	va_start(args, line);
	vsnprintf(s_FormatBuffer, DUSK_LOGGING_MAX_BUFFER_SIZE, format.c_str(), args);
	va_end(args);

	Format(level.c_str(), s_FormatBuffer, Basename(file).c_str(), line);
	DispatchLog(level);
}

void Logging::Format(const char* level, const char* message, const char* file, const int& line)
{
	long long ms = duration_cast<milliseconds>(high_resolution_clock::now() - s_StartTime).count();

	long long secs = ms / 1000;
	ms %= 1000;

	long long mins = secs / 60;
	secs %= 60;

	long long hrs = mins / 60;
	mins %= 60;

	snprintf(s_LogBuffer, DUSK_LOGGING_MAX_BUFFER_SIZE,
		"+%d.%d.%d.%d <%s:%d> [%s]: %s",
		hrs, mins, secs, ms,
		file, line,
		level, message);
}

void Logging::DispatchLog(const string& level)
{
	if (!HasLevel(level)) return;

	LogForegroundColor fgColor = s_ForegroundColors[level];
	LogBackgroundColor bgColor = s_BackgroundColors[level];

	ArrayList<ILogger*>& loggers = s_Loggers[level];
	for (auto logger : loggers)
	{
		if (logger == nullptr)
			continue;

		logger->Log(s_LogBuffer, fgColor, bgColor);
	}
}

bool Logging::AddConsoleLogger(const string& level)
{
	if (!s_Loggers.contains_key(level))
		return false;
	s_Loggers[level].add(New ConsoleLogger());
	return true;
}

bool Logging::AddFileLogger(const string& level, const string& filename)
{
	if (!s_Loggers.contains_key(level))
		return false;
	s_Loggers[level].add(New FileLogger(filename));
	return true;
}

void Logging::Script_RegisterFunctions()
{
	Scripting::RegisterFunction("DuskLog", &Logging::Script_Log);
	Scripting::RegisterFunction("dusk_log", &Logging::Script_Log);
}

int Logging::Script_Log(lua_State* L)
{
	lua_Debug ar;
	lua_getstack(L, 1, &ar);
	lua_getinfo(L, "nSl", &ar);

	string level = lua_tostring(L, 1);
	string message = lua_tostring(L, 2);

	Logging::Log(level.c_str(), message.c_str(), ar.source, ar.currentline);

	return 0;
}

} // namespace dusk
