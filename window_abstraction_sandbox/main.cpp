#include "Window.h"

#include <iostream>

/**
 * Entry point
 */
int WINAPI wWinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE p, _In_ PWSTR lpCmdLine, _In_ int nCmdShow)
{
	Window game_window(1366u, 768u, L"Game Window");
	game_window.SetWindowTitle(L"Window");

	while (game_window.ProcessMessages() != WM_QUIT)
	{
	}

	return 0;
}