#include "IEventDispatcher.hpp"

#include <Dusk/Scripting/Scripting.hpp>

namespace dusk
{

ArrayList<IEventDispatcher*> IEventDispatcher::s_Dispatchers = ArrayList<IEventDispatcher*>();

dusk::IEventDispatcher::IEventDispatcher() :
    m_EventMap(),
    m_Changed(false)
{
    s_Dispatchers.add(this);
}

IEventDispatcher::~IEventDispatcher()
{
    s_Dispatchers.erase_all(this);
    RemoveAllListeners();
}

void IEventDispatcher::AddEventListener(const EventID& eventId, const EventDelegate& functionDelegate)
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

void IEventDispatcher::RemoveEventListener(const EventID& eventId, const EventDelegate& functionDelegate)
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

void IEventDispatcher::RemoveEventListener(const EventID& eventId, void(*function)(const Event&))
{
    RemoveEventListener(eventId, EventDelegate(function));
}

void IEventDispatcher::AddEventListener(const EventID& eventId, void(*function)(const Event&))
{
    AddEventListener(eventId, EventDelegate(function));
}

void IEventDispatcher::RemoveAllListeners()
{
    for (auto mapIt : m_EventMap)
    {
        // TODO: Replace
    }

    m_EventMap.clear();
}

void IEventDispatcher::RemoveAllListeners(const EventID& eventId)
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

void IEventDispatcher::Dispatch(const Event& event)
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

void IEventDispatcher::CleanMap()
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

void IEventDispatcher::Script_RegisterFunctions()
{
    Scripting::RegisterFunction("dusk_ievent_dispatcher_add_event_listener", &IEventDispatcher::Script_AddEventListener);
    Scripting::RegisterFunction("dusk_ievent_dispatcher_remove_event_listener", &IEventDispatcher::Script_RemoveEventListener);
}

int IEventDispatcher::Script_AddEventListener(lua_State* L)
{
    IEventDispatcher* pEventDispatcher = (IEventDispatcher*)lua_tointeger(L, 1);

    EventID eventId = (EventID)lua_tointeger(L, 2);
    string callback = lua_tostring(L, 3);

    EventDelegate *pDelegate = New EventDelegate(Scripting::GetScriptHost(L), callback);

    if (!pEventDispatcher->m_EventMap.contains_key(eventId))
        pEventDispatcher->m_EventMap.add(eventId, ArrayList<EventDelegate*>());

    unsigned int length = (unsigned int)pEventDispatcher->m_EventMap[eventId].size();

    for (unsigned int i = 0; i < length; ++i)
    {
        if (pEventDispatcher->m_EventMap[eventId][i] == nullptr)
            continue;
        if (*(pEventDispatcher->m_EventMap[eventId][i]) == *pDelegate)
            return 0;
    }

    pEventDispatcher->m_EventMap[eventId].add(pDelegate);

    return 0;
}

int IEventDispatcher::Script_RemoveEventListener(lua_State* L)
{
    IEventDispatcher* pEventDispatcher = (IEventDispatcher*)lua_tointeger(L, 1);

    EventID eventId = (EventID)lua_tointeger(L, 2);
    string callback = lua_tostring(L, 3);

    EventDelegate delegate = EventDelegate(Scripting::GetScriptHost(L), callback);

    if (!pEventDispatcher->m_EventMap.contains_key(eventId))
        return 0;

    unsigned int length = (unsigned int)pEventDispatcher->m_EventMap[eventId].size();

    for (unsigned int i = 0; i < length; ++i)
    {
        if (pEventDispatcher->m_EventMap[eventId][i] == nullptr)
            continue;
        if (*(pEventDispatcher->m_EventMap[eventId][i]) == delegate)
        {
            delete pEventDispatcher->m_EventMap[eventId][i];
            pEventDispatcher->m_EventMap[eventId][i] = nullptr;
            pEventDispatcher->m_Changed = true;
            return 0;
        }
    }

    return 0;
}

} // namespace dusk
