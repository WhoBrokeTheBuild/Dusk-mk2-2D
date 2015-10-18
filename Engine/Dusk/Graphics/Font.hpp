#ifndef DUSK_GRAPHICS_FONT_HPP
#define DUSK_GRAPHICS_FONT_HPP

#include <Dusk/Tracking/TrackedObject.hpp>

#include <lua.hpp>
#include <SFML/Graphics/Font.hpp>

namespace dusk
{

class TextBuffer;

class Font :
    public TrackedObject
{

    friend class TextBuffer;

public:

    Font() = default;
    Font(const Font&) = default;
    Font& operator=(const Font&) = default;

    inline Font(const string& filename) { Load(filename); }

    virtual inline string GetClassName() const override { return "Font"; }

    bool Load(const string& filename);

    bool IsLoaded() const { return m_Loaded; }

private:

    inline const sf::Font& GetSFMLFont() const { return m_SfFont; }

    bool m_Loaded = false;

    string m_Filename;

    sf::Font m_SfFont;

public:

    static void Script_RegisterFunctions();
    static int Script_New(lua_State* L);
    static int Script_Delete(lua_State* L);

}; // class Font

} // namespace Dusk

#endif // DUSK_GRAPHICS_FONT_HPP