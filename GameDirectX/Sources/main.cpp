#include "MainWindow/MainWindow.hpp"



int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR cmdLine, int show)
{
	try
	{
		core::Log::begin(L"LOG.txt");

		core::RenderWindow::registerDefWC();

		MainWindow window;
		window.create(L"Main window", show, { 600, 600 });

		WPARAM wParam = window.run();

		core::RenderWindow::unregisterDefWC();

		core::Log::end();

		return static_cast<int>(wParam);
	}
	catch (std::exception & e)
	{
		std::string error{ core::toString("Terminate by: ", e.what()) };

		MessageBoxExA(nullptr, error.c_str(), "Error", MB_OK,
			MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
	}

	return 0;
}
