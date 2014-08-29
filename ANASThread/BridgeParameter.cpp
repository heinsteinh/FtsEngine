#include "stdafx.h"

#include "BridgeParameter.h"
#include "ActivityCallbacks.h"


#include "InputActivity.h"
#include "Graphic.h"
#include "Logger.h"
#include "TestScene.h"



void Main(runApp::BridgeParameter* arg)
{
	std::unique_ptr< runApp::BridgeParameter > param(arg);

	fts::Log::init();
	fts::Log::addConsumer(fts::OnAppLog);
	

	ANAS::InputActivity  Input;
	ANAS::Graphic   Graphic;
	Graphic.Init(NULL);
	Input.Init(NULL);


	// Set Configuration for Activity.
	ANAS::ActivityConfigration Configuration;
	{
		// Basic Param
		//Configuration.pActivity = param->activity;
		Configuration.pSavedState = param->savedState;
		Configuration.SavedStateSize = param->savedStateSize;

		// Custom Param
		Configuration.pUserCallbacks = NULL;	// No Implement

		// Set to configuration class.
		Configuration.pInput = &Input;
		Configuration.pGraphic = &Graphic;
	}



	// Create Activity
	std::unique_ptr< ANAS::Activity > pActivity(new ANAS::Activity(Configuration));

	// Push
	param->Notification();

	// Wait Init.
	Graphic.Wait();
	Input.Wait();
		
	
	// Scene
	ANAS::SceneContainer *pContainer = new ANAS::SceneContainer;
	{
		// Interfaces
		pContainer->pGraphic = &Graphic;
		pContainer->pInput = &Input;

		// Activity
		//pContainer->pActivity = param->activity;

		// Startup Scene
		pContainer->pStartScene = new test::testScene;
		//pContainer->pStartScene = new Game::GameScene;
	}

		
	std::unique_ptr<ANAS::SceneManager> SceneManager(new ANAS::SceneManager(pContainer));
		
	pContainer->NotifySignal.Wait();	


	fts::Log::printf("System: System Terminate");
	fts::Log::removeConsumer(fts::OnAppLog);
	fts::Log::shutdown();

	

	/*
	// Items
	//ANAS::Input Input;
	//ANAS::Graphic Graphic;

	
	// Set Configuration for Activity.
	ANAS::ActivityConfigration Configuration;
	{
	// Basic Param
	Configuration.pActivity = param->activity;
	Configuration.pSavedState = param->savedState;
	Configuration.SavedStateSize = param->savedStateSize;

	// Custom Param
	Configuration.pUserCallbacks = NULL;	// No Implement

	// Set to configuration class.
	Configuration.pInput = &Input;
	Configuration.pGraphic = &Graphic;
	}

	// Create Activity
	boost::scoped_ptr< ANAS::Activity > pActivity(new ANAS::Activity(Configuration));

	// Push
	param->Notification();

	// Wait Init.
	Graphic.Wait();
	Input.Wait();


	// Scene
	ANAS::SceneContainer *pContainer = new ANAS::SceneContainer;
	{
	// Interfaces
	pContainer->pGraphic = &Graphic;
	pContainer->pInput = &Input;

	// Activity
	pContainer->pActivity = param->activity;

	// Startup Scene
	pContainer->pStartScene = new ANAS::SplashScreenScene;
	//pContainer->pStartScene = new Game::GameScene;
	}

	boost::scoped_ptr<ANAS::SceneManager> SceneManager(new ANAS::SceneManager(pContainer));


	// I—¹‘Ò‚¿
	pContainer->NotifySignal.Wait();

	ANAS::Log::i("System", "System Terminate");


	void Main(BridgeParameter* arg){
	boost::scoped_ptr< BridgeParameter > param( arg );

	// Items
	ANAS::Input Input;
	ANAS::Graphic Graphic;

	// Set Configuration for Activity.
	ANAS::ActivityConfigration Configuration;
	{
	// Basic Param
	Configuration.pActivity = param->activity;
	Configuration.pSavedState = param->savedState;
	Configuration.SavedStateSize = param->savedStateSize;

	// Custom Param
	Configuration.pUserCallbacks = NULL;	// No Implement

	// Set to configuration class.
	Configuration.pInput = &Input;
	Configuration.pGraphic = &Graphic;
	}

	// Create Activity
	boost::scoped_ptr< ANAS::Activity > pActivity ( new ANAS::Activity( Configuration ) );

	// Push
	param->Notification();

	// Wait Init.
	Graphic.Wait();
	Input.Wait();


	// Scene
	ANAS::SceneContainer *pContainer = new ANAS::SceneContainer;
	{
	// Interfaces
	pContainer->pGraphic = &Graphic;
	pContainer->pInput = &Input;

	// Activity
	pContainer->pActivity = param->activity;

	// Startup Scene
	pContainer->pStartScene = new ANAS::SplashScreenScene;
	//pContainer->pStartScene = new Game::GameScene;
	}

	boost::scoped_ptr<ANAS::SceneManager> SceneManager ( new ANAS::SceneManager( pContainer ) );


	// I—¹‘Ò‚¿
	pContainer->NotifySignal.Wait();

	ANAS::Log::i( "System", "System Terminate" );
	
	}
	*/
}

// Entry Point
void runApp::android_main(ANativeActivity* activity, void* savedState, size_t savedStateSize)
{

	printf("System Build-Number : \n");

	// Create bridge paramaters
	BridgeParameter *param = new BridgeParameter(activity, savedState, savedStateSize);


	// Create main thread
	std::thread MainThread(&Main, param);
		
	
	// Wait( blocking )
	param->Wait();


	MainThread.join();

	return ;
}