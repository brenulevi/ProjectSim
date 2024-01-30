#pragma once

class Keyboard
{
	friend class Window;
private:
	static bool keys[256];

public:
	Keyboard() = delete;

	static bool GetKey(char key);
private:
	static void SetKey(char key);
	static void ReleaseKey(char key);
};

