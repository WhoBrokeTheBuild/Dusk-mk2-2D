#ifndef DUSK_INPUT_KEYS_HPP
#define DUSK_INPUT_KEYS_HPP

#include <Collections/Map.hpp>
#include <Events/Event.hpp>

namespace Dusk
{

enum Key
{

INVALID_KEY					= -1,

KEY_A						= 1,
KEY_B						= 2,
KEY_C						= 3,
KEY_D						= 4,
KEY_E						= 5,
KEY_F						= 6,
KEY_G						= 7,
KEY_H						= 8,
KEY_I						= 9,
KEY_J						= 10,
KEY_K						= 11,
KEY_L						= 12,
KEY_M						= 13,
KEY_N						= 14,
KEY_O						= 15,
KEY_P						= 16,
KEY_Q						= 17,
KEY_R						= 18,
KEY_S						= 19,
KEY_T						= 20,
KEY_U						= 21,
KEY_V						= 22,
KEY_W						= 23,
KEY_X						= 24,
KEY_Y						= 25,
KEY_Z						= 26,

KEY_0						= 50,
KEY_EXCLAMATION				= KEY_0,

KEY_1						= 51,
KEY_AT						= KEY_1,

KEY_2						= 52,
KEY_HASHTAG					= KEY_2,
KEY_POUND					= KEY_HASHTAG,

KEY_3						= 53,
KEY_DOLLAR					= KEY_3,

KEY_4						= 54,
KEY_PERCENT					= KEY_4,

KEY_5						= 55,
KEY_CARROT					= KEY_5,

KEY_6						= 56,
KEY_STAR					= KEY_6,
KEY_ASTERISK				= KEY_STAR,

KEY_7						= 57,
KEY_AMPERSAND				= KEY_7,

KEY_8						= 58,
KEY_PARENTHESIS_OPEN		= KEY_8,

KEY_9						= 59,
KEY_PARENTHESIS_CLOSE		= KEY_9,

KEY_DASH					= 100,
KEY_MINUS					= KEY_DASH,
KEY_UNDERSCORE				= KEY_MINUS,

KEY_EQUAL					= 101,
KEY_PLUS					= KEY_EQUAL,

KEY_ACCENT					= 102,
KEY_TILDE					= KEY_ACCENT,

KEY_SQUARE_BRACKET_OPEN		= 103,
KEY_CURLY_BRACE_OPEN		= KEY_SQUARE_BRACKET_OPEN,

KEY_SQUARE_BRACKET_CLOSE	= 104,
KEY_CURLY_BRACE_CLOSE		= KEY_SQUARE_BRACKET_CLOSE,

KEY_SEMICOLON				= 105,
KEY_COLON					= KEY_SEMICOLON,

KEY_QUOTE					= 106,
KEY_APOSTROPHE				= KEY_QUOTE,
KEY_DOUBLE_QUOTE			= KEY_QUOTE,

KEY_BACKSLASH				= 107,
KEY_PIPE					= KEY_BACKSLASH,

KEY_PERIOD					= 108,
KEY_LESS_THAN				= KEY_PERIOD,
KEY_ANGLE_BRACKET_OPEN		= KEY_LESS_THAN,
KEY_CHEVRON_LEFT			= KEY_LESS_THAN,

KEY_COMMA					= 109,
KEY_GREATER_THAN			= KEY_COMMA,
KEY_ANGLE_BRACKET_CLOSE		= KEY_GREATER_THAN,
KEY_CHEVRON_RIGHT			= KEY_GREATER_THAN,

KEY_SLASH					= 110,
KEY_FORWARD_SLASH			= KEY_SLASH,
KEY_QUESTION_MARK			= KEY_SLASH,

KEY_UP						= 111,
KEY_DOWN					= 112,
KEY_LEFT					= 113,
KEY_RIGHT					= 114,

KEY_CAPS_LOCK				= 115,
KEY_SCROLL_LOCK             = 116,
KEY_NUM_LOCK                = 117,

KEY_BACKSPACE				= 118,
KEY_TAB						= 119,
KEY_ENTER					= 120,
KEY_SPACE					= 121,

KEY_PAUSE					= 122,
KEY_BREAK					= KEY_PAUSE,

KEY_PRINT_SCREEN			= 123,
KEY_SYS_REQ					= KEY_PRINT_SCREEN,

KEY_LEFT_SHIFT				= 124,
KEY_RIGHT_SHIFT				= 125,

KEY_LEFT_CTRL				= 126,
KEY_LEFT_CONTROL			= KEY_LEFT_CTRL,

KEY_RIGHT_CTRL				= 127,
KEY_RIGHT_CONTROL			= KEY_RIGHT_CTRL,

KEY_LEFT_ALT				= 128,
KEY_LEFT_ALTERNATE			= KEY_LEFT_ALT,

KEY_RIGHT_ALT				= 129,
KEY_RIGHT_ALTERNATE			= KEY_RIGHT_ALT,

KEY_INSERT					= 130,
KEY_DELETE					= 131,
KEY_HOME					= 132,
KEY_END						= 133,
KEY_PAGE_UP					= 134,
KEY_PAGE_DOWN				= 135,
KEY_ESCAPE					= 136,
KEY_MENU					= 137,

KEY_LEFT_SUPER				= 138,
KEY_LEFT_WINDOWS			= KEY_LEFT_SUPER,

KEY_RIGHT_SUPER				= 139,
KEY_RIGHT_WINDOWS			= KEY_RIGHT_SUPER,

KEY_PAD_0					= 200,
KEY_PAD_INSERT				= KEY_PAD_0,

KEY_PAD_1					= 201,
KEY_PAD_END					= KEY_PAD_1,

KEY_PAD_2					= 202,
KEY_PAD_DOWN				= KEY_PAD_2,

KEY_PAD_3					= 203,
KEY_PAD_PAGE_DOWN			= KEY_PAD_3,

KEY_PAD_4					= 204,
KEY_PAD_LEFT				= KEY_PAD_4,

KEY_PAD_5					= 205,

KEY_PAD_6					= 206,
KEY_PAD_RIGHT				= KEY_PAD_6,

KEY_PAD_7					= 207,
KEY_PAD_HOME				= KEY_PAD_7,

KEY_PAD_8					= 208,
KEY_PAD_UP					= KEY_PAD_8,

KEY_PAD_9					= 209,
KEY_PAD_PAGE_UP				= KEY_PAD_9,

KEY_PAD_ADD					= 210,
KEY_PAD_SUBTRACT			= 211,
KEY_PAD_MULTIPLY			= 212,
KEY_PAD_DIVIDE				= 213,
KEY_PAD_ENTER				= 214,

KEY_PAD_DECIMAL				= 215,
KEY_PAD_DELETE				= KEY_PAD_DECIMAL,

KEY_F1						= 216,
KEY_F2						= 217,
KEY_F3						= 218,
KEY_F4						= 219,
KEY_F5						= 220,
KEY_F6						= 221,
KEY_F7						= 222,
KEY_F8						= 223,
KEY_F9						= 224,
KEY_F10						= 225,
KEY_F11						= 226,
KEY_F12						= 227,
KEY_F13						= 228,
KEY_F14						= 229,
KEY_F15						= 230,
KEY_F16						= 231,
KEY_F17						= 232,
KEY_F18						= 233,
KEY_F19						= 234,
KEY_F20						= 235,
KEY_F21						= 236,
KEY_F22						= 237,
KEY_F23						= 238,
KEY_F24						= 239,
KEY_F25						= 240,

}; // enum Keys

class KeyEventData :
	public EventData
{
public:

	KeyEventData() :
		m_Key(Key::INVALID_KEY)
	{ }

	KeyEventData(const Key& key) :
		m_Key(key)
	{ }

	virtual inline string GetClassName() const { return "Key Event Data"; }

	virtual inline EventData* Clone() const { return New KeyEventData(m_Key); }

	inline Key GetKey() const { return m_Key; }

	virtual int PushDataToLua(lua_State* L) const;

private:

	Key	m_Key;

}; // class KeyEventData

} // namespace Dusk

#endif // DUSK_INPUT_KEYS_HPP