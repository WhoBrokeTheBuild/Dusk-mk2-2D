#ifndef DUSK_GRAPHICS_SPRITE_HPP
#define DUSK_GRAPHICS_SPRITE_HPP

#include <Dusk/Tracking/ITrackedObject.hpp>
#include <Dusk/Geometry/Rect.hpp>
#include <Dusk/Geometry/Vector2.hpp>

#include <lua.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace dusk
{

class Texture;
class GraphicsContext;

class Sprite :
	public ITrackedObject
{

	friend class GraphicsContext;

public:

	inline Sprite() :
		mp_Texture(nullptr),
		m_Rect(),
		m_SFMLSprite()
	{ }

	virtual inline ~Sprite() { Term(); }

	virtual inline string GetClassName() const { return "Sprite"; }

	bool Init(Texture* pTexture, IntRect rect = IntRect(0, 0, 0, 0));

	void Term();

	inline Vector2f GetPos() const 
	{
		return m_SFMLSprite.getPosition(); 
	}

	inline void SetPos(const float& x, const float& y) 
	{
		m_SFMLSprite.setPosition(sf::Vector2f(x, y));
	}

private:

	inline const sf::Sprite& GetSFMLSprite() const
	{
		return m_SFMLSprite; 
	}

	Texture* mp_Texture;

	IntRect m_Rect;

	sf::Sprite m_SFMLSprite;

public:

	static void Script_RegisterFunctions();
	static int Script_New(lua_State* L);
	static int Script_Delete(lua_State* L);
	static int Script_GetPos(lua_State* L);
	static int Script_SetPos(lua_State* L);

}; // class Sprite

} // namespace dusk

#endif // DUSK_GRAPHICS_SPRITE_HPP