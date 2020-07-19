#pragma once

/*
	From glfw3.h
*/

namespace Cajo
{
	typedef enum class MouseCode : uint16_t
	{
		// From glfw3.h
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	} Mouse;

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}

#define CAJO_MOUSE_BUTTON_0      ::Cajo::Mouse::Button0
#define CAJO_MOUSE_BUTTON_1      ::Cajo::Mouse::Button1
#define CAJO_MOUSE_BUTTON_2      ::Cajo::Mouse::Button2
#define CAJO_MOUSE_BUTTON_3      ::Cajo::Mouse::Button3
#define CAJO_MOUSE_BUTTON_4      ::Cajo::Mouse::Button4
#define CAJO_MOUSE_BUTTON_5      ::Cajo::Mouse::Button5
#define CAJO_MOUSE_BUTTON_6      ::Cajo::Mouse::Button6
#define CAJO_MOUSE_BUTTON_7      ::Cajo::Mouse::Button7
#define CAJO_MOUSE_BUTTON_LAST   ::Cajo::Mouse::ButtonLast
#define CAJO_MOUSE_BUTTON_LEFT   ::Cajo::Mouse::ButtonLeft
#define CAJO_MOUSE_BUTTON_RIGHT  ::Cajo::Mouse::ButtonRight
#define CAJO_MOUSE_BUTTON_MIDDLE ::Cajo::Mouse::ButtonMiddle