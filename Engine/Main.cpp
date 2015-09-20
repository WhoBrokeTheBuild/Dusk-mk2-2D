
#include <Program.hpp>
#include <Utility/Benchmark.hpp>
#include <Scripting/ScriptingSystem.hpp>
#include <Tracking/MemoryTracker.hpp>
#include <Logging/LoggingSystem.hpp>
#include <Utility/Console.hpp>
#include <Utility/Platform.hpp>

using dusk::MemoryTracker;
using dusk::LoggingSystem;
using dusk::Program;

void initLoggingSystem() 
{
	LoggingSystem::AddLevel(4, "error");
	LoggingSystem::AddLevel(3, "info");
	LoggingSystem::AddLevel(2, "debug");
	LoggingSystem::AddLevel(1, "perf");
	LoggingSystem::AddLevel(0, "verbose");

	LoggingSystem::AddConsoleLogger("error");
	LoggingSystem::AddConsoleLogger("info");
	LoggingSystem::AddConsoleLogger("debug");
	LoggingSystem::AddConsoleLogger("perf");
	LoggingSystem::AddConsoleLogger("verbose");

	LoggingSystem::AddFileLogger("error", "error.log");
	LoggingSystem::AddFileLogger("error", "info.log");
	LoggingSystem::AddFileLogger("info", "info.log");
	LoggingSystem::AddFileLogger("debug", "info.log");
	LoggingSystem::AddFileLogger("perf", "info.log");
	LoggingSystem::AddFileLogger("perf", "perf.log");
	LoggingSystem::AddFileLogger("verbose", "info.log");

	LoggingSystem::SetLevelForegroundColor("error", dusk::LogForegroundColor::LOG_FG_RED);
	LoggingSystem::SetLevelForegroundColor("info",  dusk::LogForegroundColor::LOG_FG_BLUE);
	LoggingSystem::SetLevelForegroundColor("debug", dusk::LogForegroundColor::LOG_FG_GREEN);
	LoggingSystem::SetLevelForegroundColor("perf",  dusk::LogForegroundColor::LOG_FG_YELLOW);

	LoggingSystem::SetLoggingLevel("verbose");

	DuskLog("verbose", "Finished LoggingSystem setup");
}

int main(int argc, char* argv[])
{
	MemoryTracker::Init();

	initLoggingSystem();

	LoggingSystem::InitScripting();

	Program* pProgram = Program::Inst();

	DuskLog("verbose", "Program instance created");

    pProgram->Run();

	DuskLog("verbose", "Program has finished running");

    delete pProgram;

	DuskLog("verbose", "Program deleted, preparing to close logs");

	LoggingSystem::CloseAllLoggers();

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
