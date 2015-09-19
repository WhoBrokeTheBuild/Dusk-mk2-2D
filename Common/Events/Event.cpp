#include "Event.hpp"

namespace Dusk
{

const EventData EventData::BLANK_EVENT_DATA = EventData();

int Event::PushDataToLua(lua_State* L) const
{
	return mp_Data->PushDataToLua(L);
}

int EventData::PushDataToLua(lua_State* L) const
{
	return 0;
}

} // namespace Dusk