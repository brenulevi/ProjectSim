#include "Window.h"

Window::Window(float width, float height, const char* title) :
	fWidth(width), fHeight(height), sTitle(title), hWnd(NULL)
{
	WNDCLASSEX wndClass{};
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.lpfnWndProc = WinProcSetup;
	wndClass.lpszClassName = "SimWindowClass";
	wndClass.hInstance = GetModuleHandle(NULL);
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = NULL;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_OWNDC;
	
	RegisterClassEx(&wndClass);

	RECT winRect = { 0, 0, int(width), int(height) };

	AdjustWindowRectEx(&winRect, WS_OVERLAPPEDWINDOW, FALSE, NULL);

	int w = winRect.right - winRect.left;
	int h = winRect.bottom - winRect.top;

	hWnd = CreateWindowEx(
		NULL,
		wndClass.lpszClassName,
		sTitle,
		WS_OVERLAPPEDWINDOW,
		int((GetSystemMetrics(SM_CXSCREEN) / 2.0f) - (w / 2.0f)),
		int((GetSystemMetrics(SM_CYSCREEN) / 2.0f) - (h / 2.0f)),
		w,
		h,
		NULL,
		NULL,
		GetModuleHandle(NULL),
		NULL
	);

	ShowWindow(hWnd, SW_SHOW);
	
	graphics = Graphics(hWnd, (int)width, (int)height);
}

Window::~Window()
{
}

std::optional<int> Window::ProcessMessage() const
{
	MSG msg{};

	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return (int)msg.wParam;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return {};
}

LRESULT CALLBACK Window::WinProcSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_NCCREATE || msg == WM_CREATE)
	{
		const CREATESTRUCT* const pCreate = (CREATESTRUCT*)lParam;
		Window* pWnd = (Window*)pCreate->lpCreateParams;
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pWnd);
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)&Window::WinProcThunk);
		return pWnd->WinProc(hWnd, msg, wParam, lParam);
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK Window::WinProcThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Window* pWnd = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	return pWnd->WinProc(hWnd, msg, wParam, lParam);
}

#include <iostream>

LRESULT CALLBACK Window::WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		Keyboard::SetKey((char)wParam);
		break;
	case WM_KEYUP:
		Keyboard::ReleaseKey((char)wParam);
		break;
	case WM_MOUSEMOVE:
		auto coords = MAKEPOINTS(lParam);
		Mouse::SetMousePos(coords.x, coords.y);
		break;
	case WM_LBUTTONDOWN:
		Mouse::SetMouseL();
		break;
	case WM_RBUTTONDOWN:
		Mouse::SetMouseR();
		break;
	case WM_MBUTTONDOWN:
		Mouse::SetMouseM();
		break;
	case WM_LBUTTONUP:
		Mouse::ReleaseMouseL();
		break;
	case WM_RBUTTONUP:
		Mouse::ReleaseMouseR();
		break;
	case WM_MBUTTONUP:
		Mouse::ReleaseMouseM();
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}