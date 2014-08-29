#pragma once

#include "ActivityCallbacks.h"

namespace AppSpec
{


	class DOpenGLView;
	/// Manages a context for a specific view without touching the associated window.
	class ViewContext //: public Context
	{
	protected:
		DOpenGLView * _graphics_view;

		ViewContext();

	public:
		ViewContext(DOpenGLView * graphics_view);
		virtual ~ViewContext();

		virtual void start();
		virtual void stop();

		//virtual Vec2 size();
	};


	class UIWindow;
	/// This context manages a window which can be used to display content.
	class WindowContext : public ViewContext //, implements IInputHandler 
	{
	protected:
		UIWindow * _window;

		// Setup the graphics view
		void setup_graphics_view(ANAS::ActivityConfigration* config /*, CGRect frame*/);

	public:
		WindowContext(ANAS::ActivityConfigration* config);
		virtual ~WindowContext();

		virtual void start();
		virtual void stop();

	};
}
