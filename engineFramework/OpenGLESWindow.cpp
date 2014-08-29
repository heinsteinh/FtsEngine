#include "stdafx.h"
#include "OpenGLESWindow.h"

#include "SceneManager.h"

namespace core
{


	OpenGLESWindow::OpenGLESWindow(const std::string& title) : Window(title, Window::GLFW) 
	{
		//Default
		mWidth = 800;
		mHeight = 600;
		mFullScreen = false;
	}

	OpenGLESWindow::~OpenGLESWindow() {}

	bool OpenGLESWindow::isClosed() 
	{
		return false;//glfwWindowShouldClose(mWindow) == 1;
	}

	bool OpenGLESWindow::create() 
	{
		
		//mWindow = glfwCreateWindow(mWidth, mHeight, mTitle.c_str(), mFullScreen ? glfwGetPrimaryMonitor() : NULL, NULL);
		//if (!mWindow) {
		// return false;
		//}
		//glfwMakeContextCurrent(mWindow);
		return true;
	}

	void OpenGLESWindow::destroy() 
	{
		//glfwDestroyWindow(mWindow);

	}

	void OpenGLESWindow::run() 
	{
		// update
		update(Window::mTimeElapsedSinceLastFrame);
		
		// render
		//glfwMakeContextCurrent(mWindow);
		
		render(Window::mTimeElapsedSinceLastFrame);

		//glfwSwapBuffers(mWindow);
		//glfwPollEvents();
	}


	void OpenGLESWindow::render(double fTimeElapse)
	{
		mActiveScene->Process();
	}

	

}