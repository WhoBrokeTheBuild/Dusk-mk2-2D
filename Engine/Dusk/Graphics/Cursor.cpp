#include "Cursor.hpp"

#ifdef SFML_SYSTEM_WINDOWS

dusk::Cursor::Cursor(const dusk::Cursor::TYPE t)
{
    switch (t)
    {
    case Cursor::WAIT:
        CursorType = LoadCursor(NULL, IDC_WAIT);
        break;
    case Cursor::HAND:
        CursorType = LoadCursor(NULL, IDC_HAND);
        break;
    case Cursor::NORMAL:
        CursorType = LoadCursor(NULL, IDC_ARROW);
        break;
    case Cursor::TEXT:
        CursorType = LoadCursor(NULL, IDC_IBEAM);
        break;
        //For more cursor options on Windows go here:
        // http://msdn.microsoft.com/en-us/library/ms648391%28v=vs.85%29.aspx
    }
}

void dusk::Cursor::set(const sf::WindowHandle& aWindowHandle) const
{
    SetClassLongPtr(aWindowHandle, GCLP_HCURSOR, reinterpret_cast<LONG_PTR>(CursorType));
}

dusk::Cursor::~Cursor()
{
    // Nothing to do for destructor :
    // no memory has been allocated (shared ressource principle)
}

#elif defined(SFML_SYSTEM_LINUX)

sf::Cursor::Cursor(const sf::Cursor::TYPE t)
{
    display = XOpenDisplay(NULL);

    switch (t)
    {
    case Cursor::WAIT:
        CursorType = XCreateFontCursor(display, XC_watch);
        break;
    case Cursor::HAND:
        CursorType = XCreateFontCursor(display, XC_hand1);
        break;
    case Cursor::NORMAL:
        CursorType = XCreateFontCursor(display, XC_left_ptr);
        break;
    case Cursor::TEXT:
        CursorType = XCreateFontCursor(display, XC_xterm);
        break;
        // For more cursor options on Linux go here:
        // http://www.tronche.com/gui/x/xlib/appendix/b/
    }
}

void dusk::Cursor::set(const sf::WindowHandle& aWindowHandle) const
{
    XDefineCursor(display, aWindowHandle, CursorType);
    XFlush(display);
}

dusk::Cursor::~Cursor()
{
    XFreeCursor(display, Cursor);
    delete display;
    display = NULL;
}

#else
#error This OS is not yet supported by the cursor library.
#endif