#pragma once

#include <windows.h>

#include <windows.h>
#include <functional>

/*
namespace  BaseWindow_ {
	class BaseWindow {

		static LRESULT CALLBACK internal_WndProc(HWND hWnd, int msg, WORD wParam, LONG lParam)
		{
			BaseWindow *c = (BaseWindow *)GetWindowLong(hWnd, GWLP_USERDATA);

			if (c == NULL)
				return DefWindowProc(hWnd, msg, wParam, lParam);

			return c->WindowProc(hWnd, msg, wParam, lParam);
		}

	public:
		virtual int WindowProc(HWND hWnd, int msg, WPARAM wParam, LPARAM lParam) = 0;

		BaseWindow(HINSTANCE instance)
		{
			WNDCLASS window_class = { 0 };

			HWND window;
			HMENU my_menu;

			window_class.lpfnWndProc = (WNDPROC)internal_WndProc;

			// fill in window_class here 
			RegisterClass(&window_class);

			window = CreateWindow(
				TEXT("My Application"), TEXT("Stupidity"),
				WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT, CW_USEDEFAULT,
				CW_USEDEFAULT, CW_USEDEFAULT,
				NULL, my_menu, instance, NULL);

			// save the address of the class as the Window's USERDATA.
			SetWindowLong(window, GWLP_USERDATA, (long)this);
		}
	};
}
*/



namespace testWinAPI
{
	class Engine;
	class Win32
	{
	public:
		Win32() {};
		~Win32() {};
	
		typedef std::function<LRESULT CALLBACK(HWND, UINT, WPARAM, LPARAM)> WNDPROC_FXN;

		void Initialize(WNDPROC_FXN p);
		


	private:
		// Route messages to non static WindowProc that is declared in Engine class.
		static LRESULT CALLBACK MessageRouter(HWND, UINT, WPARAM, LPARAM);
	};

	void Win32::Initialize(WNDPROC_FXN p)
	{
	}

	class Engine
	{
	public:
		Engine() {};
		~Engine() {};

		void Initialize();

	private:
		LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

		Win32* m_win32;
	};


	//void Engine::Initialize()
	//{
	//	m_win32 = new Win32;
	//	m_win32->Initialize(&Engine::WindowProc);  // How can I pass this function without making
	//	// it static or global.
	//}

	void Engine::Initialize()
	{
		using namespace std::placeholders;

		m_win32 = new Win32;
		//m_win32->Initialize(&Engine::WindowProc);
		//m_win32->Initialize(std::bind(&Engine::WindowProc, this, _1, _2, _3, _4));
	
	}
}
