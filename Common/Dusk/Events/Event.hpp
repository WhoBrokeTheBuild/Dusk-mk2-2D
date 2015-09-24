#ifndef DUSK_EVENT_HPP
#define DUSK_EVENT_HPP

#include <Dusk/Tracking/ITrackedObject.hpp>

#include <lua.hpp>
#include <string>

using std::string;

namespace dusk
{

typedef unsigned int EventID;

class IEventDispatcher;

class EventData :
    public ITrackedObject
{
public:

    static const EventData BLANK_EVENT_DATA;

    inline EventData()
    { }

    inline EventData(const EventData& rhs)
    { }

    virtual inline ~EventData()
    { }

    virtual inline string GetClassName() const
    {
        return "Event Data";
    }

    virtual EventData* Clone() const
    {
        return New EventData();
    };

    virtual int PushDataToLua(lua_State* L) const;

}; // class EventData

class Event :
    public ITrackedObject
{
public:

    Event(const EventID& eventId, const EventData& data = EventData::BLANK_EVENT_DATA) :
        m_ID(eventId),
        mp_Data(nullptr),
        mp_EventTarget(nullptr)
    {
        mp_Data = data.Clone();
    }

    Event(const Event& rhs) :
        m_ID(rhs.m_ID),
        mp_Data(nullptr),
        mp_EventTarget(nullptr)
    {
        mp_Data = (rhs.mp_Data == nullptr ? nullptr : rhs.mp_Data->Clone());
    }

    virtual inline ~Event()
    {
        delete mp_Data;
    }

    virtual int PushDataToLua(lua_State* L) const;

    virtual inline string GetClassName() const
    {
        return "Event";
    }

    inline EventID GetID() const
    {
        return m_ID;
    }

    inline IEventDispatcher* GetTarget() const
    {
        return mp_EventTarget;
    }
    template <typename T>
    inline T* GetTargetAs() const
    {
        return dynamic_cast<T*>(mp_EventTarget);
    }

    inline void setTarget(IEventDispatcher* pTarget)
    {
        mp_EventTarget = pTarget;
    }

    inline EventData* GetData() const
    {
        return mp_Data;
    }
    template <typename T>
    inline T* GetDataAs() const
    {
        return dynamic_cast<T*>(mp_Data);
    }

protected:

    EventID             m_ID;
    EventData*          mp_Data;
    IEventDispatcher*   mp_EventTarget;

}; // class Event

} // namespace dusk

#endif // DUSK_EVENT_HPP
