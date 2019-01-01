#include "MainWindow.hpp"



MainWindow::MainWindow() = default;

MainWindow::~MainWindow() = default;

LRESULT MainWindow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	inputUpdate(msg, wParam, lParam);

	if (msg == WM_CLOSE)
	{
		TRY(PostMessageW(hWnd, WM_QUIT, NULL, NULL));
	}
	else
		return DefWindowProcW(hWnd, msg, wParam, lParam);

	return 0;
}

void MainWindow::processInput(const core::WindowInput & windowInput)
{
	std::visit(core::match{
		[&](core::Input::KeyPressedOnce input)
		{
			if (input.key == core::Keyboard::Easape)
				close();

			if (input.key == core::Keyboard::F11)
				switchFullscreenMode();
		},
		[](auto) {}
	}, windowInput);
}
