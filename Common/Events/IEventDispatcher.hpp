#ifndef DUSK_EVENT_DISPATCHER_HPP
#define DUSK_EVENT_DISPATCHER_HPP

#include <Collections/ArrayList.hpp>
#include <Collections/Map.hpp>
#include <Events/Event.hpp>
#include <Events/Delegate.hpp>

#include <lua.hpp>

namespace dusk
{

typedef Delegate<void, const Event&> EventDelegate;

class IEventDispatcher
{
public:

	IEventDispatcher();
	virtual ~IEventDispatcher();

	virtual inline string GetClassName() const { return "Event Dispatcher";  }

	void AddEventListener(const EventID& eventId, const EventDelegate& funcDelegate);
	void RemoveEventListener(const EventID& eventId, const EventDelegate& funcDelegate);

	void AddEventListener(const EventID& eventId, void(*pFunction)(const Event&));
	void RemoveEventListener(const EventID& eventId, void(*pFunction)(const Event&));

	template <typename ObjectType, typename Method>
	inline void AddEventListener(const EventID& eventId, ObjectType* pObject, Method method)
	{
		AddEventListener(eventId, EventDelegate(pObject, method));
	}

	template <typename ObjectType, typename Method>
	inline void RemoveEventListener(const EventID& eventId, ObjectType* pObject, Method method)
	{
		RemoveEventListener(eventId, EventDelegate(pObject, method));
	}

	template <typename ObjectType>
	void RemoveAllMethods(ObjectType* pObject);

	void RemoveAllListeners();
	void RemoveAllListeners(const EventID& eventId);

	void Dispatch(const Event& event);

	static void CleanEvents()
	{
		unsigned int length = (unsigned int)s_Dispatchers.size();
		for (unsigned int i = 0; i < length; ++i)
			s_Dispatchers[i]->CleanMap();
	}

	static void InitScripting();
	static int Script_AddEventListener(lua_State* L);
	static int Script_RemoveEventListener(lua_State* L);

private:

	void CleanMap();

	static ArrayList<IEventDispatcher*>         s_Dispatchers;
	Map<EventID, ArrayList<EventDelegate*>>     m_EventMap;

	bool    m_Changed;


}; // class EventDispatcher

template <typename ObjectType>
void IEventDispatcher::RemoveAllMethods( ObjectType* object )
{
	bool needRepeat = true;
	while (needRepeat)
	{
		needRepeat = false;
		for (auto mapIt : m_EventMap)
		{
			for (auto item : mapIt->second)
			{
				if (item == nullptr)
					continue;

				if (item->IsMethodOf(object))
				{
					item = nullptr;
					needRepeat = true;
					break;
				}
			}
		}
	}
}

} // namespace dusk

#endif // DUSK_EVENT_DISPATCHER_HPP
