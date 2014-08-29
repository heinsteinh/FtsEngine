#pragma once



#include "WindowVideo.h"

struct GLFWwindow;
namespace core {

	class  OpenGLESWindow : public Window
	{
	private:
		GLFWwindow *mWindow;
		bool isClosed();

		void run();

	public:
		OpenGLESWindow(const std::string& title);
		virtual ~OpenGLESWindow();

		//missing input...
		virtual void render(double fTimeElapsed);
		virtual void update(double fTimeElapsed) {}
		virtual bool create();
		virtual void destroy();


		typedef std::shared_ptr<core::OpenGLESWindow> OpenGLESWindowPtr;
	};

}
