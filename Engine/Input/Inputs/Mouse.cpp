#include "Mouse.hpp"

namespace dusk
{
	
int MouseButtonEventData::PushDataToLua(lua_State* L) const
{
	lua_pushinteger(L, m_MouseButton);
	return 1;
}

int MouseMoveEventData::PushDataToLua(lua_State* L) const
{
	lua_pushnumber(L, m_MouseX);
	lua_pushnumber(L, m_MouseY);
	lua_pushnumber(L, m_DeltaX);
	lua_pushnumber(L, m_DeltaY);
	return 4;
}

int MouseScrollEventData::PushDataToLua(lua_State* L) const
{
	lua_pushnumber(L, m_ScrollX);
	lua_pushnumber(L, m_ScrollY);
	return 2;
}

} // namespace dusk
