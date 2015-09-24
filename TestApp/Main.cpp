
#include <Dusk/Program.hpp>
#include <Dusk/Logging/Logging.hpp>
#include <Dusk/Scripting/Scripting.hpp>
#include <Dusk/Tracking/MemoryTracker.hpp>
#include <Dusk/Utility/Console.hpp>
#include <Dusk/Utility/Platform.hpp>

#include "Logging.h"
#include "TestApp.h"

using dusk::MemoryTracker;
using dusk::Logging;
using dusk::Program;

int main(int argc, char* argv[])
{
    MemoryTracker::Init();
    LoggingSetup();

    TestApp* app = New TestApp();
    app->Run();
    delete app;

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
