#include "stdafx.h"
#include "Graphic.h"
#include "Logger.h"




int ANAS::Graphic::Width = -1;
int ANAS::Graphic::Height = -1;


ANAS::Graphic::Graphic(){}


ANAS::Graphic::~Graphic()
{

}


void ANAS::Graphic::Init(ANativeWindow *_window)
{

	fts::Log::printf("Graphic: Init \n");

	submit(new AnyTasking(std::bind(&ANAS::Graphic::InitTask, this)));


	Swap(0, 0, 1, 1);

	Notification();
}

void ANAS::Graphic::Term(){

	
	fts::Log::printf("Graphic: Terminate \n");

	submit(new AnyTasking(std::bind(&ANAS::Graphic::TermTask, this)));

}


void ANAS::Graphic::Swap(float r, float g, float b, float a){

	submit(new AnyTasking(std::function<void()>(std::bind(&ANAS::Graphic::SwapTask, this, r, g, b, a))));

}


void ANAS::Graphic::InitTask(){

	
	fts::Log::printf("EGL Task: Init \n");

	/*
	const EGLint attribute[] = {
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL_NONE
	};
	EGLConfig eglConfig;
	EGLint numConfigs;
	EGLint Format;

	// Display
	eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	eglInitialize(eglDisplay, 0, 0);

	// Config
	eglChooseConfig(eglDisplay, attribute, &eglConfig, 1, &numConfigs);

	eglGetConfigAttrib(eglDisplay, eglConfig, EGL_NATIVE_VISUAL_ID, &Format);

	// Buffer
	ANativeWindow_setBuffersGeometry(pWindow, 0, 0, Format);

	//
	eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, pWindow, NULL);


	eglBindAPI(EGL_OPENGL_ES_API);


	EGLint ContextAttrib[] = {
		EGL_CONTEXT_CLIENT_VERSION, 2,
		EGL_NONE
	};
	eglContext = eglCreateContext(eglDisplay, eglConfig, NULL, ContextAttrib);



	if (eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext) == EGL_FALSE) {

		ANAS::Log::i("EGL Task", "Init Failed");
	}


	eglQuerySurface(eglDisplay, eglSurface, EGL_WIDTH, &Width);
	eglQuerySurface(eglDisplay, eglSurface, EGL_HEIGHT, &Height);

	ANAS::Log::i("GRAPHIC", (boost::format("W:%1%, H:%2%") % Width%Height).str().c_str());

	glViewport(0, 0, Width, Height);


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/

}


void ANAS::Graphic::TermTask()
{
	done = true;
		
	fts::Log::printf("EGL Task: Term \n");
	
	/*

	eglMakeCurrent(eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

	if (eglContext != EGL_NO_CONTEXT){
		eglDestroyContext(eglDisplay, eglContext);
	}
	if (eglSurface != EGL_NO_SURFACE){
		eglDestroySurface(eglDisplay, eglSurface);
	}

	eglTerminate(eglDisplay);

	eglDisplay = EGL_NO_DISPLAY;
	eglSurface = EGL_NO_SURFACE;
	eglContext = EGL_NO_CONTEXT;*/
}



void ANAS::Graphic::SwapTask(float r, float g, float b, float a)
{

	
	fts::Log::printf("SwapTask %.1f, %.1f, %.1f, %.1f\n", r, g, b, a);
	
	/*
	eglSwapBuffers(eglDisplay, eglSurface);

	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	*/
}