#include "TestApp.h"

#include <Dusk/Logging/Logging.hpp>
#include <Dusk/Scripting/ScriptHost.hpp>

using namespace dusk;

TestApp::TestApp()
{ }

bool TestApp::Init()
{
	if (!Program::Init())
	{
		DuskLog("error", "Failed to init program");
		return false;
	}

	GetScriptHost()->RunFile("Scripts/Setup");

	DuskLog("info", "Starting Up");
	return true;
}

void TestApp::Term()
{
	DuskLog("info", "Shutting Down");

	Program::Term();
}

void TestApp::Update(FrameTimeInfo& timeInfo)
{
	Program::Update(timeInfo);

	//DuskLog("info", "Updating");
}

void TestApp::Render(GraphicsContext* ctx)
{
	Program::Render(ctx);

	//DuskLog("info", "Rendering");
}