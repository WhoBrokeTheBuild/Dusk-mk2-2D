#ifndef DUSK_INPUT_INPUT_SYSTEM_HPP
#define DUSK_INPUT_INPUT_SYSTEM_HPP

#include <Dusk/Tracking/ITrackedObject.hpp>
#include <Dusk/Events/IEventDispatcher.hpp>
#include <Dusk/Input/Keyboard.hpp>
#include <Dusk/Input/Mouse.hpp>
#include <Dusk/Input/Mapped.hpp>

#include <lua.hpp>

namespace dusk
{

class Program;

class InputSystem :
	public IEventDispatcher,
	public ITrackedObject
{

	friend class Program;

public:

	static inline InputSystem* Inst()
	{
		return sp_Inst;
	}

	static EventID EvtKeyPress;
	static EventID EvtKeyRelease;

	static EventID EvtMouseMove;
	static EventID EvtMouseScroll;
	static EventID EvtMouseButtonPress;
	static EventID EvtMouseButtonRelease;

	static EventID EvtMappedInputPress;
	static EventID EvtMappedInputRelease;

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

	void MapKey(const MappedInputID& id, const Keyboard::Key& key);
	void MapMouseButton(const MappedInputID& id, const Mouse::Button& button);

	Keyboard::Key GetMappedKey(const MappedInputID& id);
	Mouse::Button GetMappedMouseButton(const MappedInputID& id);

	void TriggerKeyPress(const Keyboard::Key& key);
	void TriggerKeyRelease(const Keyboard::Key& key);

	void TriggerMouseMoveRelative(const double& dx, const double& dy);
	void TriggerMouseMoveAbsolute(const double& x, const double& y);
	void TriggerMouseScroll(const double& dx, const double& dy);
	void TriggerMouseButtonPress(const Mouse::Button& mouseButton);
	void TriggerMouseButtonRelease(const Mouse::Button& mouseButton);

	void TriggerMappedInputPress(const MappedInputID& input);
	void TriggerMappedInputRelease(const MappedInputID& input);

	static void InitScripting();
	static int Script_Get(lua_State* L);
	static int Script_MapKey(lua_State* L);
	static int Script_MapMouseButton(lua_State* L);
	static int Script_GetMappedKey(lua_State* L);
	static int Script_GetMappedMouseButton(lua_State* L);

private:

	static InputSystem* sp_Inst;

	static inline InputSystem* CreateInst()
	{
		sp_Inst = New InputSystem();
		return sp_Inst;
	}

	static inline void DestroyInst()
	{
		delete sp_Inst;
		sp_Inst = nullptr;
	}

	double m_MouseX;

	double m_MouseY;

	Map<Keyboard::Key, MappedInputID> m_MappedKeys;

	Map<Mouse::Button, MappedInputID> m_MappedMouseButtons;


}; // class InputSystem

} // namespace dusk

#endif // DUSK_INPUT_INPUT_SYSTEM_HPP