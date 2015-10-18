#ifndef DUSK_GRAPHICS_TEXT_BUFFER_HPP
#define DUSK_GRAPHICS_TEXT_BUFFER_HPP

#include <Dusk/Tracking/TrackedObject.hpp>
#include <Dusk/Graphics/Color.hpp>
#include <Dusk/Geometry/Vector2.hpp>

#include <lua.hpp>
#include <SFML/Graphics/Text.hpp>

namespace dusk
{

class Font;

class TextBuffer :
    public TrackedObject
{

    friend class GraphicsContext;

public:

    TextBuffer() = default;
    TextBuffer(const TextBuffer&) = default;
    TextBuffer& operator=(const TextBuffer&) = default;
    ~TextBuffer() = default;

    TextBuffer(const Font* pFont, const string& text, const unsigned int& fontSize, const Color& color)
    {
        SetFont(pFont);
        SetText(text);
        SetFontSize(fontSize);
        SetColor(color);
    }

    virtual inline string GetClassName() const override { return "Text Buffer"; }

    void SetFont(const Font* pFont);

    inline string GetText() const { return m_Text; }
    void SetText(const string& text);

    inline unsigned int GetFontSize() const { return m_FontSize; }
    void SetFontSize(const unsigned int& fontSize);

    inline Color GetColor() const { return m_Color; }
    void SetColor(const Color& color);

    Vector2f GetPos() const;
    void SetPos(const Vector2f& pos);

    Vector2f GetSize() const;

    inline const sf::Text& GetSFMLText() const { return m_SfText; }

private:

    const Font* mp_Font;

    string m_Text;

    unsigned int m_FontSize = 12;

    Color m_Color = Color::Black;

    sf::Text m_SfText;

public:

    static void Script_RegisterFunctions();
    static int Script_New(lua_State* L);
    static int Script_Delete(lua_State* L);

}; // class TextBuffer

} // namespace dusk

#endif // DUSK_GRAPHICS_TEXT_BUFFER_HPP