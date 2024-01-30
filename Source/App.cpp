#include "App.h"

#include <iostream>

App::App() :
	cWnd(Window(800, 600, "enquanto ela nao lembra que eu existo")),
	timer(Timer())
{
	cubes.push_back(std::make_unique<Cube>(cWnd.getGFX(), 5.0f, 4.0f, 3.0f));

	cWnd.getGFX().SetProjection(DX::XMMatrixPerspectiveLH(1.0f, cWnd.getHeight() / cWnd.getWidth(), 1.0f, 100.0f));
}
	
int App::Run()
{
	while (true)
	{
		if (const auto code = cWnd.ProcessMessage())
			return *code;

		Frame();
	}
}

void App::Frame()
{
	cWnd.getGFX().Clear(0.0f, 0.0f, 0.0f);

	for (auto& cube : cubes)
	{
		cube->Update(timer.FrameTime());
		cube->Draw(cWnd.getGFX());
	}

	cWnd.getGFX().Present();
}