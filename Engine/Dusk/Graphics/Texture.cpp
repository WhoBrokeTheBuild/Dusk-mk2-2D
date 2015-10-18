#include "Texture.hpp"

#include <Dusk/Logging/Logging.hpp>
#include <Dusk/Scripting/Scripting.hpp>
#include <Dusk/Utility/Benchmark.hpp>

#include <SFML/Graphics/Texture.hpp>

namespace dusk
{

bool Texture::Load(const string& filename)
{
    DuskExtLog("verbose", "Loading texture %s", filename.c_str());
    DuskBenchStart();

    if (!m_SfTexture.loadFromFile(filename))
    {
        DuskExtLog("error", "Failed to load texture %s", filename.c_str());
        return false;
    }

    DuskBenchEnd("Texture::Init");
    return true;
}

void Texture::Script_RegisterFunctions()
{
    Scripting::RegisterFunction("dusk_texture_new", &Texture::Script_New);
    Scripting::RegisterFunction("dusk_texture_delete", &Texture::Script_Delete);
}

int Texture::Script_New(lua_State* L)
{
    string filename = lua_tostring(L, 1);

    Texture* pTexture = New Texture();
    pTexture->Load(filename);

    lua_pushinteger(L, (ptrdiff_t)pTexture);

    return 1;
}

int Texture::Script_Delete(lua_State* L)
{
    Texture* pTexture = (Texture*)lua_tointeger(L, 1);
    delete pTexture;

    return 0;
}

} // namespace dusk
