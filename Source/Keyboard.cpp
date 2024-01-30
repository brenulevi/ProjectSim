#include "Keyboard.h"

bool Keyboard::keys[256] = { 0 };

bool Keyboard::GetKey(char key)
{
	return keys[key];
}

void Keyboard::SetKey(char key)
{
	keys[key] = true;
}

void Keyboard::ReleaseKey(char key)
{
	keys[key] = false;
}