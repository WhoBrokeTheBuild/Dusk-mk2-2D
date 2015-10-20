#include "Keyboard.hpp"

namespace dusk
{

Keyboard::Key Keyboard::ConvertSFMLKey(sf::Keyboard::Key key)
{
    for (unsigned int i = 0; i < 26; ++i)
    {
        if (key == (int)(sf::Keyboard::Key::A + i))
            return (Key)(Key::A + i);
    }

    for (unsigned int i = 0; i < 10; ++i)
    {
        if (key == (int)(sf::Keyboard::Key::Num0 + i))
            return (Key)(Key::N0 + i);
    }

    for (unsigned int i = 0; i < 10; ++i)
    {
        if (key == (int)(sf::Keyboard::Key::Numpad0 + i))
            return (Key)(Key::Pad0 + i);
    }

    for (unsigned int i = 0; i < 15; ++i)
    {
        if (key == (int)(sf::Keyboard::Key::F1 + i))
            return (Key)(Key::F1 + i);
    }

    switch (key)
    {
    case sf::Keyboard::Key::Dash:
        return Key::Dash;

    case sf::Keyboard::Key::Equal:
        return Key::Equal;

    case sf::Keyboard::Key::Tilde:
        return Key::Tilde;

    case sf::Keyboard::Key::LBracket:
        return Key::LeftBracket;

    case sf::Keyboard::Key::RBracket:
        return Key::RightBracket;

    case sf::Keyboard::Key::SemiColon:
        return Key::Semicolon;

    case sf::Keyboard::Key::Quote:
        return Key::Quote;

    case sf::Keyboard::Key::Period:
        return Key::Period;

    case sf::Keyboard::Key::BackSlash:
        return Key::Backslash;

    case sf::Keyboard::Key::Slash:
        return Key::Slash;

    case sf::Keyboard::Key::Up:
        return Key::Up;

    case sf::Keyboard::Key::Down:
        return Key::Down;

    case sf::Keyboard::Key::Left:
        return Key::Left;

    case sf::Keyboard::Key::Right:
        return Key::Right;

    case sf::Keyboard::Key::BackSpace:
        return Key::Backspace;

    case sf::Keyboard::Key::Tab:
        return Key::Tab;

    case sf::Keyboard::Key::Return:
        return Key::Enter;

    case sf::Keyboard::Key::Space:
        return Key::Space;

    case sf::Keyboard::Key::LShift:
        return Key::LeftShift;

    case sf::Keyboard::Key::RShift:
        return Key::RightShift;

    case sf::Keyboard::Key::LControl:
        return Key::LeftControl;

    case sf::Keyboard::Key::RControl:
        return Key::RightControl;

    case sf::Keyboard::Key::LAlt:
        return Key::LeftAlt;

    case sf::Keyboard::Key::RAlt:
        return Key::RightAlt;

    case sf::Keyboard::Key::Insert:
        return Key::Insert;

    case sf::Keyboard::Key::Delete:
        return Key::Delete;

    case sf::Keyboard::Key::Home:
        return Key::Home;

    case sf::Keyboard::Key::End:
        return Key::End;

    case sf::Keyboard::Key::PageUp:
        return Key::PageUp;

    case sf::Keyboard::Key::PageDown:
        return Key::PageDown;

    case sf::Keyboard::Key::Escape:
        return Key::Escape;

    case sf::Keyboard::Key::Menu:
        return Key::Menu;

    case sf::Keyboard::Key::LSystem:
        return Key::LeftSuper;

    case sf::Keyboard::Key::RSystem:
        return Key::RightSuper;

    case sf::Keyboard::Key::Pause:
        return Key::Pause;

    case sf::Keyboard::Key::Add:
        return Key::Add;

    case sf::Keyboard::Key::Subtract:
        return Key::Subtract;

    case sf::Keyboard::Key::Multiply:
        return Key::Multiply;

    case sf::Keyboard::Key::Divide:
        return Key::Divide;

    default:
        return Key::Invalid;
    }
}

int KeyEventData::PushDataToLua(lua_State* L) const
{
    lua_pushinteger(L, m_Key);
    return 1;
}

int TextInputEventData::PushDataToLua(lua_State* L) const
{
    return 0;
}

} // namespace dusk
