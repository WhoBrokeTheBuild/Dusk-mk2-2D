#include "TextBuffer.hpp"

#include <Dusk/Graphics/Font.hpp>
#include <Dusk/Scripting/Scripting.hpp>
#include <Dusk/Geometry/Rect.hpp>

namespace dusk
{

void TextBuffer::SetFont(const Font* pFont)
{
    mp_Font = pFont;
    if (mp_Font)
    {
        m_SfText.setFont(mp_Font->GetSFMLFont());
    }
}

void TextBuffer::SetText(const string& text)
{
    m_Text = text;
    m_SfText.setString(m_Text);
}

void TextBuffer::SetFontSize(const unsigned int& fontSize)
{
    m_FontSize = fontSize;
    m_SfText.setCharacterSize(fontSize);
}

void TextBuffer::SetColor(const Color& color)
{
    m_Color = color;
    m_SfText.setColor(color);
}

void TextBuffer::SetPos(const Vector2f& pos)
{
    m_SfText.setPosition(pos);
}

Vector2f TextBuffer::GetPos() const
{
    return m_SfText.getPosition();
}

Vector2f TextBuffer::GetSize() const
{
    FloatRect bounds = m_SfText.getLocalBounds();
    return Vector2f(bounds.left + bounds.left + bounds.width, bounds.top + bounds.top + bounds.height);
}

void TextBuffer::Script_RegisterFunctions()
{
    Scripting::RegisterFunction("dusk_text_buffer_new", &TextBuffer::Script_New);
    Scripting::RegisterFunction("dusk_text_buffer_delete", &TextBuffer::Script_Delete);
}

int TextBuffer::Script_New(lua_State* L)
{
    Font* pFont = (Font*)lua_tointeger(L, 1);
    string text = lua_tostring(L, 2);
    unsigned int size = (unsigned int)lua_tointeger(L, 3);

    TextBuffer* pTextBuffer = New TextBuffer(pFont, text, size, Color::White); // TODO: Add Colors

    lua_pushinteger(L, (ptrdiff_t)pTextBuffer);

    return 1;
}

int TextBuffer::Script_Delete(lua_State* L)
{
    TextBuffer* pTextBuffer = (TextBuffer*)lua_tointeger(L, 1);
    delete pTextBuffer;

    return 0;
}

} // namespace dusk