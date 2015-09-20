if not Dusk then Dusk = { } end

Dusk.GetInputSystem = function(inputId, key)
	return Dusk.InputSystem( dusk_get_input_system() )
end

-- Dusk.InputSystem

local InputSystem = Dusk.Class(Dusk.IEventDispatcher, function(self, ptr)
	Dusk.IEventDispatcher.init(self, ptr)
end)

InputSystem.EVT_KEY_PRESS			 = 1
InputSystem.EVT_KEY_RELEASE			 = 2
InputSystem.EVT_MOUSE_MOVE			 = 10
InputSystem.EVT_MOUSE_SCROLL         = 11
InputSystem.EVT_MOUSE_BUTTON_PRESS	 = 12
InputSystem.EVT_MOUSE_BUTTON_RELEASE = 13
InputSystem.EVT_MAPPED_INPUT_PRESS	 = 20
InputSystem.EVT_MAPPED_INPUT_RELEASE = 21

function InputSystem:MapKey(inputId, key)
	dusk_input_system_map_key(self.dusk_ptr, inputId, key);
end

function InputSystem:MapMouseButton(inputId, button)
	dusk_input_system_map_mouse_button(self.dusk_ptr, inputId, button);
end

function InputSystem:GetMappedKey(inputId)
	return dusk_input_system_get_mapped_key(self.dusk_ptr, inputId);
end

function InputSystem:GetMappedMouseButton(inputId)
	return dusk_input_system_get_mapped_mouse_button(self.dusk_ptr, inputId);
end

Dusk.InputSystem = InputSystem

-- Dusk.MouseButtons

Dusk.MouseButtons = {
	Left   = 1,
	Middle = 2,
	Right  = 3,
}

-- Dusk.Keys

Dusk.Keys = {
	Invalid					= -1,

	A						= 1,
	B						= 2,
	C						= 3,
	D						= 4,
	E						= 5,
	F						= 6,
	G						= 7,
	H						= 8,
	I						= 9,
	J						= 10,
	K						= 11,
	L						= 12,
	M						= 13,
	N						= 14,
	O						= 15,
	P						= 16,
	Q						= 17,
	R						= 18,
	S						= 19,
	T						= 20,
	U						= 21,
	V						= 22,
	W						= 23,
	X						= 24,
	Y						= 25,
	Z						= 26,
	N0						= 50,
	N1						= 51,
	N2						= 52,
	N3						= 53,
	N4						= 54,
	N5						= 55,
	N6						= 56,
	N7						= 57,
	N8						= 58,
	N9						= 59,
	Dash					= 100,
	Equal					= 101,
	Accent					= 102,
	SquareBracketOpen		= 103,
	SquareBracketClose		= 104,
	Semicolon				= 105,
	Quote					= 106,
	Backslash				= 107,
	Period					= 108,
	Comma					= 109,
	Slash					= 110,
	Up						= 111,
	Down					= 112,
	Left					= 113,
	Right					= 114,
	CapsLock				= 115,
	ScrollLock              = 116,
	NumLock                 = 117,
	Backspace				= 118,
	Tab						= 119,
	Enter					= 120,
	Space					= 121,
	Pause					= 122,
	PrintScreen				= 123,
	LeftShift				= 124,
	RightShift				= 125,
	LeftCtrl				= 126,
	RightCtrl				= 127,
	Home					= 132,
	End						= 133,
	PageUp					= 134,
	PageDown				= 135,
	Escape					= 136,
	Menu					= 137,
	LeftSuper				= 138,
	RightSuper				= 139,
	Pad0					= 200,
	Pad1					= 201,
	Pad2					= 202,
	Pad3					= 203,
	Pad4					= 204,
	Pad5					= 205,
	Pad6					= 206,
	Pad7					= 207,
	Pad8					= 208,
	Pad9					= 209,
	PadAdd					= 210,
	PadSubtract				= 211,
	PadMultiply				= 212,
	PadDivide				= 213,
	PadEnter				= 214,
	PadDecimal				= 215,
	F1						= 216,
	F2						= 217,
	F3						= 218,
	F4						= 219,
	F5						= 220,
	F6						= 221,
	F7						= 222,
	F8						= 223,
	F9						= 224,
	F10						= 225,
	F11						= 226,
	F12						= 227,
	F13						= 228,
	F14						= 229,
	F15						= 230,
	F16						= 231,
	F17						= 232,
	F18						= 233,
	F19						= 234,
	F20						= 235,
	F21						= 236,
	F22						= 237,
	F23						= 238,
	F24						= 239,
	F25						= 240,
}

