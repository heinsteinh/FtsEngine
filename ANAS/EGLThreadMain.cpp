#include "stdafx.h"
#include "EGLThreadMain.h"


namespace ANAS
{


	DWORD WINAPI EGLThreadMain::ThreadingMainEntryPoint(LPVOID lpParameter)
	{
		EGLThreadMain *test = (EGLThreadMain *)lpParameter;
		test->ThreadingTest();
		return 0;
	}


	void EGLThreadMain::ThreadingTest()
	{
		mEGL = LoadLibrary(L"libEGL.dll");
		mGLESv2 = LoadLibrary(L"libGLESv2.dll");

		assert(mEGL != NULL);
		assert(mGLESv2 != NULL);

		mGetDisplay = (EGLGetDisplay *)GetProcAddress(mEGL, "eglGetDisplay");
		mInitialize = (EGLInitialize *)GetProcAddress(mEGL, "eglInitialize");
		mGetCurrentContext = (EGLGetCurrentContext *)GetProcAddress(mEGL, "eglGetCurrentContext");
		mGetCurrentSurface = (EGLGetCurrentSurface *)GetProcAddress(mEGL, "eglGetCurrentSurface");

		assert(mGetDisplay != NULL);
		assert(mInitialize != NULL);
		assert(mGetCurrentContext != NULL);
		assert(mGetCurrentSurface != NULL);

	

		assert(mDisplay != EGL_NO_DISPLAY);

		mInitialize(mDisplay, NULL, NULL);
		mGetCurrentContext();
	}
}

