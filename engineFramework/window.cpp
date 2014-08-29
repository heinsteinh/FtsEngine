#include "window.h"

Window::Window() {
	//default to 800x600x32, 24bits depth, 8 bits stencil, (windowed)
	mWidth = 800;
	mHeight = 600;
		
	mAlphaBits = 8;
	mRedBits = 8;
	mGreenBits = 8;
	mBlueBits = 8;

	mDepthBits = 24;
	mStencilBits = 8;

	mFullScreen = false;

	mTitle = "Overdrive Assault";
}

Window::~Window() {
}

bool Window::create() {
	int result = glfwOpenWindow(
		mWidth, 
		mHeight,
		mRedBits,
		mGreenBits,
		mBlueBits,
		mAlphaBits,
		mDepthBits,
		mStencilBits,
		mFullScreen ? GLFW_FULLSCREEN : GLFW_WINDOW
	);

	if (result == GL_FALSE)
		return false;

	glfwSwapInterval(0); //disable vertical sync
	return true;
}

void Window::destroy() {
	glfwCloseWindow();
}