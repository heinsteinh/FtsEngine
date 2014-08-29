// ANAS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <windows.h>
#include <stdio.h>
#include <tchar.h>


#if defined(WIN32)
# include <cstdio>
# define LOGI(...) printf(__VA_ARGS__); printf("\r\n")
# define LOGW(...) printf(__VA_ARGS__); printf("\r\n")
# define LOGE(...) printf(__VA_ARGS__); printf("\r\n")
#endif


#include "Libs.h"
#include "TaskScheduler.h"
#include "GraphicTask.h"
#include "BridgeParameter.h"
#include "GameModule.h"


#include "EglDisplay.h"
#include "ClearTest.h"

//https://chromium.googlesource.com/angle/angle/+/testbranchthree/tests/angle_tests/win32/ANGLETest_win32.cpp

#include <stdio.h>
#include <crtdbg.h>
#include <typeinfo>
inline void EnableMemLeakCheck()
{
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
}


typedef TCHAR  *PTCHAR;

#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0) 
#define KEYUP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)


#include "sys/timeb.h"
float total_time;
struct _timeb beg, end;
#define FRAME 10
unsigned int frame = 0;


typedef std::function<LRESULT CALLBACK(HWND, UINT, WPARAM, LPARAM)> FUNC;


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 1;

	case WM_KEYDOWN:
	{
	int virtual_code = (int)wParam;
	int key_bits = (int)lParam;
	switch (virtual_code)
	{
	case VK_ESCAPE: PostQuitMessage(0);
		break;

	case VK_LEFT: {}
		break;
	default:
		break;

		return (0);
	}
	}

	default:
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}


static const PTCHAR GetTestWindowName()
{
	return TEXT("TEST");
}


bool ANAS::EglDisplay::InitTestWindow()
{

	RECT wRect;
	HINSTANCE hInstance;

	wRect.left = 128L;
	wRect.right = (long)320;
	wRect.top = 128L;
	wRect.bottom = (long)480;

	hInstance = GetModuleHandle(NULL);

	WNDCLASS sWC;


	sWC.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	sWC.lpfnWndProc =  (WNDPROC)WndProc;
	sWC.cbClsExtra = 0;
	sWC.cbWndExtra = 0;
	sWC.hInstance = hInstance;
	sWC.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	sWC.hCursor = LoadCursor(NULL, IDC_ARROW);
	sWC.hbrBackground = NULL;
	sWC.lpszMenuName = NULL;
	sWC.lpszClassName = GetTestWindowName();


	if (!RegisterClass(&sWC))
	{
		return false;
	}


	AdjustWindowRectEx(&wRect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);	
	mNativeWindow = CreateWindowEx(

		WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
		GetTestWindowName(), TEXT("OpenGL ES2 HelloTriangle"),
		WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		128, 128,
		wRect.right - wRect.left, wRect.bottom - wRect.top,
		NULL, NULL,
		hInstance,
		NULL
		);


	//SetWindowLong(mNativeWindow, GWL_STYLE, 0);
	ShowWindow(mNativeWindow, SW_SHOW);

	SetForegroundWindow(mNativeWindow);
	SetFocus(mNativeWindow);


	mNativeDisplay = GetDC(mNativeWindow);
	if (!mNativeDisplay)
	{
		DestroyTestWindow();
		return false;
	}
		
	
	mDisplay = eglGetDisplay(mNativeDisplay);
	if (mDisplay == EGL_NO_DISPLAY)
	{
		mDisplay = eglGetDisplay((EGLNativeDisplayType)EGL_DEFAULT_DISPLAY);
	}
	EGLint majorVersion, minorVersion;
	if (!eglInitialize(mDisplay, &majorVersion, &minorVersion))
	{
		DestroyTestWindow();
		return false;
	}
	printf("EglDisplay initialized. Egl version %d.%d\n", majorVersion, minorVersion);

	eglBindAPI(EGL_OPENGL_ES_API);
	if (eglGetError() != EGL_SUCCESS)
	{
		DestroyTestWindow();
		return false;
	}

	GL_CHECK
	
	return true;
}

