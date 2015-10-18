#ifndef DUSK_GRAPHICS_TEXTURE_HPP
#define DUSK_GRAPHICS_TEXTURE_HPP

#include <Dusk/Tracking/TrackedObject.hpp>
#include <Dusk/Utility/Types.hpp>

#include <lua.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace dusk
{

class Sprite;

class Texture :
    public TrackedObject
{

    friend class Sprite;

public:

    Texture() = default;
    Texture(const Texture&) = default;
    Texture& operator=(const Texture&) = default;

    inline Texture(const string& filename) { Load(filename); }

    virtual inline string GetClassName() const override { return "Texture"; }

    bool Load(const string& filename);

    bool IsLoaded() const { return m_Loaded; }

protected:

    inline const sf::Texture& GetSFMLTexture() const { return m_SfTexture; }

private:

    bool m_Loaded = false;

    sf::Texture m_SfTexture;

public:

    static void Script_RegisterFunctions();
    static int Script_New(lua_State* L);
    static int Script_Delete(lua_State* L);

}; // class Texture

} // namespace dusk

#endif // DUSK_GRAPHICS_TEXTURE_HPP