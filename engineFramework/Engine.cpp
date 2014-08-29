#include "stdafx.h"
#include "Engine.h"

#include "ConfigFile.h"

#include "TestScene.h"

namespace core 
{


	/////////////////////// TIME UPDATING TASK ///////////////////////
	Engine::TimeUpdater::TimeUpdater(Engine *e, uint8_t taskFlags) : mEngine(e), Task(taskFlags) {}

	void Engine::TimeUpdater::run() 
	{
		static std::chrono::high_resolution_clock::time_point mLastFrameTime = std::chrono::high_resolution_clock::now();

		auto diff = std::chrono::high_resolution_clock::now() - mLastFrameTime;
		auto timeElapsed = std::chrono::duration_cast<std::chrono::microseconds>(diff);

		if ((double)(timeElapsed.count() / 1000000.0) < (double)(1.0 / 60.0))
			return;

		mEngine->setElapsedTime((double)(timeElapsed.count() / 1000000.0));
		mEngine->setGlobalTime(mEngine->globalTime() + mEngine->elapsedTime());

		mLastFrameTime = std::chrono::high_resolution_clock::now();

		//std::cout << " Update time: " << mEngine->elapsedTime() << std::endl;
	}
	/////////////////////// !TIME UPDATING TASK ///////////////////////


		


	Engine::Engine()
		: mElapsedTime(0.0)
		, mGlobalTime(0.0)
		, mWindowLibrary(USE_GLFW3)
		, mConfig(new core::Config())
		, mVideo(new video::VideoSystem())
		, mClock(new core::Clock())
		, mInput(new input::Input())
		, mEntityManager(new entityx::EntityManager())
		, mSystemtEntity(new entityx::SystemManager())
		, mRenderSystem(new rendering::RenderSystem())
		, mStateManager(new core::cStateManager())
		
	{
		test::TestScene::TestScenePtr tScene(new test::TestScene);

		mSceneContainer = std::shared_ptr<GameScene::SceneContainer>(new GameScene::SceneContainer());		
		mSceneContainer->addScene(tScene);

		mSceneManager = std::shared_ptr<GameScene::SceneManager>(new GameScene::SceneManager(mSceneContainer.get()));
			

		add(mVideo);
		add(mClock);
		add(mInput);
		//add(mSceneManager);
		add(mSystemtEntity);

		add(mStateManager);
		add(mRenderSystem);
	}

	Engine::~Engine()
	{
	}

	void Engine::run() 
	{
		//https://github.com/AlexanderKnueppel/Harmony4D/blob/5e361525e3b5536f1800dd3066e80323cd16a491/Harmony4D/src/core/Engine.cpp

	
		/*int argc = NULL;
		char* argv[2];*/


		/*
		//std::cout << "loading assault.cfg... ";
		//mConfig->load("assault.cfg");

		std::cout << "Loading default.cfg... ";
		mConfig->load("default.cfg");
		std::cout << "done." << std::endl;

		mConfig->parseCommandLine(argc, argv);

		///////////// TEST /////////////////////
		int width			= (int)mConfig->get("window", "width", 1024);
		int height			= (int)mConfig->get("window", "height", 768);
		bool fullscreen		= (bool)mConfig->get("window", "fullscreen", true);
		std::string title	= (std::string)mConfig->get("window", "title", "Weezy");


		std::cout << "Title: " << title << "\n"
			<< "Width: " << width << "\n"
			<< "Height: " << height << "\n"
			<< "fullscreen?: " << (fullscreen ? "true" : "false") << std::endl;
		///////////// !TEST /////////////////////
		*/



		std::cout << "done." << std::endl;

		initializeSystems();

		// add timing
		mTaskManager.add(std::shared_ptr<Task>(new TimeUpdater(this)));

		
		mTaskManager.start();

		
		shutdownSystems();
	}

	void Engine::stop() 
	{
		events().broadcast(TaskManager::StopEvent());
	}



	void Engine::add(Engine::SystemPtr system)
	{
		if (mSystemMap.find(system->getName()) == mSystemMap.end()) 
		{
			system->mEngine = this;

			if (system->mSystemUpdater.get())
				mTaskManager.add(system->mSystemUpdater);

			mSystemMap.insert(std::make_pair(system->getName(), system));
		}
		else
			gLog << "Engine::add - System already added: " << system->getName();
	}


	bool Engine::remove(Engine::SystemPtr system)
	{
		SystemMap::iterator it = mSystemMap.find(system->getName());
		if (it == mSystemMap.end()) 
		{
			gLog << "Engine::remove - Cannot find system: " << system->getName();
			return false;
		}

		mSystemMap.erase(it);
		return true;
	}


	Engine::SystemPtr Engine::get(const std::string& name) const 
	{
		SystemMap::const_iterator it = mSystemMap.find(name);

		if (it == mSystemMap.end()) {
			gLog << "Engine::get - Cannot find system: " << name;
			return SystemPtr();
		}

		return it->second;
	}

	TaskManager& Engine::getTaskManager() 
	{
		return mTaskManager;
	}

	void Engine::initializeSystems()
	{
		for (SystemMap::iterator it = mSystemMap.begin(); it != mSystemMap.end(); ++it) 
		{
			gLog.info() << "Initializing " << it->second->getName();
			it->second->init();
		}

		if (mApplication.get())
		{
			gLog.info() << "Initializing app: " << mApplication->getName();
			mApplication->init();

			add(mApplication);
		}
	}

	void Engine::shutdownSystems()
	{
		if (mApplication.get())
		{
			gLog.info() << "Shutting down app: " << mApplication->getName();
			mApplication->shutdown();

			mApplication.reset();
		}

		for (SystemMap::iterator it = mSystemMap.begin(); it != mSystemMap.end(); ++it) {
			gLog.info() << "Shutting down " << it->second->getName();
			it->second->shutdown();
		}
	}

	
	const std::shared_ptr<entityx::EntityManager>& Engine::getEntityManager()
	{
		return mEntityManager;
	}

	const std::shared_ptr<entityx::SystemManager>& Engine::getSystemtEntity()
	{
		return mSystemtEntity;
	}

	const std::shared_ptr<Config>& Engine::getConfig()
	{
		return mConfig;
	}

	const std::shared_ptr<app::Application>& Engine::getApplication()
	{
		return mApplication;
	}
	
	const std::shared_ptr<video::VideoSystem>& Engine::getVideo() 
	{
		return mVideo;
	}

	
	const std::shared_ptr<input::Input>& Engine::getInput() 
	{
		return mInput;
	}
	

	const std::shared_ptr<core::Clock>& Engine::getClock() 
	{
		return mClock;
	}
	
	const std::shared_ptr<GameScene::SceneManager>& Engine::getSceneManager()
	{
		return mSceneManager;
	}
	
	const std::shared_ptr<GameScene::SceneContainer>& Engine::getSceneContainer()
	{
		return mSceneContainer;
	}


	const std::shared_ptr<core::cStateManager>& Engine::getStateManager()
	{
		return mStateManager;
	}


	EventChannel& Engine::events()
	{
		return mChannel;
	}

	
	void Engine::setApplication(const std::shared_ptr<app::Application>& application) 
	{
		if (mApplication.get() == NULL) {
			mApplication = application;

			mApplication->mEngine = this;
		}
		else
			gLog << "Engine:setApplication - application already set, ignoring " << application->getName();
	}
}
