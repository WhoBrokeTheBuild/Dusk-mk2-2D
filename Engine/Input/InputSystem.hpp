#ifndef DUSK_INPUT_INPUT_SYSTEM_HPP
#define DUSK_INPUT_INPUT_SYSTEM_HPP

#include <Tracking/ITrackedObject.hpp>
#include <Events/IEventDispatcher.hpp>
#include <Input/Inputs/Key.hpp>
#include <Input/Inputs/Mouse.hpp>

#include <lua.hpp>

namespace dusk
{

typedef string MappedInputID;

class MappedInputEventData :
	public EventData
{
public:

	MappedInputEventData(const MappedInputID& mappedInput) :
		m_MappedInput(mappedInput)
	{ }

	virtual inline string GetClassName() const { return "Mapped Input Event Data"; }

	virtual inline EventData* Clone() const { return New MappedInputEventData(m_MappedInput); }

	inline MappedInputID GetMappedInput() const { return m_MappedInput; }

	virtual int PushDataToLua(lua_State* L) const;

private:

	MappedInputID		m_MappedInput;

}; // class MappedInputEventData

class InputSystem :
	public IEventDispatcher,
	public ITrackedObject
{
public:

	static EventID
		EVT_KEY_PRESS,
		EVT_KEY_RELEASE,

		EVT_MOUSE_MOVE,
		EVT_MOUSE_SCROLL,
		EVT_MOUSE_BUTTON_PRESS,
		EVT_MOUSE_BUTTON_RELEASE,

		EVT_MAPPED_INPUT_PRESS,
		EVT_MAPPED_INPUT_RELEASE;

	InputSystem() :
		m_MouseX(0),
		m_MouseY(0),
		m_MappedKeys(),
		m_MappedMouseButtons()
	{ }

	~InputSystem() { Term(); }

	virtual inline string GetClassName() const { return "Input System"; }

	bool Init();
	void Term();

	void MapKey(const MappedInputID& id, const Key& key);
	void MapMouseButton(const MappedInputID& id, const MouseButton& button);

	Key GetMappedKey(const MappedInputID& id);
	MouseButton GetMappedMouseButton(const MappedInputID& id);

	void TriggerKeyPress(const Key& key);
	void TriggerKeyRelease(const Key& key);

	void TriggerMouseMoveRelative(const double& dx, const double& dy);
	void TriggerMouseMoveAbsolute(const double& x, const double& y);
	void TriggerMouseScroll(const double& dx, const double& dy);
	void TriggerMouseButtonPress(const MouseButton& mouseButton);
	void TriggerMouseButtonRelease(const MouseButton& mouseButton);

	void TriggerMappedInputPress(const MappedInputID& input);
	void TriggerMappedInputRelease(const MappedInputID& input);

	static void InitScripting();
	static int Script_MapKey(lua_State* L);
	static int Script_MapMouseButton(lua_State* L);
	static int Script_GetMappedKey(lua_State* L);
	static int Script_GetMappedMouseButton(lua_State* L);

private:

	double m_MouseX;

	double m_MouseY;

	Map<Key, MappedInputID>	m_MappedKeys;

	Map<MouseButton, MappedInputID> m_MappedMouseButtons;


}; // class InputSystem

} // namespace dusk

#endif // DUSK_INPUT_INPUT_SYSTEM_HPP