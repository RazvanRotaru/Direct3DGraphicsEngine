#pragma once
#include "Window.h"
#include "Timer.h"
#include "PointLight.h"

class App {
public:
	App();
	HRESULT Run();
	~App();
private:
	void Tick(float dt);

	void BeforeTick(float dt);
	void AfterTick(float dt);
	void UpdateViewport(float delta) noexcept;
private:
	Window wnd;
	Timer timer;

	// TODO use smart pointers
	//std::vector<class Drawable*> drawables;

	std::vector<std::unique_ptr<Actor>> actors;
	std::unique_ptr<Camera> camera;

	// TEst
	PointLight* pointLight;
	class Actor* actor;
	class Mesh* mesh;
};

