#include "Program.hpp"

#include <Utility/Benchmark.hpp>
#include <Logging/LoggingSystem.hpp>
#include <Graphics/GraphicsSystem.hpp>
#include <Timing/FrameTimeInfo.hpp>
#include <Input/InputSystem.hpp>
#include <Scripting/ScriptingSystem.hpp>
#include <Scripting/ScriptHost.hpp>

#include <chrono>
using namespace std::chrono;

namespace Dusk 
{

EventID Program::EVT_UPDATE	= 1;
EventID Program::EVT_RENDER	= 3;

bool Program::Init()
{
	DuskBenchStart();

	if (!InitGraphics())
	{
		DuskLog("error", "Graphics Init Failed");
		return false;
	}
	DuskLog("info", "Graphics Init Succeeded");

	if (!InitAudio())
	{
		DuskLog("error", "Audio Init Failed");
		return false;
	}
	DuskLog("info", "Audio Init Succeeded");

	if (!InitInput())
	{
		DuskLog("error", "Input Init Failed");
		return false;
	}
	DuskLog("info", "Input Init Succeeded");

	InitScripting();

	SetTargetFPS(60.0);

	mp_ScriptHost = New ScriptHost();
	mp_ScriptHost->Init();

	mp_ScriptHost->RunFile("Assets/Scripts/Setup.luac");

	DuskBenchEnd("Program::Init");
	return true;
}

void Program::Term()
{
	delete mp_ScriptHost;
	mp_ScriptHost = nullptr;

	TermGraphics();
	TermAudio();
	TermInput();
}

void Program::Run()
{
	if (!Init())
	{
		DuskLog("error", "Program Init Failed");
		return;
	}
	DuskLog("info", "Program Init Succeeded");

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
			Render();
			++frameCount;
			m_CurrentFPS = (m_UpdateInterval / secsSinceLastFrame) * m_TargetFPS;

			secsSinceLastFrame = 0;
		}
	}
}

void Program::Update(FrameTimeInfo& timeInfo)
{
	Dispatch(Event(EVT_UPDATE, UpdateEventData(&timeInfo)));
}

void Program::Render()
{
	Dispatch(Event(EVT_RENDER, RenderEventData()));
}

bool Program::InitGraphics()
{
	delete mp_GraphicsSystem;
	mp_GraphicsSystem = New GraphicsSystem();

	return mp_GraphicsSystem->Init();
}

void Program::TermGraphics()
{
	delete mp_GraphicsSystem;
	mp_GraphicsSystem = nullptr;
}

bool Program::InitInput()
{
	delete mp_InputSystem;
	mp_InputSystem = New InputSystem();

	return mp_InputSystem->Init();
}

void Program::TermInput()
{
	delete mp_InputSystem;
	mp_InputSystem = nullptr;
}

bool Program::InitAudio()
{
	return true;
}

void Program::TermAudio()
{
}

GraphicsSystem* Program::GetGraphicsSystem()
{
	return mp_GraphicsSystem;
}

InputSystem* Program::GetInputSystem()
{
	return mp_InputSystem;
}

void Program::SetTargetFPS(double fps)
{
	m_TargetFPS = fps;
	m_UpdateInterval = (1.0 / m_TargetFPS);
}

FrameTimeInfo* UpdateEventData::GetTimeInfo()
{
	return mp_TimeInfo;
}

int UpdateEventData::PushDataToLua(lua_State* L) const
{
	lua_newtable(L);
	int top = lua_gettop(L);

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

void Program::InitScripting()
{
	ScriptingSystem::RegisterFunction("dusk_get_program",		  &Program::Script_GetProgram);
	ScriptingSystem::RegisterFunction("dusk_program_exit",		  &Program::Script_Exit);
	ScriptingSystem::RegisterFunction("dusk_get_graphics_system", &Program::Script_GetGraphicsSystem);
	ScriptingSystem::RegisterFunction("dusk_get_input_system",    &Program::Script_GetInputSystem);

	IEventDispatcher::InitScripting();
	GraphicsSystem::InitScripting();
	InputSystem::InitScripting();
}

int Program::Script_GetProgram(lua_State* L)
{
	lua_pushinteger(L, (ptrdiff_t)Program::Inst());
	return 1;
}

int Dusk::Program::Script_Exit(lua_State* L)
{
	Program* pProgram = (Program*)lua_tointeger(L, 1);
	pProgram->Exit();
	return 0;
}

int Program::Script_GetGraphicsSystem(lua_State* L)
{
	lua_pushinteger(L, (ptrdiff_t)Program::Inst()->GetGraphicsSystem());
	return 1;
}

int Program::Script_GetInputSystem(lua_State* L)
{
	lua_pushinteger(L, (ptrdiff_t)Program::Inst()->GetInputSystem());
	return 1;
}

} // namespace Dusk