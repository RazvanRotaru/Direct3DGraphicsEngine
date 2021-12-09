#include "Window.h"

Window::WindowClass Window::WindowClass::wndClass;


Window::WindowClass::WindowClass() noexcept : hInstance(GetModuleHandle(nullptr)) {
	WNDCLASSEX wc = {
		sizeof(wc),		// cbSize
		CS_OWNDC,		// style
		HandleMsgSetup,	// lpfnWndProc
		0,				// cbClsExtra
		0,				// cvWndExtra
		GetInstance(),		// hInstance
		nullptr,		// hIcon
		nullptr,		// hCursor
		nullptr,		// hbrBackground
		nullptr,		// lpszMenuName
		GetName(),	// lpszClassName
		nullptr			// hIconSm
	};

	RegisterClassEx(&wc);
}

Window::WindowClass::~WindowClass() {
	UnregisterClass(GetName(), GetInstance());
}

const LPCWSTR Window::WindowClass::GetName() noexcept {
	return wndClassName;
}

HINSTANCE Window::WindowClass::GetInstance() noexcept {
	return wndClass.hInstance;
}

Window::Window(int width, int height, LPCWSTR name) noexcept {
	RECT wr = {
		100L,
		100L,
		width + 100L,
		height + 100L
	};
	this->width = width;
	this->height = height;

	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

	hWnd = CreateWindow(
		WindowClass::GetName(),						// lpClassName
		name,										// lpWindowName
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,	// dwStyle
		CW_USEDEFAULT, CW_USEDEFAULT,				// let Windows decide x, y
		wr.right - wr.left,							// nWidth
		wr.bottom - wr.top,							// nHeight
		nullptr,									// hWndParent
		nullptr,									// hMenu
		WindowClass::GetInstance(),					// hInstance
		this										// lpParam
	);

	ShowWindow(hWnd, SW_SHOW);
}

Window::~Window() {
	DestroyWindow(hWnd);
}

LRESULT CALLBACK Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept {
	if (msg == WM_CREATE) {
		const CREATESTRUCT* const pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
		Window* const pWnd = reinterpret_cast<Window*>(pCreate->lpCreateParams);

		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));

		return pWnd->HandlMsg(hWnd, msg, wParam, lParam);
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept {
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	return pWnd->HandlMsg(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandlMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept {
	switch (msg) {
	case WM_CLOSE:
		PostQuitMessage(105);
		return 0;

	// Handle input
	case WM_KEYDOWN:
		if (wParam == '*') {}
		break;
	case WM_CHAR:
		// TODO: register input in textBuffer
		break;

	/*
	WM_xBUTTON_DOWN
		-> wParam: mask of modifiers (MK_SHIFT | MK_CONTROLL)
		-> lParam: (int16 x-coordinate, int16 y-coordinate)
			*usage* int16 GET_X_LPARAM(lParam) or POINTS MAKEPOINTS(lParam)
	*/
	case WM_LBUTTONDOWN:
		// TODO: handle left click
		break;
	case WM_RBUTTONDOWN:
		// TODO: handle right-click
		break;
	case WM_MBUTTONDOWN:
		// TODO: handle middle-click
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
