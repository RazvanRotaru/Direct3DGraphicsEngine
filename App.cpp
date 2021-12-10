#include "App.h"
#include <sstream>
#include <iomanip>

App::App() : wnd(800, 600, TEXT("MG3D_Engine")) {}

HRESULT App::Run() {
	while (TRUE) {
		if (const auto errCode = Window::ProcessMessages()) {
			return static_cast<HRESULT>(*errCode);
		}

		Tick();
	}
}

void App::Tick() {
	const float t = timer.Peek();
	std::ostringstream oss;
	oss << "Frame time: " << std::setprecision(1) << std::fixed << t << "s";
	wnd.SetTitle(oss.str());
}