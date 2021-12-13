#include "App.h"
#include "Math.h"
#include "GDIPlusManager.h"
#include "Surface.h"
#include "Cube.h"
#include "Actor.h"
#include "Mesh.h"
#include <sstream>
#include <iomanip>

#include "Transform.h"
#include "Renderer.h"

GDIPlusManager gdipm;

App::App() : wnd(800, 600, TEXT("MG3D_Engine")), camera(wnd.GFX()) {
	// TEST GDI+
	const auto s = Surface::FromFile("Resources\\Textures\\gokuh.jpg");
	//drawables.push_back(std::make_unique<Cube>(wnd.GFX()));

	// TODO store width and height in window
	wnd.GFX().SetProjection(Math::Projection(1.0f, 4.0f / 3.0f, 0.5f, 60.0f));
	actor = new Actor(wnd.GFX(), nullptr);
	mesh = new Mesh(Mesh::Type::Cube);
	actor->SetMesh(mesh);

	// TODO use smart pointers
	//drawables.push_back((Drawable*)(actor->GetRenderer()));
	actors.push_back(std::unique_ptr<Actor>(actor));
	pointLight = new PointLight(wnd.GFX());
	

	// Test Hierarchy
	{

		Actor* plActor = new Actor(wnd.GFX(), pointLight->GetTransform());
		plActor->GetTransform()->SetScale(Vector3(0.5f, 0.5f, 0.5f));
		plActor->GetRenderer()->SetPixelShader(TEXT("SolidPixelShader.cso"));
		plActor->SetMesh(mesh);
		actors.push_back(std::unique_ptr<Actor>(plActor));
	}
	{
		Actor* plActor = new Actor(wnd.GFX(), pointLight->GetTransform());
		plActor->GetTransform()->SetScale(Vector3(0.5f, 0.5f, 0.5f));
		plActor->GetTransform()->SetPosition(Vector3(3.0f, 0.0f, 0.0f));
		plActor->GetRenderer()->SetPixelShader(TEXT("SolidPixelShader.cso"));
		plActor->SetMesh(mesh);
		actors.push_back(std::unique_ptr<Actor>(plActor));
	}
	{
		Actor* plActor;
		plActor = new Actor(wnd.GFX(), pointLight->GetTransform());
		plActor->GetTransform()->SetScale(Vector3(0.5f, 0.5f, 0.5f));
		plActor->GetTransform()->SetPosition(Vector3(-3.0f, 0.0f, 0.0f));
		plActor->GetTransform()->SetRotation(Vector3(45.0f, 45.0f, 45.0f));
		plActor->GetRenderer()->SetPixelShader(TEXT("SolidPixelShader.cso"));
		plActor->SetMesh(mesh);
		actors.push_back(std::unique_ptr<Actor>(plActor));
	}
	{
		Actor* plActor = new Actor(wnd.GFX(), pointLight->GetTransform());
		plActor->GetRenderer()->SetPixelShader(TEXT("SolidPixelShader.cso"));
		plActor->SetMesh(mesh);
		actors.push_back(std::unique_ptr<Actor>(plActor));
	}
	pointLight->GetTransform()->Move(Vector3(0.0f, 10.0f, -3.0f));
	pointLight->GetTransform()->Rotate(Vector3(40.0f, 0.0f, 0.0f));

	camera.GetTransform()->Move(Vector3(0.0f, 0.0f, -20.0f));
}

App::~App() {}


HRESULT App::Run() {
	while (TRUE) {
		// TODO: make it nicer
		wnd.mouse.OnNewFrame();
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
	//oss << "Mouse position: (" << wnd.GetMouseDelta().x << ", " << wnd.GetMouseDelta().y << ")";
	oss << "Camera position: (" << camera.GetTransform()->GetPosition().x << ", "
		<< camera.GetTransform()->GetPosition().y << ", "
		<< camera.GetTransform()->GetPosition().z << ")";
	wnd.SetTitle(oss.str());

	const float c = sin(timer.Peek()) * 0.5f;

	const auto mousePosition = wnd.GetMousePosition();

	wnd.GFX().BeginFrame(0.0f, 0.0f, 0.0f);
	wnd.GFX().SetCamera(camera.GetViewMatrix());

	UpdateViewport(dt);

	pointLight->Bind();

	//for (auto& d : drawables) {
	//	if (typeid(d) == typeid(Actor)) {
	//		continue;
	//	}

	//	d->Update(wnd.kbd.KeyPressed(VK_SPACE) ? 0.0f : mousePosition.x, 
	//				wnd.kbd.KeyPressed(VK_SPACE) ? 0.0f : mousePosition.y);
	//	d->Draw(wnd.GFX());
	//}

	for (auto& actor : actors) {
		actor->Tick(dt);
	}

	pointLight->Draw();

	wnd.GFX().EndFrame();
}

void App::UpdateViewport(float delta) noexcept {
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

	if (wnd.mouse.ButtonPressed(Mouse::Button::Right)) {
		const auto mousePosition = wnd.GetMouseDelta();
		camera.Rotate(mousePosition.x, mousePosition.y);
	}

	camera.SetViewport();
}
