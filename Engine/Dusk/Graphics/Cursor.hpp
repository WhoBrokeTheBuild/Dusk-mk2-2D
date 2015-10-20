#ifndef DUSK_GRAPHICS_CURSOR_HPP
#define DUSK_GRAPHICS_CURSOR_HPP

#include <Dusk/Utility/Platform.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#ifdef DUSK_OS_WINDOWS
#include <windows.h>
#elif defined(DUSK_OS_LINUX)
#include <X11/cursorfont.h>
#include <X11/Xlib.h>
#else
#error This OS is not yet supported by the cursor library.
#endif

namespace dusk
{

class Cursor
{
private:
#ifdef DUSK_OS_WINDOWS

    HCURSOR CursorType; /*Type of the Cursor with Windows*/

#else

    XID CursorType;
    Display* display;

#endif
public:
    enum TYPE { WAIT, TEXT, NORMAL, HAND /*,...*/ };
    Cursor(const TYPE t);
    void set(const sf::WindowHandle& aWindowHandle) const;
    ~Cursor();
};

}

#endif // DUSK_GRAPHICS_CURSOR_HPP