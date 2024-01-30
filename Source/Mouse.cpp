#include "Mouse.h"

int Mouse::mouseX = 0;;
int Mouse::mouseY = 0;
bool Mouse::mouseL = false;
bool Mouse::mouseR = false;
bool Mouse::mouseM = false;

int Mouse::GetMouseX()
{
	return mouseX;
}

int Mouse::GetMouseY()
{
	return mouseY;
}

bool Mouse::GetMouseButton(int button)
{
	switch (button)
	{
	case 0:
		return mouseL;
	case 1:
		return mouseR;
	case 2:
		return mouseM;
	default:
		return false;
	}
}

void Mouse::SetMousePos(int x, int y)
{
	mouseX = x;
	mouseY = y;
}

void Mouse::SetMouseL()
{
	mouseL = true;
}

void Mouse::SetMouseR()
{
	mouseR = true;
}

void Mouse::SetMouseM()
{
	mouseM = true;
}

void Mouse::ReleaseMouseL()
{
	mouseL = false;
}

void Mouse::ReleaseMouseR()
{
	mouseR = false;
}

void Mouse::ReleaseMouseM()
{
	mouseM = false;
}
