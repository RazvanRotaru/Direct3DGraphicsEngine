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
	void Tick();

	void UpdateViewport(float delta) noexcept;
private:
	Window wnd;
	Camera camera;
	Timer timer;

	// TODO use smart pointers
	//std::vector<class Drawable*> drawables;

	std::vector<std::unique_ptr<Actor>> actors;

	// TEst
	PointLight* pointLight;
	class Actor* actor;
	class Mesh* mesh;
};

