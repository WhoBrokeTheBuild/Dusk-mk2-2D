#include "LoggingSystem.hpp"

#include <Logging/ILogger.hpp>
#include <Logging/Loggers/ConsoleLogger.hpp>
#include <Logging/Loggers/FileLogger.hpp>
#include <Scripting/ScriptingSystem.hpp>
#include <Utility/Strings.hpp>

#include <cstdarg>
#include <chrono>

namespace Dusk
{

char LoggingSystem::m_LogBuffer[DUSK_LOGGING_MAX_BUFFER_SIZE];
char LoggingSystem::m_FormatBuffer[DUSK_LOGGING_MAX_BUFFER_SIZE];

int LoggingSystem::s_CurrentLevel = 0;

Map<string, int>
LoggingSystem::s_Levels = Map<string, int>();

Map<string, LogForegroundColor>
LoggingSystem::s_ForegroundColors = Map<string, LogForegroundColor>();

Map<string, LogBackgroundColor>
LoggingSystem::s_BackgroundColors = Map<string, LogBackgroundColor>();

Map<string, ArrayList<ILogger*>>
LoggingSystem::s_Loggers = Map<string, ArrayList<ILogger*>>();

bool LoggingSystem::AddLevel(const int& index, const string& level)
{
	if (s_Loggers.contains_key(level) || s_Levels.contains_key(level))
		return false;

	s_Loggers.add(level, ArrayList<ILogger*>());
	s_Levels.add(level, index);
	s_ForegroundColors.add(level, LOG_FG_DEFAULT);
	s_BackgroundColors.add(level, LOG_BG_DEFAULT);

	return true;
}

void LoggingSystem::CloseAllLoggers()
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

void LoggingSystem::SetLevelForegroundColor(const string& level, const LogForegroundColor& color)
{
	if (!HasLevel(level)) return;

	s_ForegroundColors[level] = color;
}

void LoggingSystem::SetLevelBackgroundColor(const string& level, const LogBackgroundColor& color)
{
	if (!HasLevel(level)) return;

	s_BackgroundColors[level] = color;
}

void LoggingSystem::Log(const string& level, const string& message, const string& file, const int& line)
{
	if (!IsLevelShown(level)) return;

	Format(level.c_str(), message.c_str(), Basename(file).c_str(), line);
	DispatchLog(level);
}

void LoggingSystem::ExtLog(const string& level, const string& format, const string& file, const int line, ...)
{
	if (!IsLevelShown(level)) return;

	va_list args;

	va_start(args, line);
	vsnprintf(m_FormatBuffer, DUSK_LOGGING_MAX_BUFFER_SIZE, format.c_str(), args);
	va_end(args);

	Format(level.c_str(), m_FormatBuffer, Basename(file).c_str(), line);
	DispatchLog(level);
}

void LoggingSystem::Format(const char* level, const char* message, const char* file, const int& line)
{
	snprintf(m_LogBuffer, DUSK_LOGGING_MAX_BUFFER_SIZE,
		"+%d.%d.%d.%d <%s:%d> [%s]: %s",
		0, 0, 0, 0,
		file, line,
		level, message);
}

void LoggingSystem::DispatchLog(const string& level)
{
	if (!HasLevel(level)) return;

	LogForegroundColor fgColor = s_ForegroundColors[level];
	LogBackgroundColor bgColor = s_BackgroundColors[level];

	ArrayList<ILogger*>& loggers = s_Loggers[level];
	for (auto logger : loggers)
	{
		if (logger == nullptr)
			continue;

		logger->Log(m_LogBuffer, fgColor, bgColor);
	}
}

bool LoggingSystem::AddConsoleLogger(const string& level)
{
	if (!s_Loggers.contains_key(level))
		return false;
	s_Loggers[level].add(New ConsoleLogger());
	return true;
}

bool LoggingSystem::AddFileLogger(const string& level, const string& filename)
{
	if (!s_Loggers.contains_key(level))
		return false;
	s_Loggers[level].add(New FileLogger(filename));
	return true;
}

void LoggingSystem::InitScripting()
{
	ScriptingSystem::RegisterFunction("DuskLog", &LoggingSystem::Script_Log);
}

int LoggingSystem::Script_Log(lua_State* L)
{
	lua_Debug ar;
	lua_getstack(L, 1, &ar);
	lua_getinfo(L, "nSl", &ar);

	string level = lua_tostring(L, 1);
	string message = lua_tostring(L, 2);

	LoggingSystem::Log(level.c_str(), message.c_str(), ar.source, ar.currentline);

	return 0;
}

} // namespace Dusk
