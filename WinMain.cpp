#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_CLOSE:
		PostQuitMessage(105);
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	const LPCWSTR lpClassName = TEXT("MG3D_Engine");

	WNDCLASSEX wc = {
		sizeof(wc),		// cbSize
		CS_OWNDC,		// style
		WndProc,		// lpfnWndProc
		0,				// cbClsExtra
		0,				// cvWndExtra
		hInstance,		// hInstance
		nullptr,		// hIcon
		nullptr,		// hCursor
		nullptr,		// hbrBackground
		nullptr,		// lpszMenuName
		lpClassName,	// lpszClassName
		nullptr			// hIconSm
	};

	RegisterClassEx(&wc);

	HWND hWnd = CreateWindowEx(
		WS_EX_TRANSPARENT,							// dwExStyle
		lpClassName,								// lpClassName
		TEXT("Game Engine"),						// lpWindowName
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,	// dwStyle
		200, 200,									// X,Y -> position
		640, 480,									// nWidth, nHeight -> size
		nullptr,									// hWndParent
		nullptr,									// hMenu
		hInstance,									// hInstance
		nullptr										// lpParam
	);

	ShowWindow(hWnd, SW_SHOW);

	MSG msg;
	BOOL gResult;
	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return gResult >= 0 ? msg.wParam : -1;
}