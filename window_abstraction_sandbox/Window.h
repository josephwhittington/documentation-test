#pragma once

#include "lean_windows.h"

class Window
{
public:
	Window(unsigned int pw, unsigned int ph, const WCHAR* pwindow_title);
	~Window();

	// Getters / setters
	HINSTANCE GetInstance();

	void SetWindowTitle(const WCHAR* new_title);

	UINT ProcessMessages();

	static LRESULT CALLBACK MSGInit(HWND   hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK MSGMiddleWare(HWND   hWnd, UINT   message, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK HandleMSG(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	HINSTANCE mhInst;
	HWND mhWnd;

	WCHAR* mwindowTitle = nullptr;
};