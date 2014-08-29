// objectPoolFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "TimeService.h"
#include "ObjectPool.h"
#include <iostream>



#include "LoggerInterface.h"


#include "TaskManager.h"
#include "Engine.h"
#include "ConsoleLogger.h"


class Application;
struct EngineOptions
{
	std::string basepath;
	std::string datapath;
	void* render_context;
	tin::LoggerInterface *logger_interface;
	int render_version;
	bool use_web_backend;
	bool run_in_background;
	Application* application;
	int window_width;
	int window_height;
};


int _tmain(int argc, _TCHAR* argv[])
{

	tin::TimeService t2;
	t2.InitTimeService();

	tin::TimeService* pObj = tin::ObjectPoolWithLock<tin::TimeService>::GetInstance().Pop();
	tin::ObjectPoolWithLock<tin::TimeService>::GetInstance().Push(pObj);
	
	std::shared_ptr<tin::TimeService> shrObj = tin::ObjectPoolWithLock<tin::TimeService>::GetInstance().PopShared();
	
	t2.Tick();
	std::cout << "New 1 time : " << t2.RunTime() << std::endl;

	

	tin::ConsoleLogger *logger = new tin::ConsoleLogger();
	tin::EngineOptions options;
	options.basepath = "";
	options.logger_interface = logger;
	options.render_version = tin::kOpenGLES20;
	options.use_web_backend = true;
	options.window_width = 320;
	options.window_height = 480;
	options.run_in_background = true;
	options.application = NULL;
	

	//tin::Engine::GetInstance().InitWithOptions(options);
		
	tin::TaskManager::GetInstance().CreateThreads(7);

	return 0;
}

