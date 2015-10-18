#ifndef DUSK_GRAPHICS_CONTEXT_HPP
#define DUSK_GRAPHICS_CONTEXT_HPP

#include <Dusk/Tracking/TrackedObject.hpp>

#include <SFML/Graphics.hpp>

namespace dusk
{

class GraphicsSystem;
class Sprite;
class TextBuffer;

class GraphicsContext :
    public TrackedObject
{

    friend class GraphicsSystem;

public:

    GraphicsContext() = delete;
    GraphicsContext(const GraphicsContext&) = delete;
    GraphicsContext& operator=(const GraphicsContext&) = delete;

    virtual inline string GetClassName() const override { return "Graphics Context"; }

    void Clear();
    void SwapBuffers();

    void Draw(const sf::Drawable& drawable);
    void Draw(Sprite* sprite);
    void Draw(TextBuffer* textBuffer);

    inline sf::RenderWindow& GetSFMLWindow() { return m_SfWindow; }

private:

    inline GraphicsContext(sf::RenderWindow& pSFMLWindow) :
        m_SfWindow(pSFMLWindow)
    { }

    ~GraphicsContext() = default;

    sf::RenderWindow& m_SfWindow;

public:

    static void Script_RegisterFunctions();
    static int Script_Clear(lua_State* L);
    static int Script_Draw(lua_State* L);
    static int Script_SwapBuffers(lua_State* L);

}; // GraphicsContext

} // Dusk

#endif // DUSK_GRAPHICS_CONTEXT_HPP
