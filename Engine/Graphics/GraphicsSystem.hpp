#ifndef DUSK_GRAPHICS_GRAPHICS_SYSTEM_HPP
#define DUSK_GRAPHICS_GRAPHICS_SYSTEM_HPP

#include <Tracking/ITrackedObject.hpp>

#include <lua.hpp>

namespace Dusk
{

class Window;

class GraphicsSystem :
	public ITrackedObject
{
public:

	GraphicsSystem() :
		mp_Window(nullptr)
	{ }

	~GraphicsSystem() { Term(); }

	virtual inline string GetClassName() const { return "Graphics System"; }

	bool Init();
	void Term();

	Window* GetWindow() const;

	static void InitScripting();
	static int Script_GetWindow(lua_State* L);

private:

	Window*			mp_Window;

}; // class GraphicsSystem

} // namespace Dusk

#endif // DUSK_GRAPHICS_GRAPHICS_SYSTEM_HPP