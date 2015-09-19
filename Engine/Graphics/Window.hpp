#ifndef DUSK_GRAPHICS_WINDOW_HPP
#define DUSK_GRAPHICS_WINDOW_HPP

#include <Tracking/ITrackedObject.hpp>
#include <Utility/Types.hpp>
#include <Events/Event.hpp>

#include <lua.hpp>
#include <SFML/Window.hpp>

namespace Dusk
{

class Window :
	public ITrackedObject
{
public:

	static const Flag FULLSCREEN = 1;
	static const Flag RESIZABLE  = 2;
	static const Flag DECORATED  = 4;

	inline Window( void ) :
		m_Fullscreen(false),
		m_Decorated(false),
		m_Resizable(false)
	{ }

	~Window( void ) { Term(); }

	virtual inline string GetClassName( void ) const { return "Window"; }

	bool Init( const unsigned int& width, const unsigned int& height, const string& title, const Flag& flags );
	void Term( void );

	void Update(const Event& event);

	string GetTitle( void ) const;
	void SetTitle( const string& title );

	void SetSize( const unsigned int& width, const unsigned int& height );

	unsigned int GetWidth( void ) const;
	void SetWidth( const unsigned int& width );

	unsigned int GetHeight( void ) const;
	void SetHeight( const unsigned int& height );

	inline bool IsFullscreen( void ) const { return m_Fullscreen; }
	inline bool IsDecorated( void ) const { return m_Decorated; }
	inline bool IsResizable ( void ) const { return m_Resizable; }

	static void InitScripting( void );
	static int Script_SetSize  ( lua_State* L );
	static int Script_GetWidth ( lua_State* L );
	static int Script_GetHeight( lua_State* L );
	static int Script_SetWidth ( lua_State* L );
	static int Script_SetHeight( lua_State* L );
	static int Script_GetTitle ( lua_State* L );
	static int Script_SetTitle ( lua_State* L );

private:

	bool CreateSFMLWindow( const unsigned int& width, const unsigned int& height );

	sf::Window		*mp_SFMLWindow;

	string			m_Title;

	bool			m_Fullscreen,
					m_Decorated,
					m_Resizable;

}; // class Window

} // namespace Dusk

#endif // DUSK_GRAPHICS_WINDOW_HPP