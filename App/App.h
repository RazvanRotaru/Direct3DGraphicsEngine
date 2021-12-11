#pragma once
#include "Window.h"
#include "Timer.h"

class App {
public:
	App();
	HRESULT Run();
private:
	void Tick();
private:
	Window wnd;
	Timer timer;
};

