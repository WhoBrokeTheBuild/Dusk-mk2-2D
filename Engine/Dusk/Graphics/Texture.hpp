#ifndef DUSK_GRAPHICS_TEXTURE_HPP
#define DUSK_GRAPHICS_TEXTURE_HPP

#include <Dusk/Tracking/ITrackedObject.hpp>
#include <Dusk/Utility/Types.hpp>

#include <lua.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace dusk
{

class Sprite;

class Texture :
    public ITrackedObject
{

    friend class Sprite;

public:

    inline Texture() :
        m_SfTexture()
    { }

    virtual inline ~Texture()
    {
        Term();
    }

    virtual inline string GetClassName() const
    {
        return "Texture";
    }

    bool Load(const string& filename);

    void Term();

    static void Script_RegisterFunctions();
    static int Script_New(lua_State* L);
    static int Script_Delete(lua_State* L);

private:

    inline const sf::Texture& GetSFMLTexture() const
    {
        return m_SfTexture;
    }

    sf::Texture m_SfTexture;

}; // class Texture

} // namespace dusk

#endif // DUSK_GRAPHICS_TEXTURE_HPP