-- Key Aliases

Dusk.Keys.Exclamation				= Dusk.Keys.N0;
Dusk.Keys.At						= Dusk.Keys.N1;
Dusk.Keys.Hashtag					= Dusk.Keys.N2;
Dusk.Keys.Pound					= Dusk.Keys.Hashtag;
Dusk.Keys.Dollar					= Dusk.Keys.N3;
Dusk.Keys.Percent					= Dusk.Keys.N4;
Dusk.Keys.Carrot					= Dusk.Keys.N5;
Dusk.Keys.Star					= Dusk.Keys.N6;
Dusk.Keys.Asterisk				= Dusk.Keys.Star;
Dusk.Keys.Ampersand				= Dusk.Keys.N7;
Dusk.Keys.ParenthesisOpen			= Dusk.Keys.N8;
Dusk.Keys.ParenthesisClose		= Dusk.Keys.N9;
Dusk.Keys.Minus					= Dusk.Keys.Dash;
Dusk.Keys.Underscore				= Dusk.Keys.Minus;
Dusk.Keys.Plus					= Dusk.Keys.Equal;
Dusk.Keys.Tilde					= Dusk.Keys.Accent;
Dusk.Keys.CurlyBraceOpen			= Dusk.Keys.SquareBracketOpen;
Dusk.Keys.CurlyBraceClose			= Dusk.Keys.SquareBracketClose;
Dusk.Keys.COLON					= Dusk.Keys.Semicolon;
Dusk.Keys.Apostrophy				= Dusk.Keys.Quote;
Dusk.Keys.DoubleQuote				= Dusk.Keys.Quote;
Dusk.Keys.Pipe					= Dusk.Keys.Backslash;
Dusk.Keys.LessThan				= Dusk.Keys.Period;
Dusk.Keys.AngleBracketOpen		= Dusk.Keys.LessThan;
Dusk.Keys.ChevronLeft				= Dusk.Keys.LessThan;
Dusk.Keys.GreaterThan				= Dusk.Keys.Comma;
Dusk.Keys.AngleBracketClose		= Dusk.Keys.GreaterThan;
Dusk.Keys.ChevronRight			= Dusk.Keys.GreaterThan;
Dusk.Keys.ForwardSlash			= Dusk.Keys.Slash;
Dusk.Keys.Questionmark			= Dusk.Keys.Slash;
Dusk.Keys.Break					= Dusk.Keys.Pause;
Dusk.Keys.SysReq					= Dusk.Keys.PrintScreen;
Dusk.Keys.LeftControl				= Dusk.Keys.LeftCtrl;
Dusk.Keys.RightControl			= Dusk.Keys.RightCtrl;
Dusk.Keys.LeftAlternate			= Dusk.Keys.LeftAlt;
Dusk.Keys.RightAlternate			= Dusk.Keys.RightAlt;
Dusk.Keys.LeftWindows				= Dusk.Keys.LeftSuper;
Dusk.Keys.RightWindows			= Dusk.Keys.RightSuper;
Dusk.Keys.PadInsert				= Dusk.Keys.Pad0;
Dusk.Keys.PadEnd					= Dusk.Keys.Pad1;
Dusk.Keys.PadDown					= Dusk.Keys.Pad2;
Dusk.Keys.PadPageDown				= Dusk.Keys.Pad3;
Dusk.Keys.PadLeft					= Dusk.Keys.Pad4;
Dusk.Keys.PadRight				= Dusk.Keys.Pad6;
Dusk.Keys.PadHome					= Dusk.Keys.Pad7;
Dusk.Keys.PadUp					= Dusk.Keys.Pad8;
Dusk.Keys.PadPageUp				= Dusk.Keys.Pad9;
Dusk.Keys.PadDelete				= Dusk.Keys.PadDecimal;
