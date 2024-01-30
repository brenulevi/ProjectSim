#pragma once

class Mouse
{
	friend class Window;
private:
	static int mouseX;
	static int mouseY;
	static bool mouseL;
	static bool mouseR;
	static bool mouseM;

public:
	Mouse() = delete;

	static int GetMouseX();
	static int GetMouseY();
	static bool GetMouseButton(int button);

private:
	static void SetMousePos(int x, int y);
	static void SetMouseL();
	static void SetMouseR();
	static void SetMouseM();

	static void ReleaseMouseL();
	static void ReleaseMouseR();
	static void ReleaseMouseM();
};

