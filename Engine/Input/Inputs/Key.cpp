#include "Key.hpp"

namespace dusk
{

int KeyEventData::PushDataToLua(lua_State* L) const
{
	lua_pushinteger(L, m_Key);
	return 1;
}

} // namespace dusk
