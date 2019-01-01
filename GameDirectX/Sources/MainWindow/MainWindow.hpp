#pragma once

#include "../Core/Window/RenderWindow.hpp"
#include "../Core/Input/InputListener.hpp"



class MainWindow final : public core::RenderWindow, core::InputListener
{
public:
	MainWindow();
	~MainWindow();

private:
	LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) override;

	void processInput(const core::WindowInput & windowInput) override;
};
