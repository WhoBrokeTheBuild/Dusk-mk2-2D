#include "TestApp.h"

#include <Dusk/Logging/Logging.hpp>
#include <Dusk/Scripting/ScriptHost.hpp>
#include <Dusk/Graphics/GraphicsSystem.hpp>

#include <iostream>

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

    GraphicsSystem* pGS = GetGraphicsSystem();
    pGS->SetWindowSize(640, 480);
    pGS->SetWindowTitle("Test");
    pGS->SetWindowStyle(WindowStyle::Decorated);
    pGS->ApplyWindowChanges();

    GetScriptHost()->RunFile("Content/Scripts/Setup.lua");

    m_UIManager.Init();
    m_UIManager.LoadFile("Content/Interface/EditorFrame.xml");

    DuskLog("info", "Starting Up");
    return true;
}

void TestApp::Term()
{
    DuskLog("info", "Shutting Down");
    m_UIManager.Term();

    Program::Term();
}

void TestApp::Update(FrameTimeInfo& timeInfo)
{
    Program::Update(timeInfo);
}

void TestApp::Render(GraphicsContext* ctx)
{
    Program::Render(ctx);
}