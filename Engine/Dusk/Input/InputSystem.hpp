#ifndef DUSK_INPUT_INPUT_SYSTEM_HPP
#define DUSK_INPUT_INPUT_SYSTEM_HPP

#include <Dusk/Tracking/TrackedObject.hpp>
#include <Dusk/Events/EventDispatcher.hpp>
#include <Dusk/Input/Keyboard.hpp>
#include <Dusk/Input/Mouse.hpp>
#include <Dusk/Input/Mapped.hpp>

#include <lua.hpp>

namespace dusk
{

class Program;

class InputSystem :
    public EventDispatcher,
    public TrackedObject
{

    friend class Program;

public:

    enum : EventID
    {
        EvtKeyPress,
        EvtKeyRelease,

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

    void TriggerMouseMoveRelative(const double& dx, const double& dy);
    void TriggerMouseMoveAbsolute(const double& x, const double& y);
    void TriggerMouseScroll(const double& dx, const double& dy);
    void TriggerMouseButtonPress(const Mouse::Button& mouseButton);
    void TriggerMouseButtonRelease(const Mouse::Button& mouseButton);

    void TriggerMappedInputPress(const MappedInputID& input);
    void TriggerMappedInputRelease(const MappedInputID& input);

private:

    InputSystem() = default;

    double m_MouseX = 0.0;

    double m_MouseY = 0.0;

    Map<Keyboard::Key, MappedInputID> m_MappedKeys;

    Map<Mouse::Button, MappedInputID> m_MappedMouseButtons;

public:

    static void InitScripting();
    static int Script_Get(lua_State* L);
    static int Script_MapKey(lua_State* L);
    static int Script_MapMouseButton(lua_State* L);
    static int Script_GetMappedKey(lua_State* L);
    static int Script_GetMappedMouseButton(lua_State* L);

}; // class InputSystem

} // namespace dusk

#endif // DUSK_INPUT_INPUT_SYSTEM_HPP