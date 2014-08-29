#include "stdafx.h"
#include "VideoSystem.h"



#include "Engine.h"


#include "eventbridge.h"
#include "eventhandler.h"
#include "eventchannel.h"

#include <memory>
#include <map>
#include <iostream>



namespace video
{
	
	using namespace core;

	VideoSystem::VideoSystem() : core::System("Video") 
	{
		enableUpdater(core::Task::SINGLETHREADED_REPEATING);

		//register this class as an event handler for the "Removing/Closing Window event"		
		EventChannel chan;
		chan.add<RemoveWindow>(*this); //if a window is closed, act!
		chan.add<ShutdownEngine>(*this);

		mCamMode = video::VideoSystem::PERSPECTIVE;
		

	}

	VideoSystem::~VideoSystem() {}

	bool VideoSystem::init()
	{
		System::init();

		
		// Qt uses its own threads... so there is nothing to do here except to create an application...
		// Update: I try to wrap qtwidgets in this system as well, create either glfw-windows OR qt-windows...
		if (mEngine->windowType() == Engine::USE_GLFW3) 
		{
			

			EventChannel chan;
			for (WindowMap::iterator it = mWindowMap.begin(); it != mWindowMap.end(); ++it)
			{
				if (!it->second->create()) {
					mLog << "Failed to create window \'" << it->first << "\'";
					mLog << "Aborting" << std::endl;
					return false;
				}
				else {
					chan.broadcast(WindowCreated(it->second));
					mLog << "Created window \'" << it->first << "\'" << std::endl;
				}
			}
			
		}		
		else 
			
		{
			mLog << "Unsupported window creation... aborting program!" << std::endl;
			return false;
		}

		return true;
	}

	void VideoSystem::update() 
	{
		if (mEngine == NULL)
			return;

		//only 60 frames...
		if (mEngine->elapsedTime() < (double)(1.0 / 60.0))
			return;

		EventChannel chan;
		chan.broadcast(PreUpdate());

		

		std::vector<WindowMap::iterator> remover;
		for (WindowMap::iterator it = mWindowMap.begin(); it != mWindowMap.end(); ++it) 
		{
						
			// save elapsed time
			it->second->mTimeElapsedSinceLastFrame = mEngine->elapsedTime();

			if (mEngine->windowType() == Engine::USE_QT)
			{
				//Qt specific
				//Qt handles rendering and updating itself because of theadsafety
			}
			else if (mEngine->windowType() == Engine::USE_GLFW3)
			{
				//GLFW specific
				//execute!!
				it->second->render(mEngine->elapsedTime());
				//it->second->run();
			}

			if (it->second->isClosed())
				remover.push_back(it);
		}


		//closed windows don't need any updates at all..., Qt destroys his widgets itself
		for (const WindowMap::iterator &it : remover)
			chan.broadcast(RemoveWindow(it, mEngine->windowType() == Engine::USE_GLFW3 ? true : false));

		if (mWindowMap.size() == 0)
			chan.broadcast(ShutdownEngine());
		
		chan.broadcast(PostUpdate());
	}


	void VideoSystem::shutdown()
	{
		System::shutdown();

		for (WindowMap::iterator it = mWindowMap.begin(); it != mWindowMap.end(); ++it) {
			it->second->destroy();
			mLog << "Destroying window \'" << it->first << "\'" << std::endl;
		}

		
		if (mEngine->windowType() == Engine::USE_GLFW3) 
		{
			//glfwTerminate();
		}
	}


	void VideoSystem::addWindow(WindowPtr window, const std::string &s)
	{
		if (window != nullptr)
		if (mWindowMap.find(s) == mWindowMap.end())
		{
			
			mWindowMap[s] = window; 
			addSetting("Width", &window->mHeight);
			addSetting("Height", &window->mHeight);

			addSetting("Fullscreen", &window->mFullScreen);
			addSetting("AutoSizeWindow", &window->mAutoSizeWindow);
			addSetting("Title", &window->mTitle);
		}
			
		else
			mLog << "Window \'" << s << "\' already added!" << std::endl;
	}

	const VideoSystem::WindowPtr& VideoSystem::getWindow(const std::string &s)
	{
		return mWindowMap[s];
	}

	void VideoSystem::removeWindow(const std::string &s, bool destroy)
	{
		auto it = mWindowMap.find(s);
		if (it != mWindowMap.end()) 
		{
			if (destroy)
				it->second->destroy();

			mWindowMap.erase(it);
		}
	}
	


	void VideoSystem::handle(const ShutdownEngine&) 
	{
		mEngine->stop();
	}

	void VideoSystem::handle(const RemoveWindow& rw)
	{
		//'faster' solution for closing a window; no search in a map needed... but more costly in terms of storage
		//and function calls
		if (rw.mDestroy)
			rw.mRemovableWindow->second->destroy();
		else //don't destroy it but store the removed window in a seperate strcture
			mRemovedWindowsMap[rw.mRemovableWindow->first] = rw.mRemovableWindow->second;
		//erase window
		mWindowMap.erase(rw.mRemovableWindow);
	}

}