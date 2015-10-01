#include "Program.hpp"

#include <Dusk/Utility/Benchmark.hpp>
#include <Dusk/Logging/Logging.hpp>
#include <Dusk/Graphics/GraphicsSystem.hpp>
#include <Dusk/Graphics/GraphicsContext.hpp>
#include <Dusk/Timing/FrameTimeInfo.hpp>
#include <Dusk/Input/InputSystem.hpp>
#include <Dusk/Scripting/Scripting.hpp>
#include <Dusk/Scripting/ScriptHost.hpp>

#include <chrono>
using namespace std::chrono;

namespace dusk
{

DUSK_SINGLETON_IMPL(Program);

EventID Program::EvtUpdate = 1;
EventID Program::EvtRender = 2;
EventID Program::EvtExit = 3;

Program::Program() :
    m_Running(),
    m_TargetFPS(),
    m_CurrentFPS(),
    m_UpdateInterval(),
    mp_ScriptHost(nullptr)
{
    
}

Program* Program::Run(int argc, char* argv[])
{
    DuskLog("verbose", "Program running");

    if (!Init())
    {
        DuskLog("error", "Failed to start program");
        return sp_Inst;
    }

    FrameTimeInfo timeInfo;
    unsigned long long frameCount = 0;

    auto startTime = high_resolution_clock::now();
    auto lastTime = startTime;

    double secsSinceLastFrame = 0;

    m_Running = true;
    while (m_Running)
    {
        auto time = high_resolution_clock::now();
        auto elapsedTime = time - lastTime;
        lastTime = time;

        timeInfo.CurrentFPS = m_CurrentFPS;
        timeInfo.TargetFPS = m_TargetFPS;
        timeInfo.ElapsedSeconds = duration_cast<duration<double>>(elapsedTime).count();
        timeInfo.ElapsedMilliseconds = duration_cast<duration<double, std::milli>>(elapsedTime).count();
        timeInfo.TotalSeconds += timeInfo.ElapsedSeconds;
        timeInfo.TotalMilliseconds += timeInfo.ElapsedMilliseconds;

        timeInfo.Delta = timeInfo.ElapsedSeconds / m_UpdateInterval;

        secsSinceLastFrame += timeInfo.ElapsedSeconds;

        Update(timeInfo);

        if (secsSinceLastFrame >= m_UpdateInterval)
        {
            GraphicsContext* ctx = GraphicsSystem::Inst()->GetContext();
            PreRender(ctx);
            Render(ctx);
            PostRender(ctx);

            ++frameCount;
            m_CurrentFPS = (m_UpdateInterval / secsSinceLastFrame) * m_TargetFPS;

            secsSinceLastFrame = 0;
        }
    }

    Dispatch(Event(EvtExit));
    DuskLog("verbose", "Program Exiting");

    return sp_Inst;
}

void Program::SetTargetFPS(double fps)
{
    m_TargetFPS = fps;
    m_UpdateInterval = (1.0 / m_TargetFPS);
}

ScriptHost* Program::GetScriptHost()
{
    return mp_ScriptHost;
}

bool Program::Init()
{
    DuskLog("verbose", "Program initializing");
    DuskBenchStart();

    GraphicsSystem::CreateInst()->Init(1024, 768, "Dusk 2D", GraphicsSystem::Decorated);
    InputSystem::CreateInst()->Init();

    Script_RegisterFunctions();

    SetTargetFPS(60.0);

    mp_ScriptHost = New ScriptHost();
    mp_ScriptHost->Init();

    DuskBenchEnd("Program::Init");
    return true;
}

void Program::Term()
{
    delete mp_ScriptHost;
    mp_ScriptHost = nullptr;

    GraphicsSystem::DestroyInst();
    InputSystem::DestroyInst();
}

void Program::Update(FrameTimeInfo& timeInfo)
{
    Dispatch(Event(EvtUpdate, UpdateEventData(&timeInfo)));
}

void Program::PreRender(GraphicsContext* ctx)
{
    ctx->Clear();
}

void Program::Render(GraphicsContext* ctx)
{
    Dispatch(Event(EvtRender, RenderEventData(ctx)));
}

void Program::PostRender(GraphicsContext* ctx)
{
    ctx->SwapBuffers();
}

void Program::Script_RegisterFunctions()
{
    Scripting::RegisterFunction("dusk_get_program", &Program::Script_GetProgram);
    Scripting::RegisterFunction("dusk_program_exit", &Program::Script_Exit);

    IEventDispatcher::Script_RegisterFunctions();
    GraphicsSystem::Script_RegisterFunctions();
    InputSystem::InitScripting();
}

int Program::Script_GetProgram(lua_State* L)
{
    lua_pushinteger(L, (ptrdiff_t)Program::Inst());
    return 1;
}

int dusk::Program::Script_Exit(lua_State* L)
{
    Program* pProgram = (Program*)lua_tointeger(L, 1);
    pProgram->Exit();
    return 0;
}

FrameTimeInfo* UpdateEventData::GetTimeInfo()
{
    return mp_TimeInfo;
}

int UpdateEventData::PushDataToLua(lua_State* L) const
{
    lua_newtable(L);

    lua_pushnumber(L, mp_TimeInfo->CurrentFPS);
    lua_setfield(L, -2, "CurrentFPS");

    lua_pushnumber(L, mp_TimeInfo->TargetFPS);
    lua_setfield(L, -2, "TargetFPS");

    lua_pushnumber(L, mp_TimeInfo->ElapsedSeconds);
    lua_setfield(L, -2, "ElapsedSeconds");

    lua_pushnumber(L, mp_TimeInfo->ElapsedMilliseconds);
    lua_setfield(L, -2, "ElapsedMilliseconds");

    lua_pushnumber(L, mp_TimeInfo->TotalSeconds);
    lua_setfield(L, -2, "TotalSeconds");

    lua_pushnumber(L, mp_TimeInfo->TotalMilliseconds);
    lua_setfield(L, -2, "TotalMilliseconds");

    lua_pushnumber(L, mp_TimeInfo->Delta);
    lua_setfield(L, -2, "Delta");

    return 1;
}

int RenderEventData::PushDataToLua(lua_State* L) const
{
    return 0;
}

GraphicsContext* RenderEventData::GetContext()
{
    return mp_Context;
}

} // namespace dusk
