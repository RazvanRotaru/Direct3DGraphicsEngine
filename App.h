#pragma once
#include "Window.h"
#include "Timer.h"

class App {
public:
	App();
	HRESULT Run();
	~App();
private:
	void Tick();
private:
	Window wnd;
	Timer timer;
	std::vector<std::unique_ptr<class Drawable>> drawables;
};

