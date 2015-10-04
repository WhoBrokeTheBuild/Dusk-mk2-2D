#include "InputSystem.hpp"

#include <Dusk/Program.hpp>
#include <Dusk/Logging/Logging.hpp>
#include <Dusk/Events/Event.hpp>
#include <Dusk/Scripting/Scripting.hpp>

namespace dusk
{

EventID InputSystem::EvtKeyPress = 1;
EventID InputSystem::EvtKeyRelease = 2;

EventID InputSystem::EvtMouseMove = 10;
EventID InputSystem::EvtMouseScroll = 11;
EventID InputSystem::EvtMouseButtonPress = 12;
EventID InputSystem::EvtMouseButtonRelease = 13;

EventID InputSystem::EvtMappedInputPress = 20;
EventID InputSystem::EvtMappedInputRelease = 21;

InputSystem::InputSystem() :
    m_MouseX(0),
    m_MouseY(0),
    m_MappedKeys(),
    m_MappedMouseButtons()
{ }

bool InputSystem::Init()
{
    DuskLog("verbose", "Input System initializing");

    m_MappedKeys.clear();
    m_MappedMouseButtons.clear();

    return true;
}

void InputSystem::Term()
{
    RemoveAllListeners();
}

void InputSystem::MapKey(const MappedInputID & id, const Keyboard::Key & key)
{
    m_MappedKeys.erase_all(id);
    m_MappedKeys.add(key, id);
}

void InputSystem::MapMouseButton(const MappedInputID& id, const Mouse::Button& button)
{
    m_MappedMouseButtons.erase_all(id);
    m_MappedMouseButtons.add(button, id);
}

Keyboard::Key InputSystem::GetMappedKey(const MappedInputID& id)
{
    for (const auto& it : m_MappedKeys)
    {
        if (it.second == id)
            return it.first;
    }

    return Keyboard::Key::Invalid;
}

Mouse::Button InputSystem::GetMappedMouseButton(const MappedInputID& id)
{
    for (const auto& it : m_MappedMouseButtons)
    {
        if (it.second == id)
            return it.first;
    }

    return Mouse::Button::Invalid;
}

void InputSystem::TriggerKeyPress(const Keyboard::Key& key)
{
    if (m_MappedKeys.contains_key(key))
    {
        Dispatch(Event(EvtMappedInputPress, MappedInputEventData(m_MappedKeys[key])));
    }

    Dispatch(Event(EvtKeyPress, KeyEventData(key)));
}

void InputSystem::TriggerKeyRelease(const Keyboard::Key& key)
{
    if (m_MappedKeys.contains_key(key))
    {
        Dispatch(Event(EvtMappedInputRelease, MappedInputEventData(m_MappedKeys[key])));
    }

    Dispatch(Event(EvtKeyRelease, KeyEventData(key)));
}

void InputSystem::TriggerMouseMoveRelative(const double& dx, const double& dy)
{
    m_MouseX += dx;
    m_MouseY += dy;

    Dispatch(Event(EvtMouseMove, MouseMoveEventData(m_MouseX, m_MouseY, dx, dy)));
}

void InputSystem::TriggerMouseMoveAbsolute(const double& x, const double& y)
{
    double dx = x - m_MouseX,
        dy = y - m_MouseY;

    m_MouseX = x;
    m_MouseY = y;

    Dispatch(Event(EvtMouseMove, MouseMoveEventData(m_MouseX, m_MouseY, dx, dy)));
}

void InputSystem::TriggerMouseScroll(const double& dx, const double& dy)
{
    Dispatch(Event(EvtMouseScroll, MouseScrollEventData(dx, dy)));
}

void InputSystem::TriggerMouseButtonPress(const Mouse::Button& mouseButton)
{
    if (m_MappedMouseButtons.contains_key(mouseButton))
    {
        Dispatch(Event(EvtMappedInputPress, MappedInputEventData(m_MappedMouseButtons[mouseButton])));
    }

    Dispatch(Event(EvtMouseButtonPress, MouseButtonEventData(mouseButton, m_MouseX, m_MouseY)));
}

void InputSystem::TriggerMouseButtonRelease(const Mouse::Button& mouseButton)
{
    if (m_MappedMouseButtons.contains_key(mouseButton))
    {
        Dispatch(Event(EvtMappedInputRelease, MappedInputEventData(m_MappedMouseButtons[mouseButton])));
    }

    Dispatch(Event(EvtMouseButtonRelease, MouseButtonEventData(mouseButton, m_MouseX, m_MouseY)));
}

void InputSystem::TriggerMappedInputPress(const MappedInputID& input)
{
    Dispatch(Event(EvtMappedInputPress, MappedInputEventData(input)));
}

void InputSystem::TriggerMappedInputRelease(const MappedInputID& input)
{
    Dispatch(Event(EvtMappedInputRelease, MappedInputEventData(input)));
}

void InputSystem::InitScripting(void)
{
    Scripting::RegisterFunction("dusk_get_input_system", &InputSystem::Script_Get);
    Scripting::RegisterFunction("dusk_input_system_map_key", &InputSystem::Script_MapKey);
    Scripting::RegisterFunction("dusk_input_system_map_mouse_button", &InputSystem::Script_MapMouseButton);
    Scripting::RegisterFunction("dusk_input_system_get_mapped_key", &InputSystem::Script_GetMappedKey);
    Scripting::RegisterFunction("dusk_input_system_get_mapped_mouse_button", &InputSystem::Script_GetMappedMouseButton);
}

int InputSystem::Script_Get(lua_State* L)
{
    lua_pushinteger(L, (ptrdiff_t)Program::Inst()->GetInputSystem());
    return 1;
}

int InputSystem::Script_MapKey(lua_State* L)
{
    InputSystem* pInputSystem = (InputSystem*)lua_tointeger(L, 1);

    string input = lua_tostring(L, 2);
    Keyboard::Key key = (Keyboard::Key)lua_tointeger(L, 3);

    pInputSystem->MapKey(input, key);

    return 0;
}

int InputSystem::Script_MapMouseButton(lua_State* L)
{
    InputSystem* pInputSystem = (InputSystem*)lua_tointeger(L, 1);

    string input = lua_tostring(L, 2);
    Mouse::Button button = (Mouse::Button)lua_tointeger(L, 3);

    pInputSystem->MapMouseButton(input, button);

    return 0;
}

int InputSystem::Script_GetMappedKey(lua_State* L)
{
    InputSystem* pInputSystem = (InputSystem*)lua_tointeger(L, 1);

    string input = lua_tostring(L, 2);

    Keyboard::Key key = pInputSystem->GetMappedKey(input);

    lua_pushinteger(L, key);

    return 1;
}

int InputSystem::Script_GetMappedMouseButton(lua_State* L)
{
    InputSystem* pInputSystem = (InputSystem*)lua_tointeger(L, 1);

    string input = lua_tostring(L, 2);

    Mouse::Button button = pInputSystem->GetMappedMouseButton(input);

    lua_pushinteger(L, button);

    return 1;
}

} // namespace dusk
