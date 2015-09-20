#ifndef DUSK_GRAPHICS_WINDOW_HPP
#define DUSK_GRAPHICS_WINDOW_HPP

#include <Tracking/ITrackedObject.hpp>
#include <Utility/Types.hpp>
#include <Events/Event.hpp>

#include <lua.hpp>
#include <SFML/Graphics.hpp>

namespace dusk
{

class GraphicsContext;

class Window :
	public ITrackedObject
{
public:

	static const Flag FULLSCREEN = 1;
	static const Flag RESIZABLE  = 2;
	static const Flag DECORATED  = 4;

	inline Window( void ) :
		m_SFMLWindow(),
		mp_GraphicsContext(nullptr),
		m_Title(),
		m_Fullscreen(false),
		m_Decorated(false),
		m_Resizable(false)
	{ }

	~Window() { Term(); }

	virtual inline string GetClassName( void ) const { return "Window"; }

	bool Init(const unsigned int& width, const unsigned int& height, const string& title, const Flag& flags);
	void Term();

	void OnUpdate(const Event& event);

	string GetTitle() const;
	void SetTitle(const string& title);

	unsigned int GetWidth() const;
	unsigned int GetHeight() const;

	inline bool IsFullscreen() const { return m_Fullscreen; }
	inline bool IsDecorated() const { return m_Decorated; }
	inline bool IsResizable() const { return m_Resizable; }

	GraphicsContext* GetGraphicsContext() const;

	static void InitScripting();
	static int Script_GetWidth(lua_State* L);
	static int Script_GetHeight(lua_State* L);
	static int Script_GetTitle(lua_State* L);
	static int Script_SetTitle(lua_State* L);

private:

	bool CreateSFMLWindow(const unsigned int& width, const unsigned int& height);

	sf::RenderWindow m_SFMLWindow;

	GraphicsContext* mp_GraphicsContext;

	string m_Title;

	bool m_Fullscreen;
	
	bool m_Decorated;
	
	bool m_Resizable;

}; // class Window

} // namespace dusk

#endif // DUSK_GRAPHICS_WINDOW_HPP