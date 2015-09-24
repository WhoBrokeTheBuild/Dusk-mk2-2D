#ifndef DUSK_GRAPHICS_CONTEXT_HPP
#define DUSK_GRAPHICS_CONTEXT_HPP

#include <Dusk/Tracking/ITrackedObject.hpp>

#include <SFML/Graphics.hpp>

namespace dusk
{

class GraphicsSystem;
class Sprite;
class TextBuffer;

class GraphicsContext :
    public ITrackedObject
{

    friend class GraphicsSystem;

public:

    virtual inline string GetClassName() const
    {
        return "Graphics Context";
    }

    void Clear();
    void SwapBuffers();

    void Draw(Sprite* sprite);
    void Draw(TextBuffer* textBuffer);

    static void Script_RegisterFunctions();
    static int Script_Clear(lua_State* L);
    static int Script_Draw(lua_State* L);
    static int Script_SwapBuffers(lua_State* L);

private:

    inline GraphicsContext(sf::RenderWindow& pSFMLWindow) :
        m_SFMLWindow(pSFMLWindow)
    { }

    virtual inline ~GraphicsContext()
    { }

    sf::RenderWindow& m_SFMLWindow;

}; // GraphicsContext

} // Dusk

#endif // DUSK_GRAPHICS_CONTEXT_HPP
