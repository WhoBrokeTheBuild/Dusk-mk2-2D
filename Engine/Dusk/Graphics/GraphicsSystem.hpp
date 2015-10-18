#ifndef DUSK_GRAPHICS_GRAPHICS_SYSTEM_HPP
#define DUSK_GRAPHICS_GRAPHICS_SYSTEM_HPP

#include <Dusk/Tracking/TrackedObject.hpp>
#include <Dusk/Events/EventDispatcher.hpp>
#include <Dusk/Utility/Types.hpp>
#include <Dusk/Events/Event.hpp>
#include <Dusk/Geometry/Vector2.hpp>
#include <Dusk/Graphics/GraphicsContext.hpp>

#include <lua.hpp>
#include <SFML/Graphics.hpp>

namespace dusk
{

class Program;
class Window;

class GraphicsSystem :
    public TrackedObject,
    public EventDispatcher
{

    friend class Program;

public:

    enum WindowStyle : uint8_t
    {
        Fullscreen = 1,
        Resizable = 2,
        Decorated = 4,

        Default = Resizable | Decorated
    };

    enum : EventID
    {
        EvtWindowResize = 1,
    };

    GraphicsSystem(const GraphicsSystem&) = delete;
    GraphicsSystem& operator=(const GraphicsSystem&) = delete;

    virtual ~GraphicsSystem() = default;

    virtual inline string GetClassName() const override { return "Graphics System"; }

    bool CreateWindow();

    void OnUpdate(const Event& evt);

    inline unsigned int GetWindowWidth() const { return m_Width; }
    inline unsigned int GetWindowHeight() const { return m_Height; }
    Vector2u GetWindowSize() const;

    void SetWindowWidth(const unsigned int& width);
    void SetWindowHeight(const unsigned int& height);
    void SetWindowSize(const unsigned int& width, const unsigned int& height);

    void SetWindowStyle(const int& styleFlags);

    void ApplyWindowChanges();

    inline string GetWindowTitle() const { return m_Title; }
    void SetWindowTitle(const string& title);

    bool IsFullscreen() const;
    bool IsDecorated() const;
    bool IsResizable() const;

    GraphicsContext* GetContext() const;

    sf::WindowHandle GetWindowHandle() const { return m_SfWindow.getSystemHandle(); }

private:

    GraphicsSystem() :
        mp_GraphicsContext(nullptr)
    { }

    bool CreateSFMLWindow();

    unsigned int m_Width = 1024;

    unsigned int m_Height = 768;

    string m_Title = "Dusk";

    int m_Style = WindowStyle::Default;

    sf::RenderWindow m_SfWindow;

    unique_ptr<GraphicsContext> mp_GraphicsContext;

public:

    static void Script_RegisterFunctions();
    static int Script_Get(lua_State* L);
    static int Script_GetContext(lua_State* L);
    static int Script_GetWindowSize(lua_State* L);
    static int Script_GetWindowTitle(lua_State* L);
    static int Script_SetWindowTitle(lua_State* L);

}; // class GraphicsSystem

class WindowResizeEventData :
    public EventData
{
public:

    WindowResizeEventData(const unsigned int& width, const unsigned int& height) :
        m_Width(width),
        m_Height(height)
    { }

    virtual inline string GetClassName() const
    {
        return "Window Resize Event Data";
    }

    virtual inline EventData* Clone() const
    {
        return New WindowResizeEventData(m_Width, m_Height);
    }

    inline unsigned int GetWidth() const { return m_Width; }
    inline unsigned int GetHeight() const { return m_Height; }
    inline Vector2u GetSize() const { return Vector2u(m_Width, m_Height); }

    virtual int PushDataToLua(lua_State* L) const;

private:

    unsigned int m_Width;
    unsigned int m_Height;

}; // class UpdateEventData

} // namespace dusk

#endif // DUSK_GRAPHICS_GRAPHICS_SYSTEM_HPP
