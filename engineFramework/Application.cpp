#include "stdafx.h"
#include "Application.h"


namespace app 
{

	// Internals
	int Application::width = 0;
	int Application::height = 0;
	bool Application::exitRequest = false;
	bool Application::appIsActive = false;
	bool Application::appIsSuspended = false;


	// Static Event Instantiations
	// ======================================
	Application::ApplicationEventHandler Application::Resized;
	Application::ApplicationEventHandler Application::Exitting ;
	Application::ApplicationEventHandler Application::Activating ;
	Application::ApplicationEventHandler Application::Deactivating;
	Application::ApplicationEventHandler Application::Suspending ;
	Application::ApplicationEventHandler Application::Resuming;



	Application::Application(const std::string& name, unsigned int taskFlags) :core::System(name, taskFlags)
	{
	}



	Application::~Application() 
	{
	}
	

	// ##########################################################################################
	//
	// Platform Methods
	//
	// ##########################################################################################

	// ***********************************************************************
	bool Application::Platform_InitFkh()
	{


		// Setup the application states
		exitRequest = false;
		appIsActive = true;
		appIsSuspended = false;


		return true;
	}


	// ***********************************************************************
	void Application::Platform_ShutdownFkh()
	{
		std::cout << "Shutting down" <<std::endl; 
	}


	// ***********************************************************************
	bool Application::Platform_InitGame()
	{
		// Init 2nd Tier Systems

		return true;
	}


	// ***********************************************************************
	void Application::Platform_ShutdownGame()
	{
		// Fire the Exitting event
		Exitting();

	}


	// ***********************************************************************
	void Application::Platform_MainLoop()
	{

	}




	// ##########################################################################################
	//
	// Platform Events
	//
	// ##########################################################################################


	// ***********************************************************************
	void Application::Platform_OnSuspend()
	{
		appIsSuspended = true;

		// Raise the event
		Suspending();
	}

	// ***********************************************************************
	void Application::Platform_OnResume()
	{
		appIsSuspended = false;

		// Raise the event
		Resuming();
	}

	// ***********************************************************************
	void Application::Platform_OnActive()
	{
		appIsActive = true;

		// Raise the event
		Activating();
	}

	// ***********************************************************************
	void Application::Platform_OnDeactive()
	{
		appIsActive = false;

		// Raise the event
		Deactivating();
	}

	// ***********************************************************************
	void Application::Platform_OnResize(int newWidth, int newHeight)
	{
		// Save the new dimensions
		Application::width = newWidth;
		Application::height = newHeight;

		// Fire the re-sized event
		Resized();
	}



}

