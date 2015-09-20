#ifndef DUSK_UPDATE_EVENT_DATA_HPP
#define DUSK_UPDATE_EVENT_DATA_HPP

#include <Dusk/Events/Event.hpp>
#include <Dusk/Timing/FrameTimeInfo.hpp>

namespace dusk
{

class UpdateEventData :
	public EventData
{
public:

	UpdateEventData(FrameTimeInfo* timeInfo) :
		mp_TimeInfo(timeInfo)
	{ }

	virtual inline string GetClassName() const { return "Update Event Data"; }

	virtual inline EventData* Clone() const { return New UpdateEventData(mp_TimeInfo); }

	FrameTimeInfo* GetTimeInfo();

	virtual int PushDataToLua(lua_State* L) const;

private:

	FrameTimeInfo* mp_TimeInfo;

}; // class UpdateEventData

} // namespace dusk

#endif // DUSK_UPDATE_EVENT_DATA_HPP