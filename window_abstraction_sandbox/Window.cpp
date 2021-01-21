#include "Window.h"

Window::Window(unsigned int pw, unsigned int ph, const WCHAR* pwindow_title)
{
	mhInst = GetModuleHandle(nullptr);

	WNDCLASSEX w;
	w.cbSize = sizeof(WNDCLASSEX);
	w.style = 0;
	w.lpfnWndProc = MSGInit;
	w.cbClsExtra = 0;
	w.cbWndExtra = 0;
	w.hInstance = mhInst;
	w.hIcon = nullptr;
	w.hCursor = nullptr;
	w.hbrBackground = nullptr;
	w.lpszMenuName = nullptr;
	w.lpszClassName = L"GameWindow";
	w.hIconSm = nullptr;

	RegisterClassEx(&w);

	mhWnd = CreateWindow(
		L"GameWindow",
		pwindow_title,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
		0, 0,
		pw, ph,
		nullptr,
		nullptr,
		mhInst,
		nullptr
	);

	if (!mhWnd)
	{
		MessageBox(nullptr, L"Window Creation failed", L"Initialization Error", MB_OK);
		return;
	}
	ShowWindow(mhWnd, SW_SHOW);
}

Window::~Window()
{
	DestroyWindow(mhWnd);
}

HINSTANCE Window::GetInstance()
{
	return mhInst;
}

void Window::SetWindowTitle(const WCHAR* new_title)
{
	SetWindowText(mhWnd, new_title);
}

UINT Window::ProcessMessages()
{
	MSG m;
	while (PeekMessage(&m, nullptr, 0, 0, PM_REMOVE))
	{
		if (m.message == WM_QUIT)
		{
			return WM_QUIT;
		}

		TranslateMessage(&m);
		DispatchMessage(&m);
	}

	return 0;
}

LRESULT Window::MSGInit(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_CREATE)
	{
		// extract ptr to window class from creation data
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		// set WinAPI-managed user data to store ptr to window instance
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		// set message proc to normal (non-setup) handler now that setup is finished
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::MSGMiddleWare));
		// forward message to window instance handler
		return pWnd->MSGMiddleWare(hWnd, message, wParam, lParam);
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT Window::MSGMiddleWare(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// Grab window instance ptr
	Window* const windowptr = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	// Call the instance message handler
	return windowptr->HandleMSG(hWnd, message, wParam, lParam);
}

LRESULT Window::HandleMSG(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