bool ANAS::EglDisplay::DestroyTestWindow()
{
	eglMakeCurrent(mDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	eglTerminate(mDisplay);
	if (mNativeDisplay)
	{
		ReleaseDC(mNativeWindow, mNativeDisplay);
		mNativeDisplay = 0;
	}
	if (mNativeWindow)
	{
		DestroyWindow(mNativeWindow);
		mNativeWindow = 0;
	}

	GL_CHECK

	UnregisterClass(GetTestWindowName(), NULL);
	return true;
}


bool ANAS::EglDisplay::ReizeWindow(int width, int height)
{
	RECT windowRect;
	if (!GetWindowRect(mNativeWindow, &windowRect))
	{
		return false;
	}
	if (!MoveWindow(mNativeWindow, windowRect.left, windowRect.top, width, height, FALSE))
	{
		return false;
	}
	return true;
}


EGLNativeWindowType  ANAS::EglDisplay::GetNativeWindow()
{
	return mNativeWindow;
}



void Main(ANAS::BridgeParameter* arg)
{
	std::unique_ptr< ANAS::BridgeParameter > param(arg);
		
	MSG msg;
	HINSTANCE hInstance = GetModuleHandle(NULL);

	//ANAS::Input mInput;
	//ANAS::Graphic  mGraphic(&(WNDPROC)WndProc);

	param->Notification();
}


#include "TuxisWindow.h"

int _tmain(int argc, _TCHAR* argv[])
{
	
	const int WIDTH = 50 + 170 + 50;
	const int HEIGHT = 50 + 340 + 20;
	
	MSG msg;
	ANAS::Input mInput;
	mInput.Init(&msg);

	Tuxis::Window mWindow;
	mWindow.Create(WIDTH, HEIGHT, L"TuxiTrix", true);

	BOOL bDone = FALSE;
	MSG sMessage;
	char buffer[128];

		

	while (!bDone)
	{
		if (PeekMessage(&sMessage, NULL, 0, 0, PM_REMOVE))
		{
			if (sMessage.message == WM_QUIT)
			{
				bDone = true;
			}
			else
			{
				TranslateMessage(&sMessage);
				DispatchMessage(&sMessage);
			}
		}
	}


	Sleep(100);
	mWindow.Release();

	return 0;

	/*
	BOOL bDone = FALSE;
	std::shared_ptr<ANAS::ANGLETestEnvironment> pApp(new ANAS::ANGLETestEnvironment());
	std::shared_ptr<ANAS::ClearTest> pGrpahic(new ANAS::ClearTest());

	pApp->InitUp();
	pGrpahic->Init();


	EnableMemLeakCheck();

	MSG sMessage;
	char buffer[128];
	while (!bDone)
	{
		if (PeekMessage(&sMessage, NULL, 0, 0, PM_REMOVE))
		{
			if (sMessage.message == WM_QUIT)
			{
				bDone = true;
			}
			else
			{
				TranslateMessage(&sMessage);
				DispatchMessage(&sMessage);
			}
		}

		if (frame == 0)
			_ftime64_s(&beg);

		pGrpahic->Render();


		if (frame == FRAME)
		{
			_ftime64_s(&end);
			total_time = (float)(end.time - beg.time) + (float)(end.millitm - beg.millitm) / 1000;
			sprintf_s(buffer, "OpenGL ES2 HelloTriangle(fps: %.2f)", (float)(FRAME + 1) / total_time);
			SetWindowTextA(ANAS::EglDisplay::GetNativeWindow(), buffer);
			frame = 0;
		}
		else
		{
			++frame;
		}

		Sleep(20);
	}

	pGrpahic->ShutDown();
	pApp->ShutDown();
	*/
	return 0;

}





/*
HINSTANCE hInstance = GetModuleHandle(NULL);


ANAS::BridgeParameter *param = new ANAS::BridgeParameter(NULL, NULL, 0);

// Create main thread
std::thread MainThread(&Main, param);


//// Wait( blocking )
param->Wait();


if (MainThread.joinable())
MainThread.join();

*/

/*
while (glGetError() != GL_NO_ERROR){ assert(false); }

BOOL bDone = FALSE;
std::shared_ptr<ANAS::ANGLETestEnvironment> pApp(new ANAS::ANGLETestEnvironment());
std::shared_ptr<ANAS::ClearTest> pGrpahic(new ANAS::ClearTest());

pApp->InitUp();
pGrpahic->Init();


EnableMemLeakCheck();

MSG sMessage;
char buffer[128];
while (!bDone)
{
if (PeekMessage(&sMessage, NULL, 0, 0, PM_REMOVE))
{
if (sMessage.message == WM_QUIT)
{
bDone = true;
}
else
{
TranslateMessage(&sMessage);
DispatchMessage(&sMessage);
}
}

if (frame == 0)
_ftime64_s(&beg);

pGrpahic->Render();


if (frame == FRAME)
{
_ftime64_s(&end);
total_time = (float)(end.time - beg.time) + (float)(end.millitm - beg.millitm) / 1000;
sprintf_s(buffer, "OpenGL ES2 HelloTriangle(fps: %.2f)", (float)(FRAME + 1) / total_time);
SetWindowTextA(ANAS::Graphic::GetNativeWindow(), buffer);
frame = 0;
}
else
{
++frame;
}

Sleep(20);
}

pGrpahic->ShutDown();
pApp->ShutDown();
*/