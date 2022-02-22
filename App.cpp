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

App::App() {
	imgui = std::make_unique<ImGUIManager>();
	wnd = std::make_unique<Window>(800, 600, TEXT("MG3D_Engine"));
	collMgr = std::make_unique<CollisionManager>();
	luaMgr = std::make_unique<LuaManager>();

	// TEST GDI+
	const auto s = Surface::FromFile("Resources\\Textures\\gokuh.jpg");
	//drawables.push_back(std::make_unique<Cube>(wnd.GFX()));
	camera = std::make_unique<Camera>(wnd->GFX());

	// TODO store width and height in window
	wnd->GFX().SetProjection(Math::Projection(1.0f, 4.0f / 3.0f, 0.5f, 60.0f));
	actor = new Actor(wnd->GFX(), nullptr);
	mesh = new Mesh(Mesh::Type::Cube);
	actor->SetMesh(mesh);


	 //TODO use smart pointers
	//drawables.push_back((Drawable*)(actor->GetRenderer()));
	actors.push_back(std::unique_ptr<Actor>(actor));
	pointLight = new PointLight(wnd->GFX());


	// Test Hierarchy
	{
		Actor* plActor = new Actor(wnd->GFX(), pointLight->GetTransform());
		plActor->GetTransform()->SetScale(Vector3(0.5f, 0.5f, 0.5f));
		plActor->GetRenderer()->SetPixelShader(TEXT("SolidPixelShader.cso"));
		plActor->SetMesh(mesh);
		actors.push_back(std::unique_ptr<Actor>(plActor));
	}
	{
		Actor* plActor = new Actor(wnd->GFX(), pointLight->GetTransform());
		plActor->GetTransform()->SetScale(Vector3(0.5f, 0.5f, 0.5f));
		plActor->GetTransform()->SetPosition(Vector3(3.0f, 0.0f, 0.0f));
		plActor->GetRenderer()->SetPixelShader(TEXT("SolidPixelShader.cso"));
		plActor->SetMesh(mesh);
		actors.push_back(std::unique_ptr<Actor>(plActor));
	}
	{
		Actor* plActor = new Actor(wnd->GFX(), pointLight->GetTransform());
		plActor->GetTransform()->SetScale(Vector3(0.5f, 0.5f, 0.5f));
		plActor->GetTransform()->SetPosition(Vector3(3.2f, 0.2f, 0.0f));
		plActor->GetRenderer()->SetPixelShader(TEXT("SolidPixelShader.cso"));
		plActor->SetMesh(mesh);
		actors.push_back(std::unique_ptr<Actor>(plActor));
	}
	{
		Actor* plActor;
		plActor = new Actor(wnd->GFX(), pointLight->GetTransform());
		plActor->GetTransform()->SetScale(Vector3(0.5f, 0.5f, 0.5f));
		plActor->GetTransform()->SetPosition(Vector3(-3.0f, 0.0f, 0.0f));
		plActor->GetTransform()->SetRotation(Vector3(45.0f, 45.0f, 45.0f));
		plActor->GetRenderer()->SetPixelShader(TEXT("SolidPixelShader.cso"));
		plActor->SetMesh(mesh);
		actors.push_back(std::unique_ptr<Actor>(plActor));
	}
	{
		Actor* plActor = new Actor(wnd->GFX(), pointLight->GetTransform());
		plActor->GetRenderer()->SetPixelShader(TEXT("SolidPixelShader.cso"));
		plActor->SetMesh(mesh);
		actors.push_back(std::unique_ptr<Actor>(plActor));
	}
	pointLight->GetTransform()->Move(Vector3(0.0f, 10.0f, -3.0f));
	//pointLight->GetTransform()->Move(Vector3(0.0f, 2.0f, -7.0f));
	//pointLight->GetTransform()->Move(Vector3(13.0f, 10.0f, -5.0f));
	pointLight->GetTransform()->Rotate(Vector3(40.0f, 0.0f, 0.0f));

	camera->GetTransform()->Move(Vector3(0.0f, 0.0f, 20.0f));
}

App::~App() {}


HRESULT App::Run() {
	while (TRUE) {
		// TODO: make it nicer
		wnd->mouse.OnNewFrame();
		if (const auto errCode = Window::ProcessMessages()) {
			return static_cast<HRESULT>(*errCode);
		}
		const float dt = timer.Mark();

		BeforeTick(dt);
		Tick(dt);
		AfterTick(dt);
	}
}

void App::Tick(float dt) {
	for (auto& actor : actors) {
		actor->Tick(dt);
	}

	collMgr->CheckCollisions();
	imgui->DrawGui();
}

void App::BeforeTick(float dt) {
	wnd->GFX().BeginFrame(0.0f, 0.0f, 0.0f);

	UpdateViewport(dt);
	wnd->GFX().SetCamera(camera->GetViewMatrix());

	pointLight->Bind();
}

void App::AfterTick(float dt) {
	pointLight->Draw();
	wnd->GFX().EndFrame();
}

void App::UpdateViewport(float delta) noexcept {
	if (wnd->kbd.KeyPressed('W')) {
		camera->Move({ 0.0f, 0.0f, delta });
	}
	if (wnd->kbd.KeyPressed('S')) {
		camera->Move({ 0.0f, 0.0f, -delta });
	}
	if (wnd->kbd.KeyPressed('A')) {
		camera->Move({ delta, 0.0f, 0.0f });
	}
	if (wnd->kbd.KeyPressed('D')) {
		camera->Move({ -delta, 0.0f, 0.0f });
	}
	if (wnd->kbd.KeyPressed('Q')) {
		camera->Move({ 0.0f, -delta , 0.0f });
	}
	if (wnd->kbd.KeyPressed('E')) {
		camera->Move({ 0.0f, delta, 0.0f });
	}

	if (wnd->mouse.ButtonPressed(Mouse::Button::Right)) {
		const auto mousePosition = wnd->GetMouseDelta();
		camera->Rotate(mousePosition.x, mousePosition.y);
	}

	camera->SetViewport();
}
