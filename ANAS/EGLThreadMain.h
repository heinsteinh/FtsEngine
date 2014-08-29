#pragma once

//https://chromium.googlesource.com/angle/angle/+/testbranchthree/tests/standalone_tests/EGLThreadTest.cpp

#include "Libs.h"

#define GL_GLEXT_PROTOTYPES

#include <EGL/egl.h>
#include <EGL/eglext.h>

namespace ANAS
{
	typedef EGLAPI EGLDisplay EGLAPIENTRY EGLGetDisplay(EGLNativeDisplayType display_id);
	typedef EGLAPI EGLBoolean EGLAPIENTRY EGLInitialize(EGLDisplay dpy, EGLint *major, EGLint *minor);
	typedef EGLAPI EGLContext EGLAPIENTRY EGLGetCurrentContext(void);
	typedef EGLAPI EGLSurface EGLAPIENTRY EGLGetCurrentSurface(EGLint readdraw);


	class EGLThreadMain
	{
	public:
		virtual void Init() {}
		virtual void ShutDown() {}

		EGLGetDisplay *mGetDisplay;
		EGLInitialize *mInitialize;

		EGLGetCurrentContext *mGetCurrentContext;
		EGLGetCurrentSurface *mGetCurrentSurface;

		EGLDisplay mDisplay;

		HMODULE mEGL;
		HMODULE mGLESv2;

		static DWORD WINAPI ThreadingMainEntryPoint(LPVOID thisPointer);

	private:
		void ThreadingTest();
	};

}

/*

DWORD threadId;
HANDLE threadHandle = CreateThread(NULL, 0, EGLThreadTest::ThreadingTestEntryPoint, this, 0, &threadId);
EXPECT_TRUE(threadHandle != NULL);
// wait for signal from thread
DWORD waitResult = WaitForSingleObject(threadHandle, 1000);
EXPECT_EQ(waitResult, WAIT_OBJECT_0);
// crash, because the TLS value is NULL on main thread
mGetCurrentSurface(EGL_DRAW);
mGetCurrentContext();
*/