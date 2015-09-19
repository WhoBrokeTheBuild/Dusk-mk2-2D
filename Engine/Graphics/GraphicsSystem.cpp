#include "GraphicsSystem.hpp"

#include <Program.hpp>
#include <Utility/Benchmark.hpp>
#include <Graphics/Window.hpp>
#include <Logging/LoggingSystem.hpp>
#include <Scripting/ScriptingSystem.hpp>

namespace Dusk
{

bool GraphicsSystem::Init()
{
	DuskBenchStart();

	delete mp_Window;
	mp_Window = New Window();
	mp_Window->Init(800, 600, "Test", Window::DECORATED | Window::RESIZABLE);

	DuskBenchEnd("GraphicsSystem::Init");
	return true;
}

void GraphicsSystem::Term()
{
	delete mp_Window;
	mp_Window = nullptr;
}

Window* GraphicsSystem::GetWindow() const
{
	return mp_Window;
}

void GraphicsSystem::InitScripting()
{
	ScriptingSystem::RegisterFunction("dusk_graphics_system_get_window", &GraphicsSystem::Script_GetWindow);

	Window::InitScripting();
}

int GraphicsSystem::Script_GetWindow(lua_State* L)
{
	lua_pushinteger(L, (ptrdiff_t)Program::Inst()->GetGraphicsSystem()->GetWindow());
	return 1;
}

} // namespace Dusk