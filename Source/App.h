#pragma once

#include <vector>
#include <memory>

#include "Window.h"
#include "Cube.h"
#include "Timer.h"

class App
{
private:
	Window cWnd;
	Timer timer;

	std::vector<std::unique_ptr<Cube>> cubes;
public:
	App();
	~App() = default;

	int Run();
	void Frame();
};