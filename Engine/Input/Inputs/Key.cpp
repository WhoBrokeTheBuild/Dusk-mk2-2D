#include "Key.hpp"

namespace Dusk
{

int KeyEventData::PushDataToLua(lua_State* L) const
{
	lua_pushinteger(L, m_Key);
	return 1;
}

} // namespace Dusk