#pragma once

#include <windows.h>

class Timer
{
private:
	LARGE_INTEGER start, end;
	LARGE_INTEGER freq;
	float last;

public:
	Timer();

	float Peek();
	float FrameTime();
};

