#ifndef DUSK_GRAPHICS_GRAPHICS_SYSTEM_HPP
#define DUSK_GRAPHICS_GRAPHICS_SYSTEM_HPP

#include <Dusk/Tracking/ITrackedObject.hpp>
#include <Dusk/Utility/Singleton.hpp>
#include <Dusk/Utility/Types.hpp>
#include <Dusk/Events/Event.hpp>
#include <Dusk/Geometry/Vector2.hpp>

#include <lua.hpp>
#include <SFML/Graphics.hpp>

namespace dusk
{

class Program;
class Window;
class GraphicsContext;

class GraphicsSystem :
    public ITrackedObject
{

    DUSK_SINGLETON(GraphicsSystem);

    friend class Program;

public:

    static Flag Fullscreen;
    static Flag Resizable;
    static Flag Decorated;

    virtual inline string GetClassName() const
    {
        return "Graphics System";
    }

    bool Init(const unsigned int& width, const unsigned int& height, const string& title, const Flag& flags);
    void Term();

    void OnUpdate(const Event& evt);

    Vector2u GetWindowSize() const;

    inline string GetWindowTitle() const
    {
        return m_Title;
    }
    void SetWindowTitle(const string& title);

    inline bool IsFullscreen() const
    {
        return m_Fullscreen;
    }
    inline bool IsDecorated() const
    {
        return m_Decorated;
    }
    inline bool IsResizable() const
    {
        return m_Resizable;
    }

    GraphicsContext* GetContext() const;

private:

    GraphicsSystem();

    virtual ~GraphicsSystem()
    {
        Term();
    }

    bool CreateSFMLWindow(const unsigned int& width, const unsigned int& height);

    string m_Title;

    bool m_Fullscreen;
    bool m_Decorated;
    bool m_Resizable;

    sf::RenderWindow m_SFMLWindow;

    GraphicsContext* mp_GraphicsContext;

public:

    static void Script_RegisterFunctions();
    static int Script_Get(lua_State* L);
    static int Script_GetContext(lua_State* L);
    static int Script_GetWindowSize(lua_State* L);
    static int Script_GetWindowTitle(lua_State* L);
    static int Script_SetWindowTitle(lua_State* L);

}; // class GraphicsSystem

} // namespace dusk

#endif // DUSK_GRAPHICS_GRAPHICS_SYSTEM_HPP
