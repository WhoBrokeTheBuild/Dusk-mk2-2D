#include "Mapped.hpp"

namespace dusk
{

int MappedInputEventData::PushDataToLua(lua_State* L) const
{
    lua_pushstring(L, m_MappedInput.c_str());
    return 1;
}

} // namespace dusk