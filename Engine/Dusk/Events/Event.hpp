#ifndef DUSK_EVENT_HPP
#define DUSK_EVENT_HPP

#include <Dusk/Tracking/TrackedObject.hpp>

#include <lua.hpp>
#include <string>

using std::string;

namespace dusk
{

typedef unsigned int EventID;

class EventDispatcher;

class EventData :
    public TrackedObject
{
public:

    static const EventData BlankEventData;

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
    public TrackedObject
{
public:

    Event(const EventID& eventId, const EventData& data = EventData::BlankEventData) :
        m_ID(eventId),
        m_Data(nullptr),
        m_EventTarget(nullptr)
    {
        m_Data = data.Clone();
    }

    Event(const Event& rhs) :
        m_ID(rhs.m_ID),
        m_Data(nullptr),
        m_EventTarget(nullptr)
    {
        m_Data = (rhs.m_Data == nullptr ? nullptr : rhs.m_Data->Clone());
    }

    virtual inline ~Event()
    {
        delete m_Data;
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

    inline EventDispatcher* GetTarget() const
    {
        return m_EventTarget;
    }
    template <typename T>
    inline T* GetTargetAs() const
    {
        return dynamic_cast<T*>(m_EventTarget);
    }

    inline void setTarget(EventDispatcher* pTarget)
    {
        m_EventTarget = pTarget;
    }

    inline EventData* GetData() const
    {
        return m_Data;
    }
    template <typename T>
    inline T* GetDataAs() const
    {
        return dynamic_cast<T*>(m_Data);
    }

protected:

    EventID             m_ID;
    EventData*          m_Data;
    EventDispatcher*    m_EventTarget;

}; // class Event

} // namespace dusk

#endif // DUSK_EVENT_HPP
