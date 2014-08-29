#pragma once

#include "System.h"

namespace core {
	class Engine;
}

namespace app {
	class Application : public core::System
	{
	public:
		friend class core::Engine;
		typedef std::shared_ptr<app::Application> Ptr;
		

		Application(const std::string& name, unsigned int taskFlags = core::Task::SINGLETHREADED_REPEATING);
		virtual ~Application();



		// =====================================================
		// Platform -> Application : interfaces
		//              These methods are intended to be called from the platform-dependent Main() implementation
		// =====================================================

		// Main execution methods
		static bool Platform_InitFkh();
		static void Platform_ShutdownFkh();

		static bool Platform_InitGame();
		static void Platform_ShutdownGame();
		static void Platform_MainLoop();


		// Execution events
		static void Platform_OnSuspend();
		static void Platform_OnResume();
		static void Platform_OnActive();
		static void Platform_OnDeactive();
		static void Platform_OnResize(int newWidth, int newHeight);


		// Application Delegates
		// ------------------------------
		typedef std::function<void(void)>   ApplicationEventHandler;

		// Application Events
		// ------------------------------
		// Called when the application window or display is resized.
		static ApplicationEventHandler Resized;

		// Called just before the application is closed/terminated
		static ApplicationEventHandler Exitting;

		// Called when the application is made the primary view (iOS: dismiss text msg, WIN: alt-tab back, etc)
		static ApplicationEventHandler Activating;

		// Called when the application is being made a non-primary view (iOS: txt msg pops up / incoming call, WIN: alt-tab away, etc)
		static ApplicationEventHandler Deactivating;

		// Called when the application is being suspended (iOS: hit home button or change apps, WIN: does nothing)
		static ApplicationEventHandler Suspending;

		// Called when the application is resuming from the suspended state
		static ApplicationEventHandler Resuming;


	protected:
		core::Engine* mEngine;

	private:

		static int width;
		static int height;
		static bool exitRequest;
		static bool appIsActive;
		static bool appIsSuspended;

	};
}

