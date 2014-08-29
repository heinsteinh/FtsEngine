#pragma once



#include <string>
#include <cstdint>

#include "taskmanager.h"

#include "System.h"
#include "ConfigSystem.h"
#include "VideoSystem.h"
#include "Input.h"
#include "Entity.h"
#include "SystemEntity.h"
#include "StateMachine.h"

#include "SceneManager.h"
#include "RenderSystem.h"



#include "Clock.h"
#include "Application.h"

namespace core 
{
	

	
	class  Engine 
	{
	public:
		typedef std::shared_ptr<System> SystemPtr;
		typedef std::map<std::string, SystemPtr> SystemMap;


		enum eWindowLibraryType : std::int8_t 
		{
			USE_GLFW3 = 0,
			USE_QT = 1
		};
		
		void windowCreationHint(eWindowLibraryType windowLibrary)
		{
			if (!mbRunning)
				mWindowLibrary = windowLibrary;
		}

		const eWindowLibraryType& windowType() { return mWindowLibrary; }


		struct TimeUpdater : public Task 
		{
			TimeUpdater(Engine *e, uint8_t taskFlags = Task::SINGLETHREADED_REPEATING);
			virtual void run();

			Engine* mEngine;
		};

		friend TimeUpdater;

		Engine();
		~Engine();

		void run();
		void stop();

		void setApplication(const std::shared_ptr<app::Application>& application);

		void add(SystemPtr system);
		bool remove(SystemPtr system);

		SystemPtr load(const std::string& name);
		SystemPtr get(const std::string& name) const;

		TaskManager& getTaskManager();

		const std::shared_ptr<app::Application>& getApplication();
		const std::shared_ptr<Config>& getConfig();
		const std::shared_ptr<core::Clock>& getClock();
		const std::shared_ptr<video::VideoSystem>& getVideo();
		const std::shared_ptr<input::Input>& getInput();
				
		const std::shared_ptr<entityx::EntityManager>& getEntityManager();
		const std::shared_ptr<entityx::SystemManager>& getSystemtEntity();

		const std::shared_ptr<GameScene::SceneManager>& getSceneManager();
		const std::shared_ptr<GameScene::SceneContainer>& getSceneContainer();

		const std::shared_ptr<core::cStateManager>& getStateManager();

		EventChannel& events();

		const void setElapsedTime(const double& t) {  mElapsedTime =t; }
		const void setGlobalTime(const double& t) { mGlobalTime = t; }

		const double& elapsedTime() { return mElapsedTime; }
		const double& globalTime() { return mGlobalTime; }

	private:
		void initializeSystems();
		void shutdownSystems();

		std::shared_ptr<app::Application> mApplication;
		std::shared_ptr<Config> mConfig;

		std::shared_ptr<video::VideoSystem> mVideo;
		std::shared_ptr<input::Input> mInput;
		std::shared_ptr<core::Clock> mClock;
		
		std::shared_ptr<GameScene::SceneContainer> mSceneContainer;
		std::shared_ptr<GameScene::SceneManager> mSceneManager;
		
		std::shared_ptr<entityx::EntityManager> mEntityManager;
		std::shared_ptr<entityx::SystemManager> mSystemtEntity;

		std::shared_ptr<rendering::RenderSystem> mRenderSystem;

		std::shared_ptr<core::cStateManager> mStateManager;
		

		eWindowLibraryType mWindowLibrary;

		SystemMap		mSystemMap;
		TaskManager		mTaskManager;
		EventChannel	mChannel;
		bool			mbRunning;

		double mElapsedTime; //seconds
		double mGlobalTime;  //seconds

	};
}


