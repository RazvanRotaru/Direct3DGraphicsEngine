#include "Window.h"
#include <sstream>

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	try {
		const LPCWSTR lpClassName = TEXT("MG3D_Engine");
		Window wnd(800, 300, lpClassName);

		MSG msg;
		BOOL gResult;
		while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			// test code
			while (!wnd.mouse.buffer.IsEmpty()) {
				const auto e = wnd.mouse.buffer.ReadInput();
				switch (e.GetType()) {
				case Mouse::Event::Type::Leave:
					wnd.SetTitle("Gone!");
					break;
				case Mouse::Event::Type::Move:
				{
					std::ostringstream oss;
					oss << "Mouse moved to (" << e.GetPosX() << "," << e.GetPosY() << ")";
					wnd.SetTitle(oss.str());
				}
				break;
				}
			}

			if (wnd.kbd.KeyPressed(VK_MENU)) {
				MessageBox(nullptr, TEXT("DAU FLASH"), TEXT("No details available"), MB_OK | MB_ICONEXCLAMATION);
			}

		}
		return gResult >= 0 ? msg.wParam : -1;
	} catch (const EngineException& e) {
		MessageBoxA(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	} catch (const std::exception& e) {
		MessageBoxA(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	} catch (...) {
		MessageBox(nullptr, TEXT("No details available"), TEXT("Unkown Exception"), MB_OK | MB_ICONEXCLAMATION);
	}

	return -1;
}