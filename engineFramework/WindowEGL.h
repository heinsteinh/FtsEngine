#pragma once


#include <Windows.h>
#include "string"

using namespace std;


#define GL_GLEXT_PROTOTYPES

#include <EGL/egl.h>
#include <EGL/eglext.h>


#include "VideoSystem.h"
namespace Tuxis
{
	//https://github.com/mhyhre/Tuxis-Engine/blob/master/Includes/Window.h

	class WindowEGL;
	typedef LRESULT(CALLBACK WindowEGL::*WNDPROC)(HWND, UINT, WPARAM, LPARAM);

	class  WindowEGL : public core::Window
	{
	private:

		bool mCreated;
		HWND mWindowHandler;

		bool mEnableButtonBox;
		wstring mCaption;
		wstring mClassName;

		HINSTANCE hInstance;

		/*<  EGL>*/
		EGLConfig mConfig;
		EGLSurface mSurface;
		EGLContext mContext;

		static EGLDisplay mDisplay;
		//static EGLNativeWindowType mNativeWindow;
		static EGLNativeDisplayType mNativeDisplay;
		/*<  EGL>*/

	public:

		WindowEGL(int pWidth, int pHeight, const WCHAR* pCaption, bool EnableButtonBox);
		WindowEGL();

		~WindowEGL();

		//void create(int pWidth, int pHeight, const WCHAR* pCaption, bool EnableButtonBox);
		void SetWindow(HWND pHWND, int pWidth, int pHeight);
		

		//missing input...
		virtual void render(double fTimeElapsed);
		virtual void update(double fTimeElapsed);
		virtual bool create();
		virtual void destroy();
		virtual void run();

		bool IsRunning();
		void Release();

		HWND GetHWND();


	private:
		bool createEGLContext();
		bool destroyEGLContext();
		bool extensionEnabled(const std::string &extName);

		int mClientVersion;
		/*int mWidth;
		int mHeight;*/
		int mRedBits;
		int mGreenBits;
		int mBlueBits;
		int mAlphaBits;
		int mDepthBits;
		int mStencilBits;
		bool mMultisample;


	public:
		typedef std::shared_ptr<Tuxis::WindowEGL> Ptr;
	};



	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

}

