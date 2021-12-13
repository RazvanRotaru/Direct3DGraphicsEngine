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

	void UpdateCamera(float delta) noexcept;
private:
	Window wnd;
	Camera camera;
	Timer timer;
	std::vector<std::unique_ptr<class Drawable>> drawables;

	// TEst
	PointLight* pointLight;
	class Actor* actor;
	class Mesh* mesh;
};

