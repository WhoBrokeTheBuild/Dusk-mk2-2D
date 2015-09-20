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

Program* Program::sp_Inst = nullptr;

EventID Program::EVT_UPDATE = 1;
EventID Program::EVT_RENDER	= 2;
EventID Program::EVT_EXIT = 3;

Program::Program() :
	m_Running(),
	m_TargetFPS(),
	m_CurrentFPS(),
	m_UpdateInterval(),
	mp_ScriptHost(nullptr)
{
	sp_Inst = this;
}

void Program::Run()
{
	DuskLog("verbose", "Program running");

	if (!Init())
	{
		DuskLog("error", "Failed to start program");
		return;
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

	Dispatch(Event(EVT_EXIT));
	DuskLog("verbose", "Program Exiting");
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

	GraphicsSystem::CreateInst()->Init(1024, 768, "Dusk 2D", GraphicsSystem::DECORATED);
	InputSystem::CreateInst()->Init();

	Script_RegisterFunctions();

	SetTargetFPS(60.0);

	mp_ScriptHost = New ScriptHost();
	mp_ScriptHost->Init();

	mp_ScriptHost->RunFile("Scripts/Dusk");

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
	Dispatch(Event(EVT_UPDATE, UpdateEventData(&timeInfo)));
}

void Program::PreRender(GraphicsContext* ctx)
{
	ctx->Clear();
}

void Program::Render(GraphicsContext* ctx)
{
	Dispatch(Event(EVT_RENDER, RenderEventData(ctx)));
}

void Program::PostRender(GraphicsContext* ctx)
{
	ctx->SwapBuffers();
}

void Program::Script_RegisterFunctions()
{
	Scripting::RegisterFunction("dusk_get_program",  &Program::Script_GetProgram);
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

} // namespace dusk
