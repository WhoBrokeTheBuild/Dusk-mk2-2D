#include "TextBuffer.hpp"

#include <Dusk/Graphics/Font.hpp>
#include <Dusk/Scripting/Scripting.hpp>

namespace dusk
{

bool TextBuffer::Init(Font* pFont, const string& text, const unsigned int& size, const Color& color)
{
    if (!pFont)
    {
        return false;
    }

    SetFont(pFont);
    SetText(text);
    SetSize(size);
    SetColor(color);

    return true;
}

void TextBuffer::Term()
{ }

void TextBuffer::SetFont(Font* pFont)
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

void TextBuffer::SetSize(const unsigned int& size)
{
    m_Size = size;
    m_SfText.setCharacterSize(size);
}

void TextBuffer::SetColor(const Color& color)
{
    m_Color = color;
    m_SfText.setColor(color);
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

    TextBuffer* pTextBuffer = New TextBuffer();
    pTextBuffer->Init(pFont, text, size, Color::White); // TODO: Add Colors

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