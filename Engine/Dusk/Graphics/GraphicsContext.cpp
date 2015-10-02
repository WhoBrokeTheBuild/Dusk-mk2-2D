#include "GraphicsContext.hpp"

#include <Dusk/Graphics/GraphicsSystem.hpp>
#include <Dusk/Graphics/Sprite.hpp>
#include <Dusk/Graphics/TextBuffer.hpp>
#include <Dusk/Scripting/Scripting.hpp>
#include <Dusk/Logging/Logging.hpp>

namespace dusk
{

void GraphicsContext::Clear()
{
    m_SfWindow.clear();
}

void GraphicsContext::SwapBuffers()
{
    m_SfWindow.display();
}

void GraphicsContext::Draw(Sprite* sprite)
{
    m_SfWindow.draw(sprite->GetSFMLSprite());
}

void GraphicsContext::Draw(TextBuffer* textBuffer)
{
    m_SfWindow.draw(textBuffer->GetSFMLText());
}

void GraphicsContext::Draw(const sf::Drawable& drawable)
{
    m_SfWindow.draw(drawable);
}

void GraphicsContext::Script_RegisterFunctions()
{
    Scripting::RegisterFunction("dusk_graphics_context_clear", &GraphicsContext::Script_Clear);
    Scripting::RegisterFunction("dusk_graphics_context_draw", &GraphicsContext::Script_Draw);
    Scripting::RegisterFunction("dusk_graphics_context_swap_buffers", &GraphicsContext::Script_SwapBuffers);
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
