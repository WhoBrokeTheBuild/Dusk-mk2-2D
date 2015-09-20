#include "UpdateEventData.hpp"

namespace dusk
{

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

} // namespace dusk