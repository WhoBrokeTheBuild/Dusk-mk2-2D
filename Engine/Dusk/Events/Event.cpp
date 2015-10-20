#include "Event.hpp"

namespace dusk
{

const EventData EventData::BlankEventData = EventData();

int Event::PushDataToLua(lua_State* L) const
{
    return m_Data->PushDataToLua(L);
}

int EventData::PushDataToLua(lua_State* L) const
{
    return 0;
}

} // namespace dusk
