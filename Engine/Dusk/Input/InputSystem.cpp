#include "InputSystem.hpp"

#include <Dusk/Program.hpp>
#include <Dusk/Logging/Logging.hpp>
#include <Dusk/Events/Event.hpp>
#include <Dusk/Scripting/Scripting.hpp>

namespace dusk
{
	
InputSystem* InputSystem::sp_Inst = nullptr;

EventID InputSystem::EVT_KEY_PRESS				= 1;
EventID InputSystem::EVT_KEY_RELEASE			= 2;

EventID InputSystem::EVT_MOUSE_MOVE				= 10;
EventID InputSystem::EVT_MOUSE_SCROLL           = 11;
EventID InputSystem::EVT_MOUSE_BUTTON_PRESS		= 12;
EventID InputSystem::EVT_MOUSE_BUTTON_RELEASE   = 13;

EventID InputSystem::EVT_MAPPED_INPUT_PRESS		= 20;
EventID InputSystem::EVT_MAPPED_INPUT_RELEASE	= 21;

bool InputSystem::Init()
{
	DuskLog("verbose", "Input System initializing");

	m_MappedKeys.clear();
	m_MappedMouseButtons.clear();

	return true;
}

void InputSystem::Term()
{
	
}

void InputSystem::MapKey(const MappedInputID & id, const Key & key)
{
	m_MappedKeys.erase_all(id);
	m_MappedKeys.add(key, id);
}

void InputSystem::MapMouseButton(const MappedInputID& id, const MouseButton& button)
{
	m_MappedMouseButtons.erase_all(id);
	m_MappedMouseButtons.add(button, id);
}

Key InputSystem::GetMappedKey(const MappedInputID& id)
{
	for (const auto& it : m_MappedKeys)
	{
		if (it.second == id)
			return it.first;
	}

	return Key::INVALID_KEY;
}

MouseButton InputSystem::GetMappedMouseButton(const MappedInputID& id)
{
	for (const auto& it : m_MappedMouseButtons)
	{
		if (it.second == id)
			return it.first;
	}

	return MouseButton::INVALID_MOUSE_BUTTON;
}

void InputSystem::TriggerKeyPress(const Key& key)
{
	if ( m_MappedKeys.contains_key(key) )
	{
		Dispatch(Event(EVT_MAPPED_INPUT_PRESS, MappedInputEventData(m_MappedKeys[key])));
	}

	Dispatch(Event(EVT_KEY_PRESS, KeyEventData(key)));
}

void InputSystem::TriggerKeyRelease(const Key& key)
{
	if ( m_MappedKeys.contains_key(key) ) 
	{
		Dispatch(Event(EVT_MAPPED_INPUT_RELEASE, MappedInputEventData(m_MappedKeys[key])));
	}

	Dispatch(Event(EVT_KEY_RELEASE, KeyEventData(key)));
}

void InputSystem::TriggerMouseMoveRelative(const double& dx, const double& dy)
{
	m_MouseX += dx;
	m_MouseY += dy;

	Dispatch(Event(EVT_MOUSE_MOVE, MouseMoveEventData(m_MouseX, m_MouseY, dx, dy)));
}

void InputSystem::TriggerMouseMoveAbsolute(const double& x, const double& y)
{
	double dx = x - m_MouseX,
		   dy = y - m_MouseY;

	m_MouseX = x;
	m_MouseY = y;

	Dispatch(Event(EVT_MOUSE_MOVE, MouseMoveEventData(m_MouseX, m_MouseY, dx, dy)));
}

void InputSystem::TriggerMouseScroll(const double& dx, const double& dy)
{
	Dispatch(Event(EVT_MOUSE_SCROLL, MouseScrollEventData(dx, dy)));
}

void InputSystem::TriggerMouseButtonPress(const MouseButton& mouseButton)
{
	if ( m_MappedMouseButtons.contains_key(mouseButton) )
	{
		Dispatch(Event(EVT_MAPPED_INPUT_PRESS, MappedInputEventData(m_MappedMouseButtons[mouseButton])));
	}

	Dispatch(Event(EVT_MOUSE_BUTTON_PRESS, MouseButtonEventData(mouseButton)));
}

void InputSystem::TriggerMouseButtonRelease(const MouseButton& mouseButton)
{
	if ( m_MappedMouseButtons.contains_key(mouseButton) )
	{
		Dispatch(Event(EVT_MAPPED_INPUT_RELEASE, MappedInputEventData(m_MappedMouseButtons[mouseButton])));
	}

	Dispatch(Event(EVT_MOUSE_BUTTON_RELEASE, MouseButtonEventData(mouseButton)));
}

void InputSystem::TriggerMappedInputPress(const MappedInputID& input)
{
	Dispatch(Event(EVT_MAPPED_INPUT_PRESS, MappedInputEventData(input)));
}

void InputSystem::TriggerMappedInputRelease(const MappedInputID& input)
{
	Dispatch(Event(EVT_MAPPED_INPUT_RELEASE, MappedInputEventData(input)));
}

void InputSystem::InitScripting( void )
{
	Scripting::RegisterFunction("dusk_input_system_map_key",					&InputSystem::Script_MapKey);
	Scripting::RegisterFunction("dusk_input_system_map_mouse_button",			&InputSystem::Script_MapMouseButton);
	Scripting::RegisterFunction("dusk_input_system_get_mapped_key",			&InputSystem::Script_GetMappedKey);
	Scripting::RegisterFunction("dusk_input_system_get_mapped_mouse_button",	&InputSystem::Script_GetMappedMouseButton);
}

int InputSystem::Script_MapKey(lua_State* L)
{
	InputSystem* pInputSystem = (InputSystem*)lua_tointeger(L, 1);

	string input = lua_tostring(L, 2);
	Key key = (Key)lua_tointeger(L, 3);

	pInputSystem->MapKey(input, key);

	return 0;
}

int InputSystem::Script_MapMouseButton(lua_State* L)
{
	InputSystem* pInputSystem = (InputSystem*)lua_tointeger(L, 1);

	string input = lua_tostring(L, 2);
	MouseButton button = (MouseButton)lua_tointeger(L, 3);

	pInputSystem->MapMouseButton(input, button);

	return 0;
}

int InputSystem::Script_GetMappedKey(lua_State* L)
{
	InputSystem* pInputSystem = (InputSystem*)lua_tointeger(L, 1);

	string input = lua_tostring(L, 2);

	Key key = pInputSystem->GetMappedKey(input);

	lua_pushinteger(L, key);

	return 1;
}

int InputSystem::Script_GetMappedMouseButton(lua_State* L)
{
	InputSystem* pInputSystem = (InputSystem*)lua_tointeger(L, 1);

	string input = lua_tostring(L, 2);

	MouseButton button = pInputSystem->GetMappedMouseButton(input);

	lua_pushinteger(L, button);

	return 1;
}

} // namespace dusk
