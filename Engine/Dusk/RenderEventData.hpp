#ifndef DUSK_RENDER_EVENT_DATA
#define DUSK_RENDER_EVENT_DATA

#include <Dusk/Events/Event.hpp>

namespace dusk
{

class GraphicsContext;

class RenderEventData :
	public EventData
{
public:

	RenderEventData(GraphicsContext* ctx)
	{ }

	virtual inline string GetClassName() const { return "Render Event Data"; }

	virtual inline EventData* Clone() const { return New RenderEventData(mp_Context); }

	virtual int PushDataToLua(lua_State* L) const;

	virtual GraphicsContext* GetContext();

private:

	GraphicsContext* mp_Context;

}; // class RenderEventData

} // namespace dusk

#endif // DUSK_RENDER_EVENT_DATA
