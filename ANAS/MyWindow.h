#pragma once
//window.h__________________________________

//#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

namespace win
{
	struct InputStruct{
		bool spacedown;
		bool wdown;
		bool adown;
		bool sdown;
		bool ddown;
		bool shiftdown;
	};

	class windowclass{
	public:
		WNDCLASSEX wndClass;
		HWND window;
		windowclass::windowclass(HINSTANCE &instance);
		RECT windowSize;



		static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);
	};

	LRESULT CALLBACK WndProc(HWND wnd, UINT message, WPARAM wParam, LPARAM lParam);
}