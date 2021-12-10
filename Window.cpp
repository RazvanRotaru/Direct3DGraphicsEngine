#include "Window.h"
#include <sstream>

Window::WindowClass Window::WindowClass::wndClass;


Window::WindowClass::WindowClass() noexcept : hInstance(GetModuleHandle(nullptr)) {
	WNDCLASSEX wc = {
		sizeof(wc),		// cbSize
		CS_OWNDC,		// style
		HandleMsgSetup,	// lpfnWndProc
		0,				// cbClsExtra
		0,				// cvWndExtra
		GetInstance(),	// hInstance
		nullptr,		// hIcon
		nullptr,		// hCursor
		nullptr,		// hbrBackground
		nullptr,		// lpszMenuName
		GetName(),		// lpszClassName
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

Window::Window(int width, int height, LPCWSTR name) : width(width), height(height) {
	RECT wr = {
		100L,
		100L,
		width + 100L,
		height + 100L
	};

	if (!AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE)) {
		throw CHWND_LAST_EXCEPT();
	}

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

	if (hWnd == nullptr) { throw CHWND_LAST_EXCEPT(); }

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

	/************************* HANDLE INPUT *************************/

	case WM_KILLFOCUS:
		kbd.ClearState();
		// TODO: maybe clear mouse state too
		break;

	/************ HANDLE KEYBOARD INPUT ************/
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		if (!(lParam & (1 << 30)) || kbd.IsAutorepeatEnabled()) {
			kbd.OnKeyPressed(static_cast<unsigned char>(wParam));
		}
		break;
	
	case WM_KEYUP:
	case WM_SYSKEYUP:
		kbd.OnKeyReleased(static_cast<unsigned char>(wParam));
		break;
	
	case WM_CHAR:
		kbd.OnChar(static_cast<unsigned char>(wParam));
		break;

	/************ HANDLE MOUSE INPUT ************/
	/*
	WM_xBUTTON_DOWN
		-> wParam: mask of modifiers (MK_SHIFT | MK_CONTROLL)
		-> lParam: (int16 x-coordinate, int16 y-coordinate)
			*usage* int16 GET_X_LPARAM(lParam) or POINTS MAKEPOINTS(lParam)
	*/
	//case WM_LBUTTONDOWN:
	//	// TODO: handle left click
	//	break;
	//case WM_RBUTTONDOWN:
	//	// TODO: handle right-click
	//	break;
	//case WM_MBUTTONDOWN:
	//	// TODO: handle middle-click
	//	break;
	case WM_MOUSEMOVE:
		const POINTS pt = MAKEPOINTS(lParam);
		// Coursor in client region
		if (pt.x >= 0 && pt.x < width && pt.y >= 0 && pt.y < height) {
			mouse.OnMouseMove(pt.x, pt.y);
			if (!mouse.InWindow()) {
				SetCapture(hWnd);
				mouse.OnMouseEnter();
			}
		}
		// Coursor not in client
		else {
			// Maintain capture if any button is pressed
			if (wParam & (MK_LBUTTON | MK_RBUTTON)) {
				mouse.OnMouseMove(pt.x, pt.y);
			} else {
				ReleaseCapture();
				mouse.OnMouseLeave();
			}
		}
		break;
	
	case WM_LBUTTONDOWN:
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnButtonPressed(pt.x, pt.y, Mouse::Button::Left);
		break;
	
	case WM_RBUTTONDOWN:
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnButtonPressed(pt.x, pt.y, Mouse::Button::Right);
		break;

	case WM_LBUTTONUP:
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnButtonReleased(pt.x, pt.y, Mouse::Button::Left);

		// Release mouse if outside of window
		if (pt.x < 0 || pt.x >= width || pt.y < 0 || pt.y >= height) {
			ReleaseCapture();
			mouse.OnMouseLeave();
		}
		break;
	
	case WM_RBUTTONUP:
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnButtonReleased(pt.x, pt.y, Mouse::Button::Right);

		// Release mouse if outside of window
		if (pt.x < 0 || pt.x >= width || pt.y < 0 || pt.y >= height) {
			ReleaseCapture();
			mouse.OnMouseLeave();
		}
		break;
	
	case WM_MOUSEWHEEL:
		const POINTS pt = MAKEPOINTS(lParam);
		const int delta = GET_WHEEL_DELTA_WPARAM(wParam);
		mouse.OnScrollDelta(pt.x, pt.y, delta);
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

Window::WindowException::WindowException(int line, const char* file, HRESULT hr) noexcept : EngineException(line, file), hr(hr) {}

const char* Window::WindowException::what() const noexcept {
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "Error Code: " << GetErrorCode() << std::endl
		<< "Description " << GetErrorString() << std::endl
		<< GetOriginString();

	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* Window::WindowException::GetType() const noexcept {
	return "Engine Window Exception";
}

std::string Window::WindowException::TranslateErrorCode(HRESULT hr) noexcept {
	char* pMsgBuff = nullptr;
	DWORD nMsgLen = FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPSTR>(&pMsgBuff), 0, nullptr
	);

	if (nMsgLen == 0) { return "Undefined error code"; }

	std::string errString = pMsgBuff;
	LocalFree(pMsgBuff);
	return errString;
}

HRESULT Window::WindowException::GetErrorCode() const noexcept {
	return hr;
}

std::string Window::WindowException::GetErrorString() const noexcept {
	return TranslateErrorCode(hr);
}
