#include "Mouse.hpp"

namespace dusk
{

Mouse::Button Mouse::ConvertSFMLMouseButton(sf::Mouse::Button button)
{
    switch (button)
    {
    case sf::Mouse::Button::Left:
        return Button::Left;

    case sf::Mouse::Button::Middle:
        return Button::Middle;

    case sf::Mouse::Button::Right:
        return Button::Right;

    case sf::Mouse::Button::XButton1:
        return Button::Extra1;

    case sf::Mouse::Button::XButton2:
        return Button::Extra2;
    }

    return Button::Invalid;
}

int MouseButtonEventData::PushDataToLua(lua_State* L) const
{
    lua_pushinteger(L, m_MouseButton);
    return 1;
}

int MouseMoveEventData::PushDataToLua(lua_State* L) const
{
    lua_pushnumber(L, m_MousePos.x);
    lua_pushnumber(L, m_MousePos.y);
    lua_pushnumber(L, m_MouseDelta.x);
    lua_pushnumber(L, m_MouseDelta.y);
    return 4;
}

int MouseScrollEventData::PushDataToLua(lua_State* L) const
{
    lua_pushnumber(L, m_ScrollX);
    lua_pushnumber(L, m_ScrollY);
    return 2;
}

} // namespace dusk
