#include "App.h"
#include "Math.h"
#include "GDIPlusManager.h"
#include "Surface.h"
#include "Cube.h"
#include <sstream>
#include <iomanip>

GDIPlusManager gdipm;

App::App() : wnd(800, 600, TEXT("MG3D_Engine")) {
	// TEST GDI+
	const auto s = Surface::FromFile("Resources\\Textures\\gokuh.jpg");
	drawables.push_back(std::make_unique<Cube>(wnd.GFX()));

	// TODO store width and height in window
	wnd.GFX().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
}

App::~App() {}


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

	const float c = sin(timer.Peek()) * 0.5f;

	float dx = Math::ClipCoursor(wnd.mouse.GetPosX(), 800);
	float dy = Math::ClipCoursor(wnd.mouse.GetPosY(), 600);
	
	wnd.GFX().BeginFrame(c, 1.0f, 1.0f);
	for (auto& d : drawables) {
		d->Update(wnd.kbd.KeyPressed(VK_SPACE) ? 0.0f : dx, wnd.kbd.KeyPressed(VK_SPACE) ? 0.0f : dy);
		d->Draw(wnd.GFX());
	}

	wnd.GFX().EndFrame();
}