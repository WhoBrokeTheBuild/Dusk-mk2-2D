#ifndef DUSK_INPUT_MOUSE_BUTTON_HPP
#define DUSK_INPUT_MOUSE_BUTTON_HPP

#include <Dusk/Events/Event.hpp>

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

    MouseButtonEventData(const Mouse::Button& button) :
        m_MouseButton(button)
    { }

    virtual inline string GetClassName() const
    {
        return "Mouse Button Event Data";
    }

    virtual inline EventData* Clone() const
    {
        return New MouseButtonEventData(m_MouseButton);
    }

    inline Mouse::Button GetMouseButton() const
    {
        return m_MouseButton;
    }

    virtual int PushDataToLua(lua_State* L) const;

private:

    Mouse::Button        m_MouseButton;

}; // class MouseButtonEventData

class MouseMoveEventData :
    public EventData
{
public:

    MouseMoveEventData() :
        m_MouseX(0),
        m_MouseY(0),
        m_DeltaX(0),
        m_DeltaY(0)
    { }

    MouseMoveEventData(const double& x, const double& y, const double& dx, const double& dy) :
        m_MouseX(x),
        m_MouseY(y),
        m_DeltaX(dx),
        m_DeltaY(dy)
    { }

    virtual inline string GetClassName() const
    {
        return "Mouse Move Event Data";
    }

    virtual inline EventData* Clone() const
    {
        return New MouseMoveEventData(m_MouseX, m_MouseY, m_DeltaX, m_DeltaY);
    }

    inline double GetX() const
    {
        return m_MouseX;
    }
    inline double GetY() const
    {
        return m_MouseY;
    }
    inline double GetDeltaX() const
    {
        return m_DeltaX;
    }
    inline double GetDeltaY() const
    {
        return m_DeltaY;
    }

    virtual int PushDataToLua(lua_State* L) const;

private:

    double    m_MouseX,
        m_MouseY,
        m_DeltaX,
        m_DeltaY;

}; // class MouseMoveEventData

class MouseScrollEventData :
    public EventData
{
public:

    MouseScrollEventData() :
        m_ScrollX(0),
        m_ScrollY(0)
    { }

    MouseScrollEventData(const double& x, const double& y) :
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

    double m_ScrollX,
        m_ScrollY;

}; // class MouseScrollEventData

} // namespace dusk

#endif // DUSK_INPUT_MOUSE_BUTTON_HPP