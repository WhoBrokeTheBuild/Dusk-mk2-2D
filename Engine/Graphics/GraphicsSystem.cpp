#include "GraphicsSystem.hpp"

#include <Program.hpp>
#include <Graphics/Window.hpp>
#include <Graphics/GraphicsContext.hpp>
#include <Graphics/Texture.hpp>
#include <Graphics/Sprite.hpp>
#include <Utility/Benchmark.hpp>
#include <Logging/LoggingSystem.hpp>
#include <Scripting/ScriptingSystem.hpp>

namespace dusk
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


GraphicsContext* GraphicsSystem::GetGraphicsContext() const
{
	if (mp_Window)
	{
		return mp_Window->GetGraphicsContext();
	}
	return nullptr;
}

void GraphicsSystem::InitScripting()
{
	ScriptingSystem::RegisterFunction("dusk_graphics_system_get_window",           &GraphicsSystem::Script_GetWindow);
	ScriptingSystem::RegisterFunction("dusk_graphics_system_get_graphics_context", &GraphicsSystem::Script_GetGraphicsContext);

	Window::InitScripting();
	GraphicsContext::InitScripting();
	Texture::InitScripting();
	Sprite::InitScripting();
}

int GraphicsSystem::Script_GetWindow(lua_State* L)
{
	lua_pushinteger(L, (ptrdiff_t)Program::Inst()->GetGraphicsSystem()->GetWindow());
	return 1;
}

int GraphicsSystem::Script_GetGraphicsContext(lua_State* L)
{
	lua_pushinteger(L, (ptrdiff_t)Program::Inst()->GetGraphicsSystem()->GetGraphicsContext());
	return 1;
}

} // namespace dusk
