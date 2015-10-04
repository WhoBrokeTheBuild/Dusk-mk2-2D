#ifndef DUSK_GRAPHICS_TEXT_BUFFER_HPP
#define DUSK_GRAPHICS_TEXT_BUFFER_HPP

#include <Dusk/Tracking/ITrackedObject.hpp>
#include <Dusk/Graphics/Color.hpp>
#include <Dusk/Geometry/Vector2.hpp>

#include <lua.hpp>
#include <SFML/Graphics/Text.hpp>

namespace dusk
{

class Font;

class TextBuffer :
    public ITrackedObject
{

    friend class GraphicsContext;

public:

    inline TextBuffer() :
        mp_Font(nullptr),
        m_Text(),
        m_FontSize(),
        m_Color(),
        m_SfText()
    { }

    virtual inline ~TextBuffer() { Term(); }

    virtual inline string GetClassName() const { return "Text Buffer"; }

    bool Init(Font* pFont, const string& text, const unsigned int& fontSize, const Color& color);
    void Term();

    void SetFont(Font* pFont);

    inline string GetText() const { return m_Text; }
    void SetText(const string& text);

    inline unsigned int GetFontSize() const { return m_FontSize; }
    void SetFontSize(const unsigned int& fontSize);

    inline Color GetColor() const { return m_Color; }
    void SetColor(const Color& color);

    void SetPos(const Vector2f& pos);

    Vector2f GetPos() const;
    Vector2f GetSize() const;

    inline const sf::Text& GetSFMLText() const { return m_SfText; }

private:

    Font* mp_Font;

    string m_Text;

    unsigned int m_FontSize;

    Color m_Color;

    sf::Text m_SfText;

public:

    static void Script_RegisterFunctions();
    static int Script_New(lua_State* L);
    static int Script_Delete(lua_State* L);

}; // class TextBuffer

} // namespace dusk

#endif // DUSK_GRAPHICS_TEXT_BUFFER_HPP