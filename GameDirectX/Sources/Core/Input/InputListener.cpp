#include "InputListener.hpp"



namespace core
{
InputListener::InputListener() = default;

InputListener::~InputListener() = default;

void InputListener::inputUpdate(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
	{
		if (!keyboard.at(static_cast<std::size_t>(wParam)))
		{
			keyboard.at(static_cast<std::size_t>(wParam)) = true;
			processInput({ Input::KeyPressedOnce{ static_cast<Keyboard>(wParam) } });
		}
		keyboard.at(static_cast<std::size_t>(wParam)) = true;
		processInput({ Input::KeyPressed{ static_cast<Keyboard>(wParam) } });
		break;
	}

	case WM_KEYUP:
	{
		keyboard.at(static_cast<std::size_t>(wParam)) = false;
		processInput({ Input::KeyReleased{ static_cast<Keyboard>(wParam) } });
		break;
	}

	case WM_LBUTTONDOWN:
	{
		mouse.at(static_cast<std::size_t>(Mouse::LeftButton)) = true;
		processInput({ Input::MouseButtonPressedOnce{ Mouse::LeftButton, getMousePosition(lParam) } });
		break;
	}

	case WM_LBUTTONUP:
	{
		mouse.at(static_cast<std::size_t>(Mouse::LeftButton)) = false;
		processInput({ Input::MouseButtonReleased{ Mouse::LeftButton, getMousePosition(lParam) } });
		break;
	}

	case WM_LBUTTONDBLCLK:
	{
		processInput({ Input::DoubleClick{ Mouse::LeftButton, getMousePosition(lParam) } });
		break;
	}

	case WM_RBUTTONDOWN:
	{
		mouse.at(static_cast<std::size_t>(Mouse::RightButton)) = true;
		processInput({ Input::MouseButtonPressedOnce{ Mouse::RightButton, getMousePosition(lParam) } });
		break;
	}

	case WM_RBUTTONUP:
	{
		mouse.at(static_cast<std::size_t>(Mouse::RightButton)) = false;
		processInput({ Input::MouseButtonReleased{ Mouse::RightButton, getMousePosition(lParam) } });
		break;
	}

	case WM_RBUTTONDBLCLK:
	{
		processInput({ Input::DoubleClick{ Mouse::RightButton, getMousePosition(lParam) } });
		break;
	}

	case WM_MBUTTONDOWN:
	{
		mouse.at(static_cast<std::size_t>(Mouse::MiddleButton)) = true;
		processInput({ Input::MouseButtonPressedOnce{ Mouse::MiddleButton, getMousePosition(lParam) } });
		break;
	}

	case WM_MBUTTONUP:
	{
		mouse.at(static_cast<std::size_t>(Mouse::MiddleButton)) = false;
		processInput({ Input::MouseButtonReleased{ Mouse::MiddleButton, getMousePosition(lParam) } });
		break;
	}

	case WM_MBUTTONDBLCLK:
	{
		processInput({ Input::DoubleClick{ Mouse::MiddleButton, getMousePosition(lParam) } });
		break;
	}

	case WM_XBUTTONDOWN:
	{
		Mouse button{ HIWORD(wParam) == XBUTTON1 ?
			Mouse::XButton1 : Mouse::XButton2 };
		mouse.at(static_cast<std::size_t>(button)) = true;
		processInput({ Input::MouseButtonPressedOnce{ button, getMousePosition(lParam) } });
		break;
	}

	case WM_XBUTTONUP:
	{
		Mouse button{ HIWORD(wParam) == XBUTTON1 ?
			Mouse::XButton1 : Mouse::XButton2 };
		mouse.at(static_cast<std::size_t>(button)) = false;
		processInput({ Input::MouseButtonReleased{ button, getMousePosition(lParam) } });
		break;
	}

	case WM_XBUTTONDBLCLK:
	{
		processInput({ Input::DoubleClick{ HIWORD(wParam) == XBUTTON1 ? Mouse::XButton1
			: Mouse::XButton2, getMousePosition(lParam) } });
		break;
	}

	case WM_MOUSEMOVE:
	{
		POINT position = getMousePosition(lParam);

		if (oldMousePosition.x == -1 && oldMousePosition.y == -1)
			oldMousePosition = position;

		processInput({ Input::MouseMove{ oldMousePosition, position } });
		oldMousePosition = position;
	}

	case WM_MOUSEWHEEL:
	{
		processInput({ Input::MouseWheel{ GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA,
			getMousePosition(lParam) } });
		break;
	}
	}
}

void InputListener::processInput(const WindowInput & windowInput) {}

bool InputListener::keyIsPresssed(Keyboard key)
{
	return keyboard.at(static_cast<std::size_t>(key));
}

bool InputListener::mouseButtonIsPresssed(Mouse button)
{
	return mouse.at(static_cast<std::size_t>(button));
}

POINT InputListener::getMousePosition(LPARAM lParam)
{
	return { static_cast<std::uint16_t>(LOWORD(lParam)),
		static_cast<std::uint16_t>(HIWORD(lParam)) };
}

std::array<bool, 256> InputListener::keyboard;
std::array<bool, 5> InputListener::mouse;

POINT InputListener::oldMousePosition{ -1, -1 };
}
