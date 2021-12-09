#include "Window.h"

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	const LPCWSTR lpClassName = TEXT("MG3D_Engine");
	
	Window wnd(800, 300, lpClassName);
	Window wnd2(300, 500, L"Cici Cichi");

	MSG msg;
	BOOL gResult;
	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return gResult >= 0 ? msg.wParam : -1;
}