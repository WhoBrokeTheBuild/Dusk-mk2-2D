#include "Window.hpp"

#include <Program.hpp>
#include <Graphics/GraphicsContext.hpp>
#include <Utility/Benchmark.hpp>
#include <Utility/Platform.hpp>
#include <Logging/LoggingSystem.hpp>
#include <Input/InputSystem.hpp>
#include <Scripting/ScriptingSystem.hpp>

#include <Windows.h>

namespace dusk
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

	mp_GraphicsContext = New GraphicsContext(m_SFMLWindow);

	Program::Inst()->AddEventListener(Program::EVT_UPDATE, this, &Window::OnUpdate);

	DuskBenchEnd("Window::Init");
	return res;
}

void Window::Term()
{
	Program::Inst()->RemoveEventListener(Program::EVT_UPDATE, this, &Window::OnUpdate);

	delete mp_GraphicsContext;
	mp_GraphicsContext = nullptr;
}

void Window::OnUpdate(const Event& event)
{
	sf::Event sfEvent;
	while (m_SFMLWindow.pollEvent(sfEvent))
	{
		if (sfEvent.type == sf::Event::Closed)
		{
			m_SFMLWindow.close();
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

	m_SFMLWindow.create(sf::VideoMode(width, height), m_Title, style);

	DuskExtLog("info", "Req %d %d", width, height);
	DuskExtLog("info", "Act %d %d", m_SFMLWindow.getSize().x, m_SFMLWindow.getSize().y);

	DuskBenchEnd("Window::CreateSFMLWindow");
	return m_SFMLWindow.isOpen();
}

void Window::SetTitle(const string& title)
{
	m_SFMLWindow.setTitle(title);
}

unsigned int Window::GetWidth() const
{
	return m_SFMLWindow.getSize().x;
}

unsigned int Window::GetHeight() const
{
	return m_SFMLWindow.getSize().y;
}

string Window::GetTitle() const
{
	return m_Title;
}

GraphicsContext* Window::GetGraphicsContext() const
{
	return mp_GraphicsContext;
}

void Window::InitScripting()
{
	ScriptingSystem::RegisterFunction("dusk_window_get_width",  &Window::Script_GetWidth);
	ScriptingSystem::RegisterFunction("dusk_window_get_height", &Window::Script_GetHeight);
	ScriptingSystem::RegisterFunction("dusk_window_get_title",  &Window::Script_GetTitle);
	ScriptingSystem::RegisterFunction("dusk_window_set_title",  &Window::Script_SetTitle);
}

int Window::Script_GetWidth(lua_State* L)
{
	Window* pWindow = (Window*)lua_tointeger(L, 1);
	lua_pushinteger(L, (int)pWindow->GetWidth());

	return 1;
}

int Window::Script_GetHeight(lua_State* L)
{
	Window* pWindow = (Window*)lua_tointeger(L, 1);
	lua_pushinteger(L, (int)pWindow->GetHeight());

	return 1;
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

} // namespace dusk
