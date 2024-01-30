#include "Timer.h"

Timer::Timer()
	:
	last(0.0f)
{
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);

	ZeroMemory(&end, sizeof(end));
}

float Timer::Peek()
{
	QueryPerformanceCounter(&end);

	long long delta = end.QuadPart - start.QuadPart;

	return float(delta / double(freq.QuadPart));
}

float Timer::FrameTime()
{
	float old = last;
	last = Peek();

	float elapsed = last - old;

	return elapsed;
}


