#include "EventDispatcher.hpp"

#include <Dusk/Scripting/Scripting.hpp>

namespace dusk
{

ArrayList<EventDispatcher*> EventDispatcher::s_Dispatchers = ArrayList<EventDispatcher*>();

dusk::EventDispatcher::EventDispatcher() :
    m_EventMap(),
    m_Changed(false)
{
    s_Dispatchers.add(this);
}

EventDispatcher::~EventDispatcher()
{
    s_Dispatchers.erase_all(this);
    RemoveAllListeners();
}

void EventDispatcher::AddEventListener(const EventID& eventId, const EventDelegate& functionDelegate)
{
    if (!m_EventMap.contains_key(eventId))
        m_EventMap.add(eventId, ArrayList<EventDelegate*>());

    unsigned int length = (unsigned int)m_EventMap[eventId].size();

    for (unsigned int i = 0; i < length; ++i)
    {
        if (m_EventMap[eventId][i] == nullptr)
            continue;
        if (*(m_EventMap[eventId][i]) == functionDelegate)
            return;
    }

    m_EventMap[eventId].add(New EventDelegate(functionDelegate));
}

void EventDispatcher::RemoveEventListener(const EventID& eventId, const EventDelegate& functionDelegate)
{
    if (!m_EventMap.contains_key(eventId))
        return;

    unsigned int length = (unsigned int)m_EventMap[eventId].size();

    for (unsigned int i = 0; i < length; ++i)
    {
        if (m_EventMap[eventId][i] == nullptr)
            continue;
        if (*(m_EventMap[eventId][i]) == functionDelegate)
        {
            delete m_EventMap[eventId][i];
            m_EventMap[eventId][i] = nullptr;
            m_Changed = true;
            return;
        }
    }
}

void EventDispatcher::RemoveEventListener(const EventID& eventId, void(*function)(const Event&))
{
    RemoveEventListener(eventId, EventDelegate(function));
}

void EventDispatcher::AddEventListener(const EventID& eventId, void(*function)(const Event&))
{
    AddEventListener(eventId, EventDelegate(function));
}

void EventDispatcher::AddEventListener(const EventID& eventId, ScriptHost* pScriptHost, const string& callback)
{
    EventDelegate *pDelegate = New EventDelegate(pScriptHost, callback);

    if (!m_EventMap.contains_key(eventId))
        m_EventMap.add(eventId, ArrayList<EventDelegate*>());

    unsigned int length = (unsigned int)m_EventMap[eventId].size();

    for (unsigned int i = 0; i < length; ++i)
    {
        if (m_EventMap[eventId][i] == nullptr)
            continue;
        if (*(m_EventMap[eventId][i]) == *pDelegate)
            return;
    }

    m_EventMap[eventId].add(pDelegate);
}

void EventDispatcher::RemoveEventListener(const EventID& eventId, ScriptHost* pScriptHost, const string& callback)
{
    EventDelegate delegate = EventDelegate(pScriptHost, callback);

    if (!m_EventMap.contains_key(eventId))
        return;

    unsigned int length = (unsigned int)m_EventMap[eventId].size();

    for (unsigned int i = 0; i < length; ++i)
    {
        if (m_EventMap[eventId][i] == nullptr)
            continue;
        if (*(m_EventMap[eventId][i]) == delegate)
        {
            delete m_EventMap[eventId][i];
            m_EventMap[eventId][i] = nullptr;
            m_Changed = true;
            return;
        }
    }
}

void EventDispatcher::RemoveAllListeners()
{
    for (auto mapIt : m_EventMap)
    {
        for (auto listener : mapIt.second)
        {
            delete listener;
        }
        mapIt.second.clear();
    }

    m_EventMap.clear();
}

void EventDispatcher::RemoveAllListeners(const EventID& eventId)
{
    if (!m_EventMap.contains_key(eventId))
        return;

    unsigned int length = (unsigned int)m_EventMap[eventId].size();
    for (unsigned int i = 0; i < length; ++i)
    {
        if (m_EventMap[eventId][i] != nullptr)
        {
            delete m_EventMap[eventId][i];
            m_EventMap[eventId][i] = nullptr;
        }
    }

    m_EventMap.erase(eventId);
    m_Changed = true;
}

void EventDispatcher::Dispatch(const Event& event)
{
    EventID id = event.GetID();

    if (!m_EventMap.contains_key(id))
        return;

    Event tmp = Event(event);

    tmp.setTarget(this);

    unsigned int length = (unsigned int)m_EventMap[id].size();
    for (unsigned int i = 0; i < length; ++i)
    {
        if (m_EventMap[id][i] != nullptr)
            m_EventMap[id][i]->Invoke(event);
    }
}

void EventDispatcher::CleanMap()
{
    if (!m_Changed)
        return;

    bool needRepeat = true;
    ArrayList<EventDelegate*>* list;

    while (needRepeat)
    {
        needRepeat = false;
        for (auto mapIt = m_EventMap.begin(); !needRepeat && mapIt != m_EventMap.end(); ++mapIt)
        {
            list = &mapIt->second;
            for (unsigned int i = 0; !needRepeat && i < list->size(); ++i)
            {
                if (list->at(i) == nullptr)
                {
                    list->erase_at(i);
                    needRepeat = true;
                    break;
                }
            }
        }
    }

    m_Changed = false;
}

void EventDispatcher::Script_RegisterFunctions()
{
    Scripting::RegisterFunction("dusk_event_dispatcher_add_event_listener", &EventDispatcher::Script_AddEventListener);
    Scripting::RegisterFunction("dusk_event_dispatcher_remove_event_listener", &EventDispatcher::Script_RemoveEventListener);
}

int EventDispatcher::Script_AddEventListener(lua_State* L)
{
    EventDispatcher* pEventDispatcher = (EventDispatcher*)lua_tointeger(L, 1);

    EventID eventId = (EventID)lua_tointeger(L, 2);
    string callback = lua_tostring(L, 3);

    pEventDispatcher->AddEventListener(eventId, Scripting::GetScriptHost(L), callback);

    return 0;
}

int EventDispatcher::Script_RemoveEventListener(lua_State* L)
{
    EventDispatcher* pEventDispatcher = (EventDispatcher*)lua_tointeger(L, 1);

    EventID eventId = (EventID)lua_tointeger(L, 2);
    string callback = lua_tostring(L, 3);

    pEventDispatcher->RemoveEventListener(eventId, Scripting::GetScriptHost(L), callback);


    return 0;
}

} // namespace dusk
