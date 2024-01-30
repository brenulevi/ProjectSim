#pragma once

#include <memory>

#include "IDrawable.h"

class Cube : public IDrawable
{
private:
	float xView;
	float yView;
	float zView;
	float xMove;
	float yMove;
	float zMove;
	float xSpeed;
	float ySpeed;
	float zSpeed;

public:
	Cube(Graphics& gfx, float xSpeed, float ySpeed, float zSpeed);

	void Update(float deltaTime);
	DX::XMMATRIX GetTransformMatrix();
};

