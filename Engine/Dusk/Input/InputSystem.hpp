#ifndef DUSK_INPUT_INPUT_SYSTEM_HPP
#define DUSK_INPUT_INPUT_SYSTEM_HPP

#include <Dusk/Tracking/TrackedObject.hpp>
#include <Dusk/Events/EventDispatcher.hpp>
#include <Dusk/Input/Keyboard.hpp>
#include <Dusk/Input/Mouse.hpp>
#include <Dusk/Input/Mapped.hpp>

#include <lua.hpp>
#include <SFML/Window/Event.hpp>

namespace dusk
{

class Program;
class GraphicsSystem;

class InputSystem :
    public EventDispatcher,
    public TrackedObject
{

    friend class Program;
    friend class GraphicsSystem;

public:

    enum : EventID
    {
        EvtKeyPress = 1,
        EvtKeyRelease,

        EvtTextInput,

        EvtMouseMove,
        EvtMouseScroll,
        EvtMouseButtonPress,
        EvtMouseButtonRelease,

        EvtMappedInputPress,
        EvtMappedInputRelease,
    };

    InputSystem(const InputSystem&) = delete;
    InputSystem& operator=(const InputSystem&) = delete;

    virtual ~InputSystem() = default;

    virtual inline string GetClassName() const { return "Input System"; }

    void MapKey(const MappedInputID& id, const Keyboard::Key& key);
    void MapMouseButton(const MappedInputID& id, const Mouse::Button& button);

    Keyboard::Key GetMappedKey(const MappedInputID& id);
    Mouse::Button GetMappedMouseButton(const MappedInputID& id);

    void TriggerKeyPress(const Keyboard::Key& key);
    void TriggerKeyRelease(const Keyboard::Key& key);

    void TriggerTextInput(const char32_t& input);

    void TriggerMouseMoveRelative(const float& dx, const float& dy);
    void TriggerMouseMoveAbsolute(const float& x, const float& y);
    void TriggerMouseScroll(const float& dx, const float& dy);
    void TriggerMouseButtonPress(const Mouse::Button& mouseButton);
    void TriggerMouseButtonRelease(const Mouse::Button& mouseButton);

    void TriggerMappedInputPress(const MappedInputID& input);
    void TriggerMappedInputRelease(const MappedInputID& input);

private:

    InputSystem() = default;

    void ProcessSfEvent(const sf::Event& sfEvent);

    float m_MouseX = 0.0;

    float m_MouseY = 0.0;

    Map<Keyboard::Key, MappedInputID> m_MappedKeys;

    Map<Mouse::Button, MappedInputID> m_MappedMouseButtons;

public:

    static void Script_RegisterFunctions();
    static int Script_Get(lua_State* L);
    static int Script_MapKey(lua_State* L);
    static int Script_MapMouseButton(lua_State* L);
    static int Script_GetMappedKey(lua_State* L);
    static int Script_GetMappedMouseButton(lua_State* L);

}; // class InputSystem

} // namespace dusk

#endif // DUSK_INPUT_INPUT_SYSTEM_HPP