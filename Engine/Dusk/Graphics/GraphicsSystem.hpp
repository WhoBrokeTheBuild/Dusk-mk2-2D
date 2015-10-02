#ifndef DUSK_GRAPHICS_GRAPHICS_SYSTEM_HPP
#define DUSK_GRAPHICS_GRAPHICS_SYSTEM_HPP

#include <Dusk/Tracking/ITrackedObject.hpp>
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

enum WindowStyle
{
    Fullscreen = 1,
    Resizable  = 2,
    Decorated  = 4,

    Default = Resizable | Decorated
};

class GraphicsSystem :
    public ITrackedObject
{

    friend class Program;

public:

    virtual inline ~GraphicsSystem() { Term(); }

    virtual inline string GetClassName() const
    {
        return "Graphics System";
    }

    bool Init();
    void Term();

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

private:

    GraphicsSystem();

    bool CreateSFMLWindow();

    unsigned int m_Width;
    unsigned int m_Height;
    string m_Title;
    int m_Style;

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
