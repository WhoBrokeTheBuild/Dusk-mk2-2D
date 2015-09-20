#include "RenderEventData.hpp"

namespace dusk
{

int RenderEventData::PushDataToLua(lua_State* L) const
{
	return 0;
}

GraphicsContext* RenderEventData::GetContext()
{
	return mp_Context;
}

} // namespace dusk