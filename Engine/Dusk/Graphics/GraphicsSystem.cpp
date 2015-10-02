#include "GraphicsSystem.hpp"

#include <Dusk/Program.hpp>
#include <Dusk/Graphics/GraphicsContext.hpp>
#include <Dusk/Graphics/Texture.hpp>
#include <Dusk/Graphics/Sprite.hpp>
#include <Dusk/Utility/Benchmark.hpp>
#include <Dusk/Logging/Logging.hpp>
#include <Dusk/Scripting/Scripting.hpp>
#include <Dusk/Input/InputSystem.hpp>

namespace dusk
{

GraphicsSystem::GraphicsSystem() :
    m_Title(),
    m_Width(1024),
    m_Height(768),
    m_Style(WindowStyle::Default),
    m_SFMLWindow(),
    mp_GraphicsContext(nullptr)
{ }

bool GraphicsSystem::Init()
{
    DuskLog("verbose", "Graphics System initializing");
    DuskBenchStart();

    CreateSFMLWindow();
    mp_GraphicsContext = New GraphicsContext(m_SFMLWindow);

    Program::Inst()->AddEventListener(Program::EvtUpdate, this, &GraphicsSystem::OnUpdate);

    DuskBenchEnd("GraphicsSystem::Init");
    return true;
}

void GraphicsSystem::Term()
{
    Program::Inst()->RemoveEventListener(Program::EvtUpdate, this, &GraphicsSystem::OnUpdate);

    delete mp_GraphicsContext;
    mp_GraphicsContext = nullptr;
}

void GraphicsSystem::OnUpdate(const Event& event)
{
    InputSystem* pIS = Program::Inst()->GetInputSystem();

    sf::Event sfEvent;
    while (m_SFMLWindow.pollEvent(sfEvent))
    {
        Keyboard::Key key = Keyboard::Key::Invalid;
        Mouse::Button button = Mouse::Button::Invalid;

        switch (sfEvent.type)
        {
        case sf::Event::Closed:

            m_SFMLWindow.close();
            Program::Inst()->Exit();

            break;
        case sf::Event::KeyPressed:

            key = Keyboard::ConvertSFMLKey(sfEvent.key.code);
            pIS->TriggerKeyPress(key);

            break;
        case sf::Event::KeyReleased:

            key = Keyboard::ConvertSFMLKey(sfEvent.key.code);
            pIS->TriggerKeyRelease(key);

            break;
        case sf::Event::MouseButtonPressed:

            button = Mouse::ConvertSFMLMouseButton(sfEvent.mouseButton.button);
            pIS->TriggerMouseButtonPress(button);

            break;
        case sf::Event::MouseButtonReleased:

            button = Mouse::ConvertSFMLMouseButton(sfEvent.mouseButton.button);
            pIS->TriggerMouseButtonRelease(button);

            break;
        case sf::Event::MouseMoved:

            pIS->TriggerMouseMoveAbsolute(sfEvent.mouseMove.x, sfEvent.mouseMove.y);

            break;
        case sf::Event::MouseWheelScrolled:

            if (sfEvent.mouseWheelScroll.wheel == sf::Mouse::Wheel::HorizontalWheel)
            {
                pIS->TriggerMouseScroll(sfEvent.mouseWheelScroll.delta, 0.0f);
            }
            else if (sfEvent.mouseWheelScroll.wheel == sf::Mouse::Wheel::VerticalWheel)
            {
                pIS->TriggerMouseScroll(0.0f, sfEvent.mouseWheelScroll.delta);
            }

            break;
        }
    }
}

Vector2u GraphicsSystem::GetWindowSize() const
{
    return m_SFMLWindow.getSize();
}

void GraphicsSystem::SetWindowWidth(const unsigned int& width)
{
    m_Width = width;
}

void GraphicsSystem::SetWindowHeight(const unsigned int& height)
{
    m_Height = height;
}

void GraphicsSystem::SetWindowSize(const unsigned int& width, const unsigned int& height)
{
    m_Width = width;
    m_Height = height;
}

void GraphicsSystem::SetWindowStyle(const int& styleFlags)
{
    m_Style = styleFlags;
}

void GraphicsSystem::ApplyWindowChanges()
{
    CreateSFMLWindow();
}

void GraphicsSystem::SetWindowTitle(const string& title)
{
    m_Title = title;
    m_SFMLWindow.setTitle(title);
}

bool GraphicsSystem::IsFullscreen() const
{
    return (m_Style & WindowStyle::Fullscreen) > 0;
}

bool GraphicsSystem::IsDecorated() const
{
    return (m_Style & WindowStyle::Decorated) > 0;
}

bool GraphicsSystem::IsResizable() const
{
    return (m_Style & WindowStyle::Resizable) > 0;
}

GraphicsContext* GraphicsSystem::GetContext() const
{
    return mp_GraphicsContext;
}

bool GraphicsSystem::CreateSFMLWindow()
{
    uint32_t style = 0;

    if (IsFullscreen())
    {
        style = sf::Style::Fullscreen;
    }
    else
    {
        style |= sf::Style::Close;

        if (IsResizable())
            style |= sf::Style::Resize;

        if (IsDecorated())
            style |= sf::Style::Titlebar;
    }

    m_SFMLWindow.create(sf::VideoMode(m_Width, m_Height), m_Title, style);

    m_SFMLWindow.setKeyRepeatEnabled(false);

    return m_SFMLWindow.isOpen();
}

void GraphicsSystem::Script_RegisterFunctions()
{
    Scripting::RegisterFunction("dusk_get_graphics_system", &GraphicsSystem::Script_Get);
    Scripting::RegisterFunction("dusk_graphics_system_get_context", &GraphicsSystem::Script_GetContext);
    Scripting::RegisterFunction("dusk_graphics_system_get_window_size", &GraphicsSystem::Script_GetWindowSize);
    Scripting::RegisterFunction("dusk_graphics_system_get_window_title", &GraphicsSystem::Script_GetWindowTitle);
    Scripting::RegisterFunction("dusk_graphics_system_set_window_title", &GraphicsSystem::Script_SetWindowTitle);

    GraphicsContext::Script_RegisterFunctions();
    Texture::Script_RegisterFunctions();
    Sprite::Script_RegisterFunctions();
}

int GraphicsSystem::Script_Get(lua_State* L)
{
    lua_pushinteger(L, (ptrdiff_t)Program::Inst()->GetGraphicsSystem());
    return 1;
}

int GraphicsSystem::Script_GetContext(lua_State* L)
{
    lua_pushinteger(L, (ptrdiff_t)Program::Inst()->GetGraphicsSystem()->GetContext());
    return 1;
}

int GraphicsSystem::Script_GetWindowSize(lua_State* L)
{
    GraphicsSystem* pGS = Program::Inst()->GetGraphicsSystem();
    Vector2u size = pGS->GetWindowSize();
    lua_pushinteger(L, size.x);
    lua_pushinteger(L, size.y);
    return 2;
}

int GraphicsSystem::Script_GetWindowTitle(lua_State* L)
{
    GraphicsSystem* pGS = Program::Inst()->GetGraphicsSystem();
    string title = pGS->GetWindowTitle();
    lua_pushstring(L, title.c_str());
    return 1;
}

int GraphicsSystem::Script_SetWindowTitle(lua_State* L)
{
    GraphicsSystem* pGS = Program::Inst()->GetGraphicsSystem();
    string title = lua_tostring(L, 1);
    pGS->SetWindowTitle(title);
    return 0;
}

} // namespace dusk
