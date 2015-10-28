#include "TestApp.h"

#include <Dusk/Logging/Logging.hpp>
#include <Dusk/Scripting/ScriptHost.hpp>
#include <Dusk/Graphics/GraphicsSystem.hpp>

#include <iostream>
#include "CustomRenderFrame.h"

using namespace dusk;

TestApp::TestApp() :
    Program()
{
    GraphicsSystem* pGS = GetGraphicsSystem();
    pGS->SetWindowSize(1600, 900);
    pGS->SetWindowTitle("Test");
    pGS->SetWindowStyle(GraphicsSystem::WindowStyle::Decorated);
    pGS->ApplyWindowChanges();

    GetScriptHost()->RunFile("Content/Scripts/Setup.lua");

    m_UIManager.RegisterRenderFrameType<CustomRenderFrame>("Custom");
    m_UIManager.LoadFile("Content/Interface/EditorFrame.xml");

    DuskLog("info", "Starting Up");
}

TestApp::~TestApp()
{
    DuskLog("info", "Shutting Down");
}

void TestApp::Update(FrameTimeInfo& timeInfo)
{
    Program::Update(timeInfo);
}

void TestApp::Render(GraphicsContext* ctx)
{
    Program::Render(ctx);
}