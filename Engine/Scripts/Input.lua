if not Dusk then Dusk = { } end
if not Dusk.Input then Dusk.Input = { } end

Dusk.Input.GetInputSystem = function(inputId, key)
	return Dusk.Input.InputSystem( dusk_get_input_system() )
end

-- Dusk.Input.InputSystem

local InputSystem = DuskClass(Dusk.Events.IEventDispatcher, function(self, ptr)
	Dusk.Events.IEventDispatcher.init(self, ptr)
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

Dusk.Input.InputSystem = InputSystem

-- Dusk.Input.MouseButtons

Dusk.Input.MouseButtons = {
	Left   = 1,
	Middle = 2,
	Right  = 3,
}

-- Dusk.Input.Keys

Dusk.Input.Keys = {
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

Dusk.Input.Keys.Exclamation				= Dusk.Input.Keys.N0;
Dusk.Input.Keys.At						= Dusk.Input.Keys.N1;
Dusk.Input.Keys.Hashtag					= Dusk.Input.Keys.N2;
Dusk.Input.Keys.Pound					= Dusk.Input.Keys.Hashtag;
Dusk.Input.Keys.Dollar					= Dusk.Input.Keys.N3;
Dusk.Input.Keys.Percent					= Dusk.Input.Keys.N4;
Dusk.Input.Keys.Carrot					= Dusk.Input.Keys.N5;
Dusk.Input.Keys.Star					= Dusk.Input.Keys.N6;
Dusk.Input.Keys.Asterisk				= Dusk.Input.Keys.Star;
Dusk.Input.Keys.Ampersand				= Dusk.Input.Keys.N7;
Dusk.Input.Keys.ParenthesisOpen			= Dusk.Input.Keys.N8;
Dusk.Input.Keys.ParenthesisClose		= Dusk.Input.Keys.N9;
Dusk.Input.Keys.Minus					= Dusk.Input.Keys.Dash;
Dusk.Input.Keys.Underscore				= Dusk.Input.Keys.Minus;
Dusk.Input.Keys.Plus					= Dusk.Input.Keys.Equal;
Dusk.Input.Keys.Tilde					= Dusk.Input.Keys.Accent;
Dusk.Input.Keys.CurlyBraceOpen			= Dusk.Input.Keys.SquareBracketOpen;
Dusk.Input.Keys.CurlyBraceClose			= Dusk.Input.Keys.SquareBracketClose;
Dusk.Input.Keys.COLON					= Dusk.Input.Keys.Semicolon;
Dusk.Input.Keys.Apostrophy				= Dusk.Input.Keys.Quote;
Dusk.Input.Keys.DoubleQuote				= Dusk.Input.Keys.Quote;
Dusk.Input.Keys.Pipe					= Dusk.Input.Keys.Backslash;
Dusk.Input.Keys.LessThan				= Dusk.Input.Keys.Period;
Dusk.Input.Keys.AngleBracketOpen		= Dusk.Input.Keys.LessThan;
Dusk.Input.Keys.ChevronLeft				= Dusk.Input.Keys.LessThan;
Dusk.Input.Keys.GreaterThan				= Dusk.Input.Keys.Comma;
Dusk.Input.Keys.AngleBracketClose		= Dusk.Input.Keys.GreaterThan;
Dusk.Input.Keys.ChevronRight			= Dusk.Input.Keys.GreaterThan;
Dusk.Input.Keys.ForwardSlash			= Dusk.Input.Keys.Slash;
Dusk.Input.Keys.Questionmark			= Dusk.Input.Keys.Slash;
Dusk.Input.Keys.Break					= Dusk.Input.Keys.Pause;
Dusk.Input.Keys.SysReq					= Dusk.Input.Keys.PrintScreen;
Dusk.Input.Keys.LeftControl				= Dusk.Input.Keys.LeftCtrl;
Dusk.Input.Keys.RightControl			= Dusk.Input.Keys.RightCtrl;
Dusk.Input.Keys.LeftAlternate			= Dusk.Input.Keys.LeftAlt;
Dusk.Input.Keys.RightAlternate			= Dusk.Input.Keys.RightAlt;
Dusk.Input.Keys.LeftWindows				= Dusk.Input.Keys.LeftSuper;
Dusk.Input.Keys.RightWindows			= Dusk.Input.Keys.RightSuper;
Dusk.Input.Keys.PadInsert				= Dusk.Input.Keys.Pad0;
Dusk.Input.Keys.PadEnd					= Dusk.Input.Keys.Pad1;
Dusk.Input.Keys.PadDown					= Dusk.Input.Keys.Pad2;
Dusk.Input.Keys.PadPageDown				= Dusk.Input.Keys.Pad3;
Dusk.Input.Keys.PadLeft					= Dusk.Input.Keys.Pad4;
Dusk.Input.Keys.PadRight				= Dusk.Input.Keys.Pad6;
Dusk.Input.Keys.PadHome					= Dusk.Input.Keys.Pad7;
Dusk.Input.Keys.PadUp					= Dusk.Input.Keys.Pad8;
Dusk.Input.Keys.PadPageUp				= Dusk.Input.Keys.Pad9;
Dusk.Input.Keys.PadDelete				= Dusk.Input.Keys.PadDecimal;
