#pragma once


#include <array>
#include <variant>

#include "InputCodes.hpp"

#include "../Common/Log.hpp"


namespace core
{
namespace Input
{
	struct KeyPressed
	{
		Keyboard key;
	};

	struct KeyPressedOnce : KeyPressed {};

	struct KeyReleased : KeyPressedOnce {};

	struct MouseButtonPressedOnce
	{
		Mouse button;
		POINT position;
	};

	struct MouseButtonReleased : MouseButtonPressedOnce {};

	struct DoubleClick : MouseButtonPressedOnce {};

	struct MouseMove
	{
		POINT oldPosition;
		POINT position;
	};

	struct MouseWheel
	{
		std::int16_t wheel;
		POINT position;
	};
}

using WindowInput = std::variant<
	Input::KeyPressed,
	Input::KeyPressedOnce,
	Input::KeyReleased,
	Input::MouseButtonPressedOnce,
	Input::MouseButtonReleased,
	Input::DoubleClick,
	Input::MouseMove,
	Input::MouseWheel
>;

class InputListener
{
protected:
	InputListener();
	virtual ~InputListener();

	void inputUpdate(UINT msg, WPARAM wParam, LPARAM lParam);

	virtual void processInput(const WindowInput & windowInput);

	static bool keyIsPresssed(Keyboard key);
	static bool mouseButtonIsPresssed(Mouse button);

private:
	static POINT getMousePosition(LPARAM lParam);

	static std::array<bool, 256> keyboard;
	static std::array<bool, 5> mouse;

	static POINT oldMousePosition;
};
}
