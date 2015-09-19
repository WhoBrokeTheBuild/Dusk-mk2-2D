#include "Window.hpp"

#include <Program.hpp>
#include <Utility/Benchmark.hpp>
#include <Logging/LoggingSystem.hpp>
#include <Graphics/GraphicsSystem.hpp>
#include <Input/InputSystem.hpp>
#include <Scripting/ScriptingSystem.hpp>

namespace Dusk
{
	
bool Window::Init(const unsigned int& width, const unsigned int& height, const string& title, const Flag& flags)
{
	DuskBenchStart();
	DuskLog("info", "Initializing Window");

	m_Title = title;

	m_Fullscreen = (flags & Window::FULLSCREEN) > 0;
	m_Decorated = (flags & Window::DECORATED) > 0;
	m_Resizable = (flags & Window::RESIZABLE) > 0;

	bool res = CreateSFMLWindow(width, height);

	Program::Inst()->AddEventListener(Program::EVT_UPDATE, this, &Window::Update);

	DuskBenchEnd("Window::Init");
	return res;
}

void Window::Term()
{
	Program::Inst()->RemoveEventListener(Program::EVT_UPDATE, this, &Window::Update);
}

void Window::Update(const Event& event)
{
	sf::Event sfEvent;
	while (mp_SFMLWindow->pollEvent(sfEvent))
	{
		if (sfEvent.type == sf::Event::Closed)
		{
			mp_SFMLWindow->close();
			Program::Inst()->Exit();
		}
	}
}

bool Window::CreateSFMLWindow(const unsigned int& width, const unsigned int& height)
{
	DuskBenchStart();

	uint32_t style = 0;

	if (m_Fullscreen)
	{
		style = sf::Style::Fullscreen;
	}
	else
	{
		style |= sf::Style::Close;

		if (m_Resizable)
			style |= sf::Style::Resize;

		if (m_Decorated)
			style |= sf::Style::Titlebar;
	}

	mp_SFMLWindow = new sf::Window(sf::VideoMode(width, height), m_Title, style);

	DuskBenchEnd("Window::CreateSFMLWindow");
	return mp_SFMLWindow->isOpen();
}

void Window::SetTitle(const string& title)
{
	mp_SFMLWindow->setTitle(title);
}

unsigned int Window::GetWidth() const
{
	return mp_SFMLWindow->getSize().x;
}

unsigned int Window::GetHeight() const
{
	return mp_SFMLWindow->getSize().y;
}

string Window::GetTitle() const
{
	return m_Title;
}

void Window::SetSize(const unsigned int& width, const unsigned int& height)
{
	mp_SFMLWindow->setSize(sf::Vector2u(width, height));
}

void Window::SetWidth(const unsigned int& width)
{
	sf::Vector2u size = mp_SFMLWindow->getSize();
	size.x = width;
	mp_SFMLWindow->setSize(size);
}

void Window::SetHeight(const unsigned int& height)
{
	sf::Vector2u size = mp_SFMLWindow->getSize();
	size.y = height;
	mp_SFMLWindow->setSize(size);
}

void Window::InitScripting()
{
	ScriptingSystem::RegisterFunction("dusk_window_set_size", &Window::Script_SetSize);

	ScriptingSystem::RegisterFunction("dusk_window_get_width", &Window::Script_GetWidth);
	ScriptingSystem::RegisterFunction("dusk_window_set_width", &Window::Script_SetWidth);

	ScriptingSystem::RegisterFunction("dusk_window_get_height", &Window::Script_GetHeight);
	ScriptingSystem::RegisterFunction("dusk_window_set_height", &Window::Script_SetHeight);

	ScriptingSystem::RegisterFunction("dusk_window_get_title", &Window::Script_GetTitle);
	ScriptingSystem::RegisterFunction("dusk_window_set_title", &Window::Script_SetTitle);
}

int Window::Script_SetSize(lua_State* L)
{
	Window* pWindow = (Window*)lua_tointeger(L, 1);
	int width = (int)lua_tointeger(L, 2);
	int height = (int)lua_tointeger(L, 3);
	pWindow->SetSize(width, height);

	return 0;
}

int Window::Script_GetWidth(lua_State* L)
{
	Window* pWindow = (Window*)lua_tointeger(L, 1);
	lua_pushinteger(L, (int)pWindow->GetWidth());

	return 1;
}

int Window::Script_SetWidth(lua_State* L)
{
	Window* pWindow = (Window*)lua_tointeger(L, 1);
	int width = (int)lua_tointeger(L, 2);
	pWindow->SetWidth(width);

	return 0;
}

int Window::Script_GetHeight(lua_State* L)
{
	Window* pWindow = (Window*)lua_tointeger(L, 1);
	lua_pushinteger(L, (int)pWindow->GetHeight());

	return 1;
}

int Window::Script_SetHeight(lua_State* L)
{
	Window* pWindow = (Window*)lua_tointeger(L, 1);
	int height = (int)lua_tointeger(L, 2);
	pWindow->SetHeight(height);

	return 0;
}

int Window::Script_GetTitle(lua_State* L)
{
	Window* pWindow = (Window*)lua_tointeger(L, 1);
	lua_pushstring(L, pWindow->GetTitle().c_str());

	return 1;
}

int Window::Script_SetTitle(lua_State* L)
{
	Window* pWindow = (Window*)lua_tointeger(L, 1);
	string title = lua_tostring(L, 2);
	pWindow->SetTitle(title);

	return 0;
}

} // namespace Dusk