#include "GraphicsContext.hpp"

#include <Graphics/Window.hpp>
#include <Graphics/Sprite.hpp>
#include <Scripting/ScriptingSystem.hpp>
#include <Logging/LoggingSystem.hpp>

namespace dusk
{

void GraphicsContext::Clear()
{
	m_SFMLWindow.clear();
}

void GraphicsContext::SwapBuffers()
{
	m_SFMLWindow.display();
}

void GraphicsContext::Draw(Sprite* sprite)
{
	m_SFMLWindow.draw(sprite->GetSFMLSprite());
}

void GraphicsContext::InitScripting()
{
	ScriptingSystem::RegisterFunction("dusk_graphics_context_clear",	    &GraphicsContext::Script_Clear);
	ScriptingSystem::RegisterFunction("dusk_graphics_context_draw",         &GraphicsContext::Script_Draw);
	ScriptingSystem::RegisterFunction("dusk_graphics_context_swap_buffers", &GraphicsContext::Script_SwapBuffers);
}

int GraphicsContext::Script_Clear(lua_State* L)
{
	GraphicsContext* pContext = (GraphicsContext*)lua_tointeger(L, 1);
	
	pContext->Clear();

	return 0;
}

int GraphicsContext::Script_Draw(lua_State* L)
{
	GraphicsContext* pContext = (GraphicsContext*)lua_tointeger(L, 1);
	Sprite* pSprite = (Sprite*)lua_tointeger(L, 2);

	pContext->Draw(pSprite);

	return 0;
}

int GraphicsContext::Script_SwapBuffers(lua_State* L)
{
	GraphicsContext* pContext = (GraphicsContext*)lua_tointeger(L, 1);

	pContext->SwapBuffers();

	return 0;
}

} // namespace dusk
