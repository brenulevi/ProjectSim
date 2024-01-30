#pragma once

#include <windows.h>
#include <optional>

#include "Graphics.h"
#include "Keyboard.h"
#include "Mouse.h"

class Window
{
private:
	Graphics graphics;

	HWND hWnd;
	float fWidth;
	float fHeight;
	const char* sTitle;

public:
	Window(float width, float height, const char* title);
	~Window();

	inline Graphics& getGFX();
	inline HWND getId() const;
	inline float getWidth() const;
	inline float getHeight() const;
	inline const char* getTitle() const;

	std::optional<int> ProcessMessage() const;

private:
	static LRESULT CALLBACK WinProcThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK WinProcSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

inline Graphics& Window::getGFX() { return graphics; }
inline HWND Window::getId() const { return hWnd; }
inline float Window::getWidth() const { return fWidth; }
inline float Window::getHeight() const { return fHeight; }
inline const char* Window::getTitle() const { return sTitle; }
