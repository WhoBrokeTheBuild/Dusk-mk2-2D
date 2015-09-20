#ifndef DUSK_GRAPHICS_CONTEXT_HPP
#define DUSK_GRAPHICS_CONTEXT_HPP

#include <Tracking/ITrackedObject.hpp>

#include <SFML/Graphics.hpp>

namespace dusk
{

class Window;
class Sprite;

class GraphicsContext :
	public ITrackedObject
{

	friend class Window;

public:

	virtual inline string GetClassName() const { return "Graphics Context"; }

	void Clear();
	void SwapBuffers();

	void Draw(Sprite* sprite);
	
	static void InitScripting();
	static int Script_Clear(lua_State* L);
	static int Script_Draw(lua_State* L);
	static int Script_SwapBuffers(lua_State* L);

private:

	inline GraphicsContext( sf::RenderWindow& pSFMLWindow ) :
		m_SFMLWindow(pSFMLWindow)
	{ }

	sf::RenderWindow& m_SFMLWindow;

}; // GraphicsContext

} // Dusk

#endif // DUSK_GRAPHICS_CONTEXT_HPP
