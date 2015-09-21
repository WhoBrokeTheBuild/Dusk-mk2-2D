#ifndef DUSK_GRAPHICS_TEXT_BUFFER_HPP
#define DUSK_GRAPHICS_TEXT_BUFFER_HPP

#include <Dusk/Tracking/ITrackedObject.hpp>
#include <Dusk/Graphics/Color.h>

#include <lua.hpp>
#include <SFML/Graphics/Text.hpp>

namespace dusk
{

class Font;

class TextBuffer :
	public ITrackedObject
{

	friend class GraphicsContext;

public:

	inline TextBuffer() :
		mp_Font(nullptr),
		m_Text(),
		m_Size(),
		m_Color(),
		m_SFMLText()
	{ }

	virtual inline ~TextBuffer() { Term(); }

	virtual inline string GetClassName() const { return "Text Buffer"; }

	bool Init(Font* pFont, const string& text, const unsigned int& size, const Color& color);
	void Term();

	void SetFont(Font* pFont);

	inline string GetText() const { return m_Text; }
	void SetText(const string& text);

	inline unsigned int GetSize() const { return m_Size; }
	void SetSize(const unsigned int& size);

	inline Color GetColor() const { return m_Color; }
	void SetColor(const Color& color);

private:

	inline const sf::Text& GetSFMLText() const
	{
		return m_SFMLText;
	}

	Font* mp_Font;

	string m_Text;

	unsigned int m_Size;

	Color m_Color;

	sf::Text m_SFMLText;

public:

	static void Script_RegisterFunctions();
	static int Script_New(lua_State* L);
	static int Script_Delete(lua_State* L);

}; // class TextBuffer

} // namespace dusk

#endif // DUSK_GRAPHICS_TEXT_BUFFER_HPP