#include "App.h"
#include "Math.h"
#include "GDIPlusManager.h"
#include "Surface.h"
#include "Cube.h"
#include "Actor.h"
#include "Mesh.h"
#include <sstream>
#include <iomanip>

GDIPlusManager gdipm;

App::App() : wnd(800, 600, TEXT("MG3D_Engine")) {
	// TEST GDI+
	const auto s = Surface::FromFile("Resources\\Textures\\gokuh.jpg");
	drawables.push_back(std::make_unique<Cube>(wnd.GFX()));

	// TODO store width and height in window
	wnd.GFX().SetProjection(Math::Projection(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
	actor = new Actor(wnd.GFX(), nullptr);
	mesh = new Mesh(Mesh::Type::Cube);
	actor->SetMesh(mesh);

	pointLight = new PointLight(wnd.GFX());
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
	const float dt = timer.Mark();
	std::ostringstream oss;
	//oss << "Frame time: " << std::setprecision(1) << std::fixed << dt << "s";
	oss << "Mouse position: (" << wnd.mouse.GetPosX() << ", " << wnd.mouse.GetPosY() << ")";
	wnd.SetTitle(oss.str());

	const float c = sin(timer.Peek()) * 0.5f;

	const auto mousePosition = wnd.GetMousePosition();

	wnd.GFX().BeginFrame(0.0f, 0.0f, 0.0f);
	wnd.GFX().SetCamera(camera.GetMatrix());

	UpdateCamera(dt);

	actor->Tick(dt);
	pointLight->Bind();

	for (auto& d : drawables) {
		if (typeid(d) == typeid(Actor)) {
			continue;
		}

		d->Update(wnd.kbd.KeyPressed(VK_SPACE) ? 0.0f : mousePosition.x, 
					wnd.kbd.KeyPressed(VK_SPACE) ? 0.0f : mousePosition.y);
		d->Draw(wnd.GFX());
	}

	pointLight->Draw();

	wnd.GFX().EndFrame();
}

void App::UpdateCamera(float delta) noexcept {
	if (wnd.kbd.KeyPressed('W')) {
		camera.Move({ 0.0f, 0.0f, delta });
	}
	if (wnd.kbd.KeyPressed('S')) {
		camera.Move({ 0.0f, 0.0f, -delta });
	}
	if (wnd.kbd.KeyPressed('A')) {
		camera.Move({ -delta, 0.0f, 0.0f });
	}
	if (wnd.kbd.KeyPressed('D')) {
		camera.Move({ delta, 0.0f, 0.0f });
	}
	if (wnd.kbd.KeyPressed('Q')) {
		camera.Move({ 0.0f, -delta , 0.0f });
	}
	if (wnd.kbd.KeyPressed('E')) {
		camera.Move({ 0.0f, delta, 0.0f });
	}

	const auto mousePosition = wnd.GetMousePosition();
	camera.Rotate(mousePosition.x, mousePosition.y);
}
