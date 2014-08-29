#pragma once


#include "System.h"
#include "WindowVideo.h"
#include <memory>
#include <map>
#include <iostream>

namespace video
{

	class  VideoSystem : public core::System
	{
		
	public:
		typedef std::shared_ptr<VideoSystem> VideoSystemPtr;

		typedef std::shared_ptr<core::Window> WindowPtr;
		typedef std::map<std::string, WindowPtr> WindowMap;
		
		enum eCamMode { PERSPECTIVE, ORTHOGRAPHIC, TOP, LEFT, RIGHT, FRONT, BOTTOM, BACK };
		
		VideoSystem();
		~VideoSystem();

		// Events
		struct WindowCreated 
		{
			WindowCreated(const WindowPtr& window) : mWindow(window) {}

			WindowPtr mWindow;
		};

		struct RemoveWindow 
		{
			RemoveWindow(const WindowMap::iterator& windowIt, bool destroy = true) : mRemovableWindow(windowIt),
			mDestroy(destroy) {}
			bool mDestroy;
			WindowMap::iterator mRemovableWindow;
		};

		struct ShutdownEngine {};

		struct PreUpdate {};
		struct PostUpdate {};


		/* event based */
		void handle(const ShutdownEngine&);
		void handle(const RemoveWindow& tc);


		/* general */
		bool init();
		void update();
		void shutdown();

		/* window specific */
		void addWindow(WindowPtr window, const std::string &s);
		const WindowPtr& getWindow(const std::string &s);
		void removeWindow(const std::string &s, bool destroy = true);
		
		void setCameraMode(eCamMode e) { std::cout << "Changed Mode" << std::endl; mCamMode = e; }
		video::VideoSystem::eCamMode getCameraMode() { return mCamMode; }

	private:
		WindowMap mWindowMap;
		WindowMap mRemovedWindowsMap;
		eCamMode  mCamMode;
	};

}