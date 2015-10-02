#include "Sprite.hpp"

#include <Dusk/Scripting/Scripting.hpp>
#include <Dusk/Graphics/GraphicsContext.hpp>
#include <Dusk/Graphics/Texture.hpp>
#include <Dusk/Logging/Logging.hpp>

namespace dusk
{

bool Sprite::Init(Texture* pTexture, IntRect rect /*= IntRect(0, 0, 0, 0)*/)
{
    mp_Texture = pTexture;
    m_SfSprite.setTexture(pTexture->GetSFMLTexture());

    if (rect != IntRect(0, 0, 0, 0))
    {
        m_SfSprite.setTextureRect(rect);
    }

    return true;
}

void Sprite::Term()
{ }

void Sprite::Script_RegisterFunctions()
{
    Scripting::RegisterFunction("dusk_sprite_new", &Sprite::Script_New);
    Scripting::RegisterFunction("dusk_sprite_delete", &Sprite::Script_Delete);
    Scripting::RegisterFunction("dusk_sprite_get_pos", &Sprite::Script_GetPos);
    Scripting::RegisterFunction("dusk_sprite_set_pos", &Sprite::Script_SetPos);
}

int Sprite::Script_New(lua_State* L)
{
    Texture* pTexture = (Texture*)lua_tointeger(L, 1);

    Sprite* pSprite = New Sprite();
    pSprite->Init(pTexture);

    lua_pushinteger(L, (ptrdiff_t)pSprite);

    return 1;
}

int Sprite::Script_Delete(lua_State* L)
{
    Sprite* pSprite = (Sprite*)lua_tointeger(L, 1);
    delete pSprite;

    return 0;
}

int Sprite::Script_GetPos(lua_State* L)
{
    Sprite* pSprite = (Sprite*)lua_tointeger(L, 1);
    sf::Vector2f pos = pSprite->GetPos();
    lua_pushnumber(L, pos.x);
    lua_pushnumber(L, pos.y);

    return 2;
}

int Sprite::Script_SetPos(lua_State* L)
{
    Sprite* pSprite = (Sprite*)lua_tointeger(L, 1);
    float x = (float)lua_tonumber(L, 2);
    float y = (float)lua_tonumber(L, 3);
    pSprite->SetPos(x, y);

    return 0;
}

} // namespace dusk
