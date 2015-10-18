#include "Font.hpp"

#include <Dusk/Graphics/TextBuffer.hpp>
#include <Dusk/Scripting/Scripting.hpp>

namespace dusk
{

bool Font::Load(const string& filename)
{
    m_Filename = filename;
    m_Loaded = m_SfFont.loadFromFile(filename);
    return m_Loaded;
}

void Font::Script_RegisterFunctions()
{
    Scripting::RegisterFunction("dusk_font_new", &Font::Script_New);
    Scripting::RegisterFunction("dusk_font_delete", &Font::Script_Delete);
}

int Font::Script_New(lua_State* L)
{
    string filename = lua_tostring(L, 1);

    Font* pFont = New Font();
    pFont->Load(filename);

    lua_pushinteger(L, (ptrdiff_t)pFont);

    return 1;
}

int Font::Script_Delete(lua_State* L)
{
    Font* pFont = (Font*)lua_tointeger(L, 1);
    delete pFont;

    return 0;
}

} // namespace dusk