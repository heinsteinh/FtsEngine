#pragma once


#include "Libs.h"
#include "Logger.h"

#include "Task.h"
#include "TaskScheduler.h"
#include "ThreadSync.h"

#include <Windows.h>

namespace ANAS {

	


	class ANativeWindow;
	class Graphic : public core::TaskManager , public Signal 
	{

	private:
		typedef std::function<LRESULT CALLBACK(HWND, UINT, WPARAM, LPARAM)> WNDPROC_FUNC;
		//typedef LRESULT(CALLBACK Graphic::*WNDPROC)(HWND, UINT, WPARAM, LPARAM);

		WNDPROC_FUNC*	mCallbackFunction;
		HINSTANCE  hInstance;

		EGLDisplay eglDisplay;
		EGLSurface eglSurface;
		EGLContext eglContext;
		EGLConfig  eglConfig;
		
	public:

		static int Width;
		static int Height;

		Graphic(WNDPROC_FUNC*);
		~Graphic();


		void Init(HINSTANCE _window);

		
		void Term();


		void Swap(float r, float g, float b, float a);

		
		void InitTask();
		
		void TermTask();
		
		void SwapTask(float r, float g, float b, float a);



		static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);
	};
}