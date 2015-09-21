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

	mp_Font = New Font();
	mp_Font->Init("Fonts/Roboto.ttf");

	mp_TextBuffer = New TextBuffer();
	mp_TextBuffer->Init(mp_Font, "Hello, World!", 32, Color::White);

	DuskLog("info", "Starting Up");
	return true;
}

void TestApp::Term()
{
	DuskLog("info", "Shutting Down");

	delete mp_TextBuffer;
	delete mp_Font;

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

	ctx->Draw(mp_TextBuffer);

	//DuskLog("info", "Rendering");
}