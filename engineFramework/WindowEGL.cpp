#include "stdafx.h"
#include "WindowEGL.h"
#include "log.h"

#include "Keyboard.h"

namespace Tuxis
{

	static void PrintConfigAttributes(EGLDisplay display, EGLConfig config);

	EGLDisplay WindowEGL::mDisplay = 0;
	//EGLNativeWindowType WindowEGL::mNativeWindow = 0;
	EGLNativeDisplayType WindowEGL::mNativeDisplay = 0;


	WindowEGL::WindowEGL( int pWidth, int pHeight, const WCHAR* pCaption, bool EnableButtonBox) 
		:core::Window("WindowEGL", core::Window::eWindowType::GLFW),
		mClientVersion(2),		
		mRedBits(-1),
		mGreenBits(-1),
		mBlueBits(-1),
		mAlphaBits(-1),
		mDepthBits(-1),
		mStencilBits(-1),
		mMultisample(false)
	{

		mWidth = pWidth;
		mHeight = pHeight;

		mCaption = pCaption;
		mEnableButtonBox = EnableButtonBox;

		mCreated = false;
		mClassName = L"TuxisWindowClass";
		mWindowHandler = NULL;

		// Register window class
		hInstance = GetModuleHandle(NULL);

		WNDCLASSEX wc;
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)COLOR_GRAYTEXT;
		wc.lpszMenuName = NULL;
		wc.lpszClassName = mClassName.c_str();
		wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		if (!RegisterClassEx(&wc))
		{
			gLog.error() << "Window::Window: RegisterClassEx(&wc)";
		}
	}


	WindowEGL::WindowEGL() :core::Window("WindowEGL", core::Window::eWindowType::GLFW)
	{

		mWidth = 320;
		mHeight = 480;
		mCaption = TEXT("Test");
		mEnableButtonBox = true;

		mCreated = false;
		mClassName = L"TuxisWindowClass";
		mWindowHandler = NULL;

		// Register window class
		hInstance = GetModuleHandle(NULL);

		WNDCLASSEX wc;
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)COLOR_GRAYTEXT;
		wc.lpszMenuName = NULL;
		wc.lpszClassName = mClassName.c_str();
		wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		if (!RegisterClassEx(&wc))
		{
			gLog.error() << "Window::Window: RegisterClassEx(&wc)";
		}
	}

	WindowEGL::~WindowEGL()
	{
		destroy();

	}

	bool WindowEGL::create()
	{
		if (mCreated)
		{
			gLog.error() << "Window::Create: Window already created!";
		}

		mWindowHandler = NULL;
	

		DWORD WindowStyle;

		if (mEnableButtonBox)
			WindowStyle = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX;
		else
			WindowStyle = WS_BORDER;


		mWindowHandler = CreateWindowW(
			mClassName.c_str(),
			mCaption.c_str(),
			WindowStyle,
			CW_USEDEFAULT, CW_USEDEFAULT,
			mWidth + GetSystemMetrics(SM_CXFIXEDFRAME) * 2,
			mHeight + GetSystemMetrics(SM_CYFIXEDFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),
			NULL, NULL,
			hInstance, NULL);

		if (!mWindowHandler)
		{
			gLog.error() << "Window::Window: Window not created!";
		}

		ShowWindow(mWindowHandler, SW_SHOW);
		SetForegroundWindow(mWindowHandler);
		SetFocus(mWindowHandler);
		UpdateWindow(mWindowHandler);

		mCreated = true;


		mNativeDisplay = GetDC(mWindowHandler);
		if (!mNativeDisplay)
		{
			Release();
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
			Release();
			return false;
		}

		eglBindAPI(EGL_OPENGL_ES_API);
		if (eglGetError() != EGL_SUCCESS)
		{
			Release();
			return false;
		}


		mCreated = createEGLContext();
		
		gLog<<"Window created.";

		//if (mCreated)
			//PrintConfigAttributes(mDisplay, mConfig);

		return mCreated;
	}
	
	void WindowEGL::destroy()
	{
		destroyEGLContext();
		this->Release();
	}
	

	bool WindowEGL::IsRunning()
	{
		if (mCreated)
		{
			return IsWindow(mWindowHandler) ? true : false;;
		}
		return false;
	}
	

	void WindowEGL::SetWindow(HWND pHWND, int pWidth, int pHeight)
	{
		mWindowHandler = pHWND;
		mWidth = pWidth;
		mHeight = pHeight;
		mCaption = L"";

		gLog.info() << "Window: selected exist by HWND.";
	}


	void WindowEGL::update(double fTimeElapsed)
	{

		/*static int i = 0;
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glClearColor(cosf(i), 1.0, sinf(i), 1.0);
		
		glClearDepthf(0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);*/

		

		GL_CHECK
		eglSwapBuffers(mDisplay, mSurface); 

		//i++;
	}


	void WindowEGL::run()
	{
		glGetError(); //the GLEW initialization yields an error... catch it here and ignore it (which should be safe)
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	
	}

	void WindowEGL::render(double fTimeElapsed)
	{
		update(fTimeElapsed);
	}



	void WindowEGL::Release()
	{
		if (IsWindow(mWindowHandler))
		{
			eglMakeCurrent(mDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
			eglTerminate(mDisplay);
			if (mNativeDisplay)
			{
				ReleaseDC(mWindowHandler, mNativeDisplay);
				mNativeDisplay = 0;
			}
			if (mWindowHandler)
			{
				DestroyWindow(mWindowHandler);
				mWindowHandler = 0;
			}

			if (!mClassName.empty() && !UnregisterClassW(mClassName.c_str(), hInstance))
			{
				gLog.error() << "Window::~Window: Could Not Unregister Class.";
			}

			mCreated = false;
			gLog.info() <<"Window - Released";
		}
	}


	HWND WindowEGL::GetHWND()
	{
		return mWindowHandler;
	}

	
	bool WindowEGL::extensionEnabled(const std::string &extName)
	{
		const char* extString = reinterpret_cast<const char*>(glGetString(GL_EXTENSIONS));
		return strstr(extString, extName.c_str()) != NULL;
	}


	bool WindowEGL::createEGLContext()
	{
		const EGLint configAttributes[] =
		{
			EGL_RED_SIZE, (mRedBits >= 0) ? mRedBits : EGL_DONT_CARE,
			EGL_GREEN_SIZE, (mGreenBits >= 0) ? mGreenBits : EGL_DONT_CARE,
			EGL_BLUE_SIZE, (mBlueBits >= 0) ? mBlueBits : EGL_DONT_CARE,
			EGL_ALPHA_SIZE, (mAlphaBits >= 0) ? mAlphaBits : EGL_DONT_CARE,
			EGL_DEPTH_SIZE, (mDepthBits >= 0) ? mDepthBits : EGL_DONT_CARE,
			EGL_STENCIL_SIZE, (mStencilBits >= 0) ? mStencilBits : EGL_DONT_CARE,
			EGL_SAMPLE_BUFFERS, mMultisample ? 1 : 0,
			//EGL_SAMPLES, 2,
			EGL_NONE
		};
		EGLint configCount;
		if (!eglChooseConfig(mDisplay, configAttributes, &mConfig, 1, &configCount) || (configCount != 1))
		{
			destroyEGLContext();
			return false;
		}
		eglGetConfigAttrib(mDisplay, mConfig, EGL_RED_SIZE, &mRedBits);
		eglGetConfigAttrib(mDisplay, mConfig, EGL_GREEN_SIZE, &mGreenBits);
		eglGetConfigAttrib(mDisplay, mConfig, EGL_BLUE_SIZE, &mBlueBits);
		eglGetConfigAttrib(mDisplay, mConfig, EGL_ALPHA_SIZE, &mBlueBits);
		eglGetConfigAttrib(mDisplay, mConfig, EGL_DEPTH_SIZE, &mDepthBits);
		eglGetConfigAttrib(mDisplay, mConfig, EGL_STENCIL_SIZE, &mStencilBits);
		EGLint samples;
		eglGetConfigAttrib(mDisplay, mConfig, EGL_SAMPLE_BUFFERS, &samples);
		mMultisample = (samples != 0);
		
		mSurface = eglCreateWindowSurface(mDisplay, mConfig, mWindowHandler, NULL);
		if (mSurface == EGL_NO_SURFACE)
		{
			eglGetError(); // Clear error
			mSurface = eglCreateWindowSurface(mDisplay, mConfig, NULL, NULL);
		}
		if (eglGetError() != EGL_SUCCESS)
		{
			destroyEGLContext();
			return false;
		}
		EGLint contextAttibutes[] =
		{
			EGL_CONTEXT_CLIENT_VERSION, mClientVersion,
			EGL_NONE
		};
		mContext = eglCreateContext(mDisplay, mConfig, NULL, contextAttibutes);
		
		if (eglGetError() != EGL_SUCCESS)
		{
			destroyEGLContext();
			return false;
		}
		eglMakeCurrent(mDisplay, mSurface, mSurface, mContext);
		if (eglGetError() != EGL_SUCCESS)
		{
			destroyEGLContext();
			return false;
		}
		
		bool bTest =extensionEnabled("OES_vertex_array_object");

		return true;
	}

	bool WindowEGL::destroyEGLContext()
	{

		if (mCreated)
		{
			eglDestroySurface(mDisplay, mSurface);
			eglDestroyContext(mDisplay, mContext);
			return true;
		}
		
		return false;
	}



	LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{

		core::EventChannel evt;
		switch (uMsg)
		{

		case WM_KEYDOWN:



			
			switch (wParam) 
			{
				if (GetAsyncKeyState(VK_UP))
				{
					core::EventChannel evt;
					evt.broadcast(input::Keyboard::KeyPressed(VK_UP));
				}

				if (GetAsyncKeyState(VK_DOWN))
				{
					core::EventChannel evt;
					evt.broadcast(input::Keyboard::KeyPressed(VK_DOWN));
				}

				if (GetAsyncKeyState(VK_RIGHT))
				{
					core::EventChannel evt;
					evt.broadcast(input::Keyboard::KeyPressed(VK_RIGHT));
				}
				if (GetAsyncKeyState(VK_LEFT))
				{
					core::EventChannel evt;
					evt.broadcast(input::Keyboard::KeyPressed(VK_LEFT));
				}


				if (GetAsyncKeyState(VK_F2))
				{
					core::EventChannel evt;
					evt.broadcast(input::Keyboard::KeyPressed(VK_F2));
				}

				if (GetAsyncKeyState(VK_F1))
				{
					core::EventChannel evt;
					evt.broadcast(input::Keyboard::KeyPressed(VK_F1));
				}


			case VK_UP:			
				evt.broadcast(input::Keyboard::KeyPressed(VK_UP));

				break;

			default:
				break;
			}

		case WM_KEYUP:


			
			switch (wParam)
			{

				if (GetAsyncKeyState(VK_UP))
				{
					core::EventChannel evt;
					evt.broadcast(input::Keyboard::KeyReleased(VK_UP));
				}

				if (GetAsyncKeyState(VK_DOWN))
				{
					core::EventChannel evt;
					evt.broadcast(input::Keyboard::KeyReleased(VK_DOWN));
				}

				if (GetAsyncKeyState(VK_RIGHT))
				{
					core::EventChannel evt;
					evt.broadcast(input::Keyboard::KeyReleased(VK_RIGHT));
				}
				if (GetAsyncKeyState(VK_LEFT))
				{
					core::EventChannel evt;
					evt.broadcast(input::Keyboard::KeyReleased(VK_LEFT));
				}

				if (GetAsyncKeyState(VK_F2))
				{
					core::EventChannel evt;
					evt.broadcast(input::Keyboard::KeyReleased(VK_F2));
				}

				if (GetAsyncKeyState(VK_F1))
				{
					core::EventChannel evt;
					evt.broadcast(input::Keyboard::KeyReleased(VK_F1));
				}
			case VK_UP:
				evt.broadcast(input::Keyboard::KeyReleased(VK_UP));


				break;

			default:
				break;
			}
		case WM_ACTIVATE:
		{
							return 0;
		}
		case WM_SYSCOMMAND:
		{
							  switch (wParam)
							  {
							  case SC_SCREENSAVE:
							  case SC_MONITORPOWER:
								  return 0;
							  }
							  break;
		}
		case WM_CLOSE:
		{
						 DestroyWindow(hWnd);
						 //Log::Success("Window - Released by WndProc");
						 return 0;
		}
		case WM_DESTROY:
		{
						   PostQuitMessage(0);

						   return 0;
		}
		}
		// Pass All Unhandled Messages To DefWindowProc
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}



	static void PrintConfigAttributes(EGLDisplay display, EGLConfig config)
	{
		EGLBoolean result = GL_FALSE;
		EGLint value = 0;

		printf("--------------------------------------------------------------------------\n", value);

		eglGetConfigAttrib(display, config, EGL_CONFIG_ID, &value);
		printf("EGL_CONFIG_ID %d\n", value);

		eglGetConfigAttrib(display, config, EGL_BUFFER_SIZE, &value);
		printf("EGL_BUFFER_SIZE %d\n", value);
		eglGetConfigAttrib(display, config, EGL_RED_SIZE, &value);
		printf("EGL_RED_SIZE %d\n", value);
		eglGetConfigAttrib(display, config, EGL_GREEN_SIZE, &value);
		printf("EGL_GREEN_SIZE %d\n", value);
		eglGetConfigAttrib(display, config, EGL_BLUE_SIZE, &value);
		printf("EGL_BLUE_SIZE %d\n", value);
		eglGetConfigAttrib(display, config, EGL_ALPHA_SIZE, &value);
		printf("EGL_ALPHA_SIZE %d\n", value);
		eglGetConfigAttrib(display, config, EGL_DEPTH_SIZE, &value);
		printf("EGL_DEPTH_SIZE %d\n", value);
		eglGetConfigAttrib(display, config, EGL_STENCIL_SIZE, &value);
		printf("EGL_STENCIL_SIZE %d\n", value);
		eglGetConfigAttrib(display, config, EGL_SAMPLE_BUFFERS, &value);
		printf("EGL_SAMPLE_BUFFERS %d\n", value);
		eglGetConfigAttrib(display, config, EGL_SAMPLES, &value);
		printf("EGL_SAMPLES %d\n", value);

		eglGetConfigAttrib(display, config, EGL_CONFIG_CAVEAT, &value);
		switch (value)
		{
		case EGL_NONE: printf("EGL_CONFIG_CAVEAT EGL_NONE\n"); break;
		case EGL_SLOW_CONFIG: printf("EGL_CONFIG_CAVEAT EGL_SLOW_CONFIG\n"); break;
		}

		eglGetConfigAttrib(display, config, EGL_MAX_PBUFFER_WIDTH, &value);
		printf("EGL_MAX_PBUFFER_WIDTH %d\n", value);
		eglGetConfigAttrib(display, config, EGL_MAX_PBUFFER_HEIGHT, &value);
		printf("EGL_MAX_PBUFFER_HEIGHT %d\n", value);
		eglGetConfigAttrib(display, config, EGL_MAX_PBUFFER_PIXELS, &value);
		printf("EGL_MAX_PBUFFER_PIXELS %d\n", value);
		eglGetConfigAttrib(display, config, EGL_NATIVE_RENDERABLE, &value);
		printf("EGL_NATIVE_RENDERABLE %s \n", (value ? "true" : "false"));
		eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &value);
		printf("EGL_NATIVE_VISUAL_ID %d\n", value);
		eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_TYPE, &value);
		printf("EGL_NATIVE_VISUAL_TYPE %d\n", value);
		eglGetConfigAttrib(display, config, EGL_SURFACE_TYPE, &value);
		printf("EGL_SURFACE_TYPE %d\n", value);
		eglGetConfigAttrib(display, config, EGL_TRANSPARENT_TYPE, &value);
		printf("EGL_TRANSPARENT_TYPE %d\n", value);
	}



}


