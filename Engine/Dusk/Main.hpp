#ifndef DUSK_MAIN_HPP
#define DUSK_MAIN_HPP

#include <Dusk/Logging/Logging.hpp>
#include <Dusk/Tracking/MemoryTracker.hpp>
#include <Dusk/Utility/Console.hpp>
#include <Dusk/Utility/Platform.hpp>

using dusk::MemoryTracker;
using dusk::Logging;

template <class ProgramType>
int DuskMain(int argc, char* argv[])
{
    MemoryTracker::Init();
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

    ProgramType::CreateInst()->Run(argc, argv)->DestroyInst();

    Logging::CloseAllLoggers();

#ifdef DUSK_DEBUG_BUILD

    if (MemoryTracker::GetAllocationCount() > 0)
    {
        MemoryTracker::PrintAllocations();
        dusk::ConsolePause();
    }

#endif // DUSK_DEBUG_BUILD

    MemoryTracker::Term();

    return 0;
}

#endif // DUSK_MAIN_HPP