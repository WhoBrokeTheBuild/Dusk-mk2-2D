#ifndef LOGGING_H
#define LOGGING_H

#include <Dusk/Logging/Logging.hpp>

using dusk::Logging;

void LoggingSetup() 
{
    Logging::Init();

    Logging::AddLevel(4, "error");
    Logging::AddLevel(3, "info");
    Logging::AddLevel(2, "debug");
    Logging::AddLevel(1, "perf");
    Logging::AddLevel(0, "verbose");

    Logging::AddConsoleLogger("error");
    Logging::AddConsoleLogger("info");
    Logging::AddConsoleLogger("debug");
    Logging::AddConsoleLogger("perf");
    Logging::AddConsoleLogger("verbose");

    Logging::AddFileLogger("error", "error.log");
    Logging::AddFileLogger("error", "info.log");
    Logging::AddFileLogger("info", "info.log");
    Logging::AddFileLogger("debug", "info.log");
    Logging::AddFileLogger("perf", "info.log");
    Logging::AddFileLogger("perf", "perf.log");
    Logging::AddFileLogger("verbose", "info.log");

    Logging::SetLevelForegroundColor("error", dusk::LogForegroundColor::LOG_FG_RED);
    Logging::SetLevelForegroundColor("info", dusk::LogForegroundColor::LOG_FG_BLUE);
    Logging::SetLevelForegroundColor("debug", dusk::LogForegroundColor::LOG_FG_GREEN);
    Logging::SetLevelForegroundColor("perf", dusk::LogForegroundColor::LOG_FG_YELLOW);

    Logging::SetLoggingLevel("verbose");

    Logging::Script_RegisterFunctions();
}

#endif // LOGGING_H