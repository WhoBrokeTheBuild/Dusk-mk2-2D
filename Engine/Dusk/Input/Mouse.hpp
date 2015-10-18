#ifndef DUSK_INPUT_MOUSE_BUTTON_HPP
#define DUSK_INPUT_MOUSE_BUTTON_HPP

#include <Dusk/Events/Event.hpp>
#include <Dusk/Geometry/Vector2.hpp>

#include <SFML/Window/Mouse.hpp>

namespace dusk
{

class Mouse
{
public:

    enum Button
    {
        Invalid = -1,

        Left = 1,
        Middle = 2,
        Right = 3,
        Extra1 = 4,
        Extra2 = 5,

    }; // enum MouseButton

    static Button ConvertSFMLMouseButton(sf::Mouse::Button button);

}; // class Mouse

class MouseButtonEventData :
    public EventData
{
public:

    MouseButtonEventData() :
        m_MouseButton(Mouse::Button::Invalid)
    { }

    MouseButtonEventData(const Mouse::Button& button, const float& x, const float& y) :
        m_MouseButton(button),
        m_MousePos(x, y)
    { }

    virtual inline string GetClassName() const override { return "Mouse Button Event Data"; }

    virtual inline EventData* Clone() const
    {
        return New MouseButtonEventData(m_MouseButton, m_MousePos.x, m_MousePos.y);
    }

    inline Mouse::Button GetMouseButton() const { return m_MouseButton; }

    inline float GetMouseX() const { return m_MousePos.x; }
    inline float GetMouseY() const { return m_MousePos.y; }
    inline Vector2f GetMousePos() const { return m_MousePos; }

    virtual int PushDataToLua(lua_State* L) const;

private:

    Mouse::Button m_MouseButton;

    Vector2f m_MousePos;

}; // class MouseButtonEventData

class MouseMoveEventData :
    public EventData
{
public:

    MouseMoveEventData() = default;
    MouseMoveEventData(const MouseMoveEventData&) = default;
    MouseMoveEventData(const float& x, const float& y, const float& dx, const float& dy) :
        m_MousePos(x, y),
        m_MouseDelta(dx, dy)
    { }

    virtual inline string GetClassName() const
    {
        return "Mouse Move Event Data";
    }

    virtual inline EventData* Clone() const
    {
        return New MouseMoveEventData(m_MousePos.x, m_MousePos.y, m_MouseDelta.x, m_MouseDelta.y);
    }

    inline double GetX() const { return m_MousePos.x; }
    inline double GetY() const { return m_MousePos.y; }
    inline double GetDeltaX() const { return m_MouseDelta.x; }
    inline double GetDeltaY() const { return m_MouseDelta.y; }

    inline Vector2f GetPos() const { return m_MousePos; }
    inline Vector2f GetDelta() const { return m_MouseDelta; }

    virtual int PushDataToLua(lua_State* L) const;

private:

    Vector2f m_MousePos;
    Vector2f m_MouseDelta;

}; // class MouseMoveEventData

class MouseScrollEventData :
    public EventData
{
public:

    MouseScrollEventData() :
        m_ScrollX(0),
        m_ScrollY(0)
    { }

    MouseScrollEventData(const float& x, const float& y) :
        m_ScrollX(x),
        m_ScrollY(y)
    { }

    virtual inline string GetClassName() const
    {
        return "Mouse Scroll Event Data";
    }

    virtual inline EventData* Clone() const
    {
        return New MouseScrollEventData(m_ScrollX, m_ScrollY);
    }

    inline double GetScrollX() const
    {
        return m_ScrollX;
    }
    inline double GetScrollY() const
    {
        return m_ScrollY;
    }

    virtual int PushDataToLua(lua_State* L) const;

private:

    float m_ScrollX;
    float m_ScrollY;

}; // class MouseScrollEventData

} // namespace dusk

#endif // DUSK_INPUT_MOUSE_BUTTON_HPP