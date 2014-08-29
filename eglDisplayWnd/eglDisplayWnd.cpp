// eglDisplayWnd.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
// This file will run on windows 32
#ifdef _WIN32

#include <windows.h>
#include <cstdio>


#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <algorithm>


// OpenGL Math:
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>


#define SCREEN_W 800
#define SCREEN_H 480

#define SAFE_DEL(p) if (p) delete p; p = 0;
#define SAFE_DEL_ARRAY(p) if (p) delete []p; p = 0;

#include <string>


#include "Application.h"
#include "Log.h"



//https://github.com/huytd/ko2d/tree/a2743c3fe247339e3d2483f289054bb8b9ffbc8b/Engine

// EGL variables
EGLDisplay	eglDisplay = 0;
EGLConfig	eglConfig = 0;
EGLSurface	eglSurface = 0;
EGLContext	eglContext = 0;
EGLNativeWindowType	eglWindow = 0;
// Windows variables
HWND	hWnd = 0;
HDC	hDC = 0;
void CleanUp();
bool TestEGLError(HWND hWnd, char* pszLocation);
bool Init(GLuint width, GLuint height);
//---------------------------------------------------------------------------



//-----------------------
int main(int n, char **args)
{
	if (Init(SCREEN_W, SCREEN_H) == false)
		return -1;

	LOG_WARNING << "putting task";

	Application application = Application::GetInstance();
	
	if (application.Init("../../../../Resource") == false)
		return -1;

	MSG msg = { 0 };
	int done = 0;
	DWORD lastTime = GetTickCount();

	while (!done)
	{
		int gotMsg = (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0);
		DWORD curTime = GetTickCount();
		float deltaTime = (float)(curTime - lastTime) / 1000.0f;
		lastTime = curTime;

		if (gotMsg)
		{
			if (msg.message == WM_QUIT)
			{
				done = 1;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			application.Render();
			eglSwapBuffers(eglDisplay, eglSurface);
		}

		application.Update(deltaTime);
	}

	application.Destroy();

	return 0;
}



LRESULT CALLBACK WndProcedure(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{

	LRESULT lRet = 1;
	int x = LOWORD(lParam);
	int y = HIWORD(lParam);
	static bool mouseDown = false;

	switch (Msg)
	{
	case WM_CREATE:
		break;

	case WM_DESTROY:
		PostQuitMessage(WM_QUIT);
		break;

	case WM_KEYDOWN:
		//Input::GetInstance()->OnKey((unsigned char)wParam, true);
		break;
	case WM_KEYUP:
		//Input::GetInstance()->OnKey((unsigned char)wParam, false);
		break;
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
		mouseDown = true;
		//Input::GetInstance()->OnPointer(POINTER_DOWN, x, y, -1, -1);
		break;

	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
		mouseDown = false;
		//Input::GetInstance()->OnPointer(POINTER_UP, x, y, -1, -1);
		break;
	case WM_MOUSEMOVE:
		if (mouseDown)
		{
			//Input::GetInstance()->OnPointer(POINTER_DRAGGED, x, y, -1, -1);
		}
		break;
	default:
		lRet = DefWindowProc(hWnd, Msg, wParam, lParam);
		break;
	}

	return lRet;
}

bool TestEGLError(HWND hWnd, char* pszLocation)
{
	EGLint iErr = eglGetError();
	if (iErr != EGL_SUCCESS)
	{
		char pszStr[256];
		
		sprintf_s(pszStr, ("%s failed (%d).\n"), pszLocation, (int)iErr);
		MessageBox(hWnd, (TCHAR*)pszStr, _T("Error"), MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	return true;
}

void CleanUp()
{
	eglMakeCurrent(eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

	eglTerminate(eglDisplay);

	if (hDC)
		ReleaseDC(hWnd, hDC);

	if (hWnd)
		DestroyWindow(hWnd);
}


bool Init(GLuint width, GLuint height)
{
	HINSTANCE hInstance = GetModuleHandle(NULL);

	// Register the windows class
	WNDCLASS sWC;
	sWC.style = CS_HREDRAW | CS_VREDRAW;
	sWC.lpfnWndProc = WndProcedure; //Procedute Callback Event
	sWC.cbClsExtra = 0;
	sWC.cbWndExtra = 0;
	sWC.hInstance = hInstance;
	sWC.hIcon = 0;
	sWC.hCursor = 0;
	sWC.lpszMenuName = 0;
	sWC.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	sWC.lpszClassName = _T("OpenGLES2.0");


	ATOM registerClass = RegisterClass(&sWC);
	if (!registerClass)
	{
		MessageBox(0, _T("Failed to register the window class"), _T("Error"), MB_OK | MB_ICONEXCLAMATION);
	}
	// Create the eglWindow
	RECT	sRect;
	SetRect(&sRect, 0, 0, SCREEN_W, SCREEN_H);
	AdjustWindowRectEx(&sRect, WS_CAPTION | WS_SYSMENU, false, 0);
	hWnd = CreateWindow(_T("OpenGLES2.0"), _T("HEngine"), WS_VISIBLE | WS_SYSMENU,
		0,0, sRect.right - sRect.left, sRect.bottom - sRect.top, NULL, NULL, hInstance, NULL);
	eglWindow = hWnd;

	// Get the associated device context
	hDC = GetDC(hWnd);
	if (!hDC)
	{
		MessageBox(0, _T("Failed to create the device context"), _T("Error"), MB_OK | MB_ICONEXCLAMATION);
		CleanUp();
		return false;
	}

	eglDisplay = eglGetDisplay(hDC);

	if (eglDisplay == EGL_NO_DISPLAY)
		eglDisplay = eglGetDisplay((EGLNativeDisplayType)EGL_DEFAULT_DISPLAY);

	EGLint iMajorVersion, iMinorVersion;
	if (!eglInitialize(eglDisplay, &iMajorVersion, &iMinorVersion))
	{
		MessageBox(0, _T("eglInitialize() failed."), _T("Error"), MB_OK | MB_ICONEXCLAMATION);
		CleanUp();
		return false;
	}
	printf("\nVersion: %d %d\n", iMajorVersion, iMinorVersion);



	/******************************/

	const EGLint pi32ConfigAttribs_[] =
	{
		EGL_LEVEL, 0,
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL_NATIVE_RENDERABLE, EGL_FALSE,
		EGL_DEPTH_SIZE, 8,
		EGL_STENCIL_SIZE, 8,
		//EGL_SAMPLE_BUFFERS, 1,
		EGL_NONE
	};

	const EGLint pi32ConfigAttribs[] =
	{
		EGL_RED_SIZE, 5,
		EGL_GREEN_SIZE, 5,
		EGL_BLUE_SIZE, 5,
		EGL_ALPHA_SIZE, 1,
		EGL_BUFFER_SIZE, 16,
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_DEPTH_SIZE, 1,
		EGL_STENCIL_SIZE, false,
		EGL_SAMPLE_BUFFERS, 0,
		EGL_SAMPLES, 0,
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL_NONE, 0
	};

	int iConfigs;
	if (!eglChooseConfig(eglDisplay, pi32ConfigAttribs, &eglConfig, 1, &iConfigs) || (iConfigs != 1))
	{
		MessageBox(0, _T("eglChooseConfig() failed."), _T("Error"), MB_OK | MB_ICONEXCLAMATION);
		CleanUp();
		return false;
	}


	eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, eglWindow, NULL);

	if (eglSurface == EGL_NO_SURFACE)
	{
		eglGetError(); // Clear error
		eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, NULL, NULL);
	}

	if (!TestEGLError(hWnd, "eglCreateWindowSurface"))
	{
		CleanUp();
		return false;
	}


	// Bind the API (It could be OpenGLES or OpenVG)
	eglBindAPI(EGL_OPENGL_ES_API);
	EGLint ai32ContextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
	eglContext = eglCreateContext(eglDisplay, eglConfig, NULL, ai32ContextAttribs);

	if (!TestEGLError(hWnd, ("eglCreateContext")))
	{
		CleanUp();
		return false;
	}


	eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext);

	if (!TestEGLError(hWnd, "eglMakeCurrent"))
	{
		CleanUp();
		return false;
	}

	GL_CHECK

	glViewport(0, 0, SCREEN_W , SCREEN_H );
	GL_CHECK

	return true;
}

#endif