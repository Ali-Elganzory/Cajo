#pragma once

/*
	From glfw3.h
*/

namespace Cajo {

	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}

}

/* The unknown key */
#define CAJO_KEY_UNKNOWN            -1

/* Printable keys */
#define CAJO_KEY_SPACE           ::Cajo::Key::Space
#define CAJO_KEY_APOSTROPHE      ::Cajo::Key::Apostrophe    /* ' */
#define CAJO_KEY_COMMA           ::Cajo::Key::Comma         /* , */
#define CAJO_KEY_MINUS           ::Cajo::Key::Minus         /* - */
#define CAJO_KEY_PERIOD          ::Cajo::Key::Period        /* . */
#define CAJO_KEY_SLASH           ::Cajo::Key::Slash         /* / */
#define CAJO_KEY_0               ::Cajo::Key::D0
#define CAJO_KEY_1               ::Cajo::Key::D1
#define CAJO_KEY_2               ::Cajo::Key::D2
#define CAJO_KEY_3               ::Cajo::Key::D3
#define CAJO_KEY_4               ::Cajo::Key::D4
#define CAJO_KEY_5               ::Cajo::Key::D5
#define CAJO_KEY_6               ::Cajo::Key::D6
#define CAJO_KEY_7               ::Cajo::Key::D7
#define CAJO_KEY_8               ::Cajo::Key::D8
#define CAJO_KEY_9               ::Cajo::Key::D9
#define CAJO_KEY_SEMICOLON       ::Cajo::Key::Semicolon     /* ; */
#define CAJO_KEY_EQUAL           ::Cajo::Key::Equal         /* = */
#define CAJO_KEY_A               ::Cajo::Key::A
#define CAJO_KEY_B               ::Cajo::Key::B
#define CAJO_KEY_C               ::Cajo::Key::C
#define CAJO_KEY_D               ::Cajo::Key::D
#define CAJO_KEY_E               ::Cajo::Key::E
#define CAJO_KEY_F               ::Cajo::Key::F
#define CAJO_KEY_G               ::Cajo::Key::G
#define CAJO_KEY_H               ::Cajo::Key::H
#define CAJO_KEY_I               ::Cajo::Key::I
#define CAJO_KEY_J               ::Cajo::Key::J
#define CAJO_KEY_K               ::Cajo::Key::K
#define CAJO_KEY_L               ::Cajo::Key::L
#define CAJO_KEY_M               ::Cajo::Key::M
#define CAJO_KEY_N               ::Cajo::Key::N
#define CAJO_KEY_O               ::Cajo::Key::O
#define CAJO_KEY_P               ::Cajo::Key::P
#define CAJO_KEY_Q               ::Cajo::Key::Q
#define CAJO_KEY_R               ::Cajo::Key::R
#define CAJO_KEY_S               ::Cajo::Key::S
#define CAJO_KEY_T               ::Cajo::Key::T
#define CAJO_KEY_U               ::Cajo::Key::U
#define CAJO_KEY_V               ::Cajo::Key::V
#define CAJO_KEY_W               ::Cajo::Key::W
#define CAJO_KEY_X               ::Cajo::Key::X
#define CAJO_KEY_Y               ::Cajo::Key::Y
#define CAJO_KEY_Z               ::Cajo::Key::Z
#define CAJO_KEY_LEFT_BRACKET    ::Cajo::Key::LeftBracket   /* [ */
#define CAJO_KEY_BACKSLASH       ::Cajo::Key::Backslash     /* \ */
#define CAJO_KEY_RIGHT_BRACKET   ::Cajo::Key::RightBracket  /* ] */
#define CAJO_KEY_GRAVE_ACCENT    ::Cajo::Key::GraveAccent   /* ` */
#define CAJO_KEY_WORLD_1         ::Cajo::Key::World1        /* non-US #1 */
#define CAJO_KEY_WORLD_2         ::Cajo::Key::World2        /* non-US #2 */

/* Function keys */
#define CAJO_KEY_ESCAPE          ::Cajo::Key::Escape
#define CAJO_KEY_ENTER           ::Cajo::Key::Enter
#define CAJO_KEY_TAB             ::Cajo::Key::Tab
#define CAJO_KEY_BACKSPACE       ::Cajo::Key::Backspace
#define CAJO_KEY_INSERT          ::Cajo::Key::Insert
#define CAJO_KEY_DELETE          ::Cajo::Key::Delete
#define CAJO_KEY_RIGHT           ::Cajo::Key::Right
#define CAJO_KEY_LEFT            ::Cajo::Key::Left
#define CAJO_KEY_DOWN            ::Cajo::Key::Down
#define CAJO_KEY_UP              ::Cajo::Key::Up
#define CAJO_KEY_PAGE_UP         ::Cajo::Key::PageUp
#define CAJO_KEY_PAGE_DOWN       ::Cajo::Key::PageDown
#define CAJO_KEY_HOME            ::Cajo::Key::Home
#define CAJO_KEY_END             ::Cajo::Key::End
#define CAJO_KEY_CAPS_LOCK       ::Cajo::Key::CapsLock
#define CAJO_KEY_SCROLL_LOCK     ::Cajo::Key::ScrollLock
#define CAJO_KEY_NUM_LOCK        ::Cajo::Key::NumLock
#define CAJO_KEY_PRINT_SCREEN    ::Cajo::Key::PrintScreen
#define CAJO_KEY_PAUSE           ::Cajo::Key::Pause
#define CAJO_KEY_F1              ::Cajo::Key::F1
#define CAJO_KEY_F2              ::Cajo::Key::F2
#define CAJO_KEY_F3              ::Cajo::Key::F3
#define CAJO_KEY_F4              ::Cajo::Key::F4
#define CAJO_KEY_F5              ::Cajo::Key::F5
#define CAJO_KEY_F6              ::Cajo::Key::F6
#define CAJO_KEY_F7              ::Cajo::Key::F7
#define CAJO_KEY_F8              ::Cajo::Key::F8
#define CAJO_KEY_F9              ::Cajo::Key::F9
#define CAJO_KEY_F10             ::Cajo::Key::F10
#define CAJO_KEY_F11             ::Cajo::Key::F11
#define CAJO_KEY_F12             ::Cajo::Key::F12
#define CAJO_KEY_F13             ::Cajo::Key::F13
#define CAJO_KEY_F14             ::Cajo::Key::F14
#define CAJO_KEY_F15             ::Cajo::Key::F15
#define CAJO_KEY_F16             ::Cajo::Key::F16
#define CAJO_KEY_F17             ::Cajo::Key::F17
#define CAJO_KEY_F18             ::Cajo::Key::F18
#define CAJO_KEY_F19             ::Cajo::Key::F19
#define CAJO_KEY_F20             ::Cajo::Key::F20
#define CAJO_KEY_F21             ::Cajo::Key::F21
#define CAJO_KEY_F22             ::Cajo::Key::F22
#define CAJO_KEY_F23             ::Cajo::Key::F23
#define CAJO_KEY_F24             ::Cajo::Key::F24
#define CAJO_KEY_F25             ::Cajo::Key::F25

/* Keypad */
#define CAJO_KEY_KP_0            ::Cajo::Key::KP0
#define CAJO_KEY_KP_1            ::Cajo::Key::KP1
#define CAJO_KEY_KP_2            ::Cajo::Key::KP2
#define CAJO_KEY_KP_3            ::Cajo::Key::KP3
#define CAJO_KEY_KP_4            ::Cajo::Key::KP4
#define CAJO_KEY_KP_5            ::Cajo::Key::KP5
#define CAJO_KEY_KP_6            ::Cajo::Key::KP6
#define CAJO_KEY_KP_7            ::Cajo::Key::KP7
#define CAJO_KEY_KP_8            ::Cajo::Key::KP8
#define CAJO_KEY_KP_9            ::Cajo::Key::KP9
#define CAJO_KEY_KP_DECIMAL      ::Cajo::Key::KPDecimal
#define CAJO_KEY_KP_DIVIDE       ::Cajo::Key::KPDivide
#define CAJO_KEY_KP_MULTIPLY     ::Cajo::Key::KPMultiply
#define CAJO_KEY_KP_SUBTRACT     ::Cajo::Key::KPSubtract
#define CAJO_KEY_KP_ADD          ::Cajo::Key::KPAdd
#define CAJO_KEY_KP_ENTER        ::Cajo::Key::KPEnter
#define CAJO_KEY_KP_EQUAL        ::Cajo::Key::KPEqual

/* Control Keys*/
#define CAJO_KEY_LEFT_SHIFT      ::Cajo::Key::LeftShift
#define CAJO_KEY_LEFT_CONTROL    ::Cajo::Key::LeftControl
#define CAJO_KEY_LEFT_ALT        ::Cajo::Key::LeftAlt
#define CAJO_KEY_LEFT_SUPER      ::Cajo::Key::LeftSuper
#define CAJO_KEY_RIGHT_SHIFT     ::Cajo::Key::RightShift
#define CAJO_KEY_RIGHT_CONTROL   ::Cajo::Key::RightControl
#define CAJO_KEY_RIGHT_ALT       ::Cajo::Key::RightAlt
#define CAJO_KEY_RIGHT_SUPER     ::Cajo::Key::RightSuper
#define CAJO_KEY_MENU            ::Cajo::Key::Menu