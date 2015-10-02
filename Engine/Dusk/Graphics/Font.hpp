#ifndef DUSK_GRAPHICS_FONT_HPP
#define DUSK_GRAPHICS_FONT_HPP

#include <Dusk/Tracking/ITrackedObject.hpp>

#include <lua.hpp>
#include <SFML/Graphics/Font.hpp>

namespace dusk
{

class TextBuffer;

class Font :
    public ITrackedObject
{

    friend class TextBuffer;

public:

    inline Font() :
        m_SfFont()
    { }

    virtual inline ~Font()
    {
        Term();
    }

    virtual inline string GetClassName() const
    {
        return "Font";
    }

    bool Load(const string& filename);
    void Term();

private:

    inline const sf::Font& GetSFMLFont() const
    {
        return m_SfFont;
    }

    string m_Filename;

    sf::Font m_SfFont;

public:

    static void Script_RegisterFunctions();
    static int Script_New(lua_State* L);
    static int Script_Delete(lua_State* L);

}; // class Font

} // namespace Dusk

#endif // DUSK_GRAPHICS_FONT_HPP