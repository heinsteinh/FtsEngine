#include "stdafx.h"
#include "GraphicTask.h"




const int ResolutionX = 540;
const int ResolutionY = 960;
HWND mNativeWindow;


#define WINDOW_CLASS _T("TriDrawClass")

GLuint viewportWidth = -1;
GLuint viewportHeight = -1;



int ANAS::Graphic::Width = -1;
int ANAS::Graphic::Height = -1;


ANAS::Graphic::Graphic(WNDPROC_FUNC* _f)
{
	mCallbackFunction = _f;

	start();
}


ANAS::Graphic::~Graphic()
{
	stop();
}


void ANAS::Graphic::Init( HINSTANCE _hInstance)
{
	
	hInstance = _hInstance;

	add(core::AnyTasking::Ptr( new core::AnyTasking(std::bind(&ANAS::Graphic::InitTask, this))));

	//Swap(0, 0, 1, 1);

	Notification();
}

void ANAS::Graphic::Term()
{	
	add(core::AnyTasking::Ptr(new core::AnyTasking(std::bind(&ANAS::Graphic::TermTask, this))));

}


void ANAS::Graphic::Swap(float r, float g, float b, float a){

	add(core::AnyTasking::Ptr(new core::AnyTasking(std::function<void()>(std::bind(&ANAS::Graphic::SwapTask, this, r, g, b, a)))));

}



LRESULT CALLBACK ANAS::Graphic::WndProc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
	{
						   ANAS::Graphic* pMyWindow = (ANAS::Graphic*)GetProp(hwnd, TEXT("Graphic"));
						   if (NULL != pMyWindow)
						   {
							   // Increment num_squares.
							   //++pMyWindow->num_squares;
						   }

						   break;
	}

	case WM_DESTROY:
	{
					   RemoveProp(hwnd, TEXT("MyWindow"));
					   break;
	}
	}

	return DefWindowProc(hwnd, msg, w_param, l_param);
}

//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	switch (message)
//	{
//	case WM_CLOSE:
//		exit(0);
//		break;
//
//	case WM_SYSKEYDOWN:
//	case WM_KEYDOWN:
//
//		break;
//	}
//
//	return DefWindowProc(hWnd, message, wParam, lParam);
//}




void ANAS::Graphic::InitTask()
{
	const EGLint attribute[] = 
	{
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,

		EGL_BLUE_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_RED_SIZE, 8,

		EGL_NONE

	};

	const EGLint attrib_list[] = {
		EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE
	};
	
	EGLint numConfigs;
	EGLint Format;


	// Display	
	eglDisplay = eglGetDisplay((EGLNativeDisplayType)EGL_DEFAULT_DISPLAY);
	EGLint majorVersion, minorVersion;
	if(!eglInitialize(eglDisplay, &majorVersion, &minorVersion))
	{
		throw std::exception("eglInitialize failed");
	}

	// Config
	if (!eglChooseConfig(eglDisplay, attribute, &eglConfig, 1, &numConfigs) || (numConfigs != 1))
	{
		throw std::exception("eglChooseConfig failed");
	}
		
	eglGetConfigAttrib(eglDisplay, eglConfig, EGL_NATIVE_VISUAL_ID, &Format);
	
	
	int x, y;
	RECT winRect;

	SetRect(&winRect, 0, 0, ResolutionX, ResolutionY);
	AdjustWindowRectEx(&winRect, WS_CAPTION | WS_SYSMENU, false, 0);

	x = 0 - winRect.left;
	winRect.left += x;
	winRect.right += x;

	y = 0 - winRect.top;
	winRect.top += y;
	winRect.bottom += y;

	if (true)
	{
		x = CW_USEDEFAULT;
		y = CW_USEDEFAULT;
	}
	else
	{
		x = winRect.left;
		y = winRect.top;
	}

	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = 0;
	wc.hCursor = 0;
	wc.lpszMenuName = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszClassName = WINDOW_CLASS;
	RegisterClass(&wc);

	mNativeWindow  = CreateWindow(
		WINDOW_CLASS, _T("Weezy Draw"),
		WS_VISIBLE | WS_CAPTION | WS_SYSMENU,
		x, y, winRect.right - winRect.left, winRect.bottom - winRect.top,
		NULL, NULL, hInstance, NULL
		);

	SetProp(mNativeWindow, TEXT("Graphic"), (HANDLE)this);

	//SetWindowLong(mNativeWindow, GWL_STYLE, 0);
	ShowWindow(mNativeWindow, SW_SHOW);

	SetForegroundWindow(mNativeWindow);
	SetFocus(mNativeWindow);


	eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, mNativeWindow, NULL);
	if (!eglSurface)
	{
		throw std::exception("Unable to eglCreateWindowSurface");
	}

	eglContext = eglCreateContext(eglDisplay, eglConfig, NULL, attrib_list);
	if (!eglContext)
	{
		throw std::exception("Unable to eglCreateContext");
	}

	if (eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext) == EGL_FALSE)
	{
		throw std::exception("Unable to eglMakeCurrent");
	}

	
	const int DownScaleFactor = 3;
	eglQuerySurface(eglDisplay, eglSurface, EGL_WIDTH, &Width);
	eglQuerySurface(eglDisplay, eglSurface, EGL_HEIGHT, &Height);
	viewportWidth = Width / DownScaleFactor;
	viewportHeight = Height / DownScaleFactor;
	


	// Initialize GL state.
	eglSwapInterval(eglDisplay, 0);

	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);


	glViewport(0, 0, viewportWidth, viewportHeight);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	


	// Load shaders:
	/*printf("Version", GL_VERSION);
	printf("Vendor", GL_VENDOR);
	printf("Renderer", GL_RENDERER);
	printf("Extensions", GL_EXTENSIONS);*/

	//printf("setupGraphics(%d, %d) \n", viewportWidth, viewportHeight);
	printf("setupGraphics view=(%d, %d) win=(%d, %d) \n", viewportWidth, viewportHeight, Width, Height);
}




void ANAS::Graphic::TermTask()
{
		
	eglMakeCurrent(eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

	if (eglContext != EGL_NO_CONTEXT)
	{
		eglDestroyContext(eglDisplay, eglContext);
	}

	if (eglSurface != EGL_NO_SURFACE)
	{
		eglDestroySurface(eglDisplay, eglSurface);
	}

	eglTerminate(eglDisplay);

	eglDisplay = EGL_NO_DISPLAY;
	eglSurface = EGL_NO_SURFACE;
	eglContext = EGL_NO_CONTEXT;
}





void ANAS::Graphic::SwapTask(float r, float g, float b, float a)
{
	eglSwapBuffers(eglDisplay, eglSurface);

	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}