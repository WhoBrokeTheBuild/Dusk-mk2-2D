#include "GraphicsSystem.hpp"

#include <Dusk/Program.hpp>
#include <Dusk/Graphics/GraphicsContext.hpp>
#include <Dusk/Graphics/Texture.hpp>
#include <Dusk/Graphics/Sprite.hpp>
#include <Dusk/Utility/Benchmark.hpp>
#include <Dusk/Logging/Logging.hpp>
#include <Dusk/Scripting/Scripting.hpp>

namespace dusk
{

Flag GraphicsSystem::FULLSCREEN = 1;
Flag GraphicsSystem::RESIZABLE  = 2;
Flag GraphicsSystem::DECORATED  = 4;

GraphicsSystem* GraphicsSystem::sp_Inst = nullptr;

GraphicsSystem::GraphicsSystem() :
	m_Title(),
	m_Fullscreen(false),
	m_Decorated(false),
	m_Resizable(false),
	m_SFMLWindow(),
	mp_GraphicsContext(nullptr)
{ }

bool GraphicsSystem::Init(const unsigned int& width, const unsigned int& height, const string& title, const Flag& flags)
{
	DuskLog("verbose", "Graphics System initializing");
	DuskBenchStart();

	m_Title = title;

	m_Fullscreen = (flags & GraphicsSystem::FULLSCREEN) > 0;
	m_Decorated  = (flags & GraphicsSystem::DECORATED) > 0;
	m_Resizable  = (flags & GraphicsSystem::RESIZABLE) > 0;

	CreateSFMLWindow(width, height);

	Program::Inst()->AddEventListener(Program::EVT_UPDATE, this, &GraphicsSystem::OnUpdate);

	DuskBenchEnd("GraphicsSystem::Init");
	return true;
}

void GraphicsSystem::Term()
{
	Program::Inst()->RemoveEventListener(Program::EVT_UPDATE, this, &GraphicsSystem::OnUpdate);

	delete mp_GraphicsContext;
	mp_GraphicsContext = nullptr;
}

void GraphicsSystem::OnUpdate(const Event& event)
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

Vector2u GraphicsSystem::GetWindowSize() const
{
	return m_SFMLWindow.getSize();
}

void GraphicsSystem::SetWindowTitle(const string& title)
{
	m_SFMLWindow.setTitle(title);
}

GraphicsContext* GraphicsSystem::GetContext() const
{
	return mp_GraphicsContext;
}

bool GraphicsSystem::CreateSFMLWindow(const unsigned int& width, const unsigned int& height)
{
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
	mp_GraphicsContext = New GraphicsContext(m_SFMLWindow);

	return m_SFMLWindow.isOpen();
}

void GraphicsSystem::Script_RegisterFunctions()
{
	Scripting::RegisterFunction("dusk_get_graphics_system",				 &GraphicsSystem::Script_Get);
	Scripting::RegisterFunction("dusk_graphics_system_get_context",      &GraphicsSystem::Script_GetContext);
	Scripting::RegisterFunction("dusk_graphics_system_get_window_size",  &GraphicsSystem::Script_GetWindowSize);
	Scripting::RegisterFunction("dusk_graphics_system_get_window_title", &GraphicsSystem::Script_GetWindowTitle);
	Scripting::RegisterFunction("dusk_graphics_system_set_window_title", &GraphicsSystem::Script_SetWindowTitle);

	GraphicsContext::Script_RegisterFunctions();
	Texture::Script_RegisterFunctions();
	Sprite::Script_RegisterFunctions();
}


int GraphicsSystem::Script_Get(lua_State* L)
{
	lua_pushinteger(L, (ptrdiff_t)GraphicsSystem::Inst());
	return 1;
}

int GraphicsSystem::Script_GetContext(lua_State* L)
{
	lua_pushinteger(L, (ptrdiff_t)GraphicsSystem::Inst()->GetContext());
	return 1;
}

int GraphicsSystem::Script_GetWindowSize(lua_State* L)
{
	Vector2u size = GraphicsSystem::Inst()->GetWindowSize();
	lua_pushinteger(L, size.x);
	lua_pushinteger(L, size.y);
	return 2;
}

int GraphicsSystem::Script_GetWindowTitle(lua_State* L)
{
	string title = GraphicsSystem::Inst()->GetWindowTitle();
	lua_pushstring(L, title.c_str());
	return 1;
}

int GraphicsSystem::Script_SetWindowTitle(lua_State* L)
{
	string title = lua_tostring(L, 1);
	GraphicsSystem::Inst()->SetWindowTitle(title);
	return 0;
}

} // namespace dusk
