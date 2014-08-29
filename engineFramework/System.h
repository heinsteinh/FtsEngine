#pragma once


#include <thread>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <algorithm>

#include "log.h"
#include "eventbridge.h"
#include "eventhandler.h"
#include "eventchannel.h"
#include "Named.h"
#include "task.h"

#include "NonCopyable.h"


namespace core 
{
	class Engine;
	class  System : public util::Named ,  entityx::help::NonCopyable 
	{
	public:
		friend class Engine;  //allows the Engine class to combine all system settings

		struct SystemInitializing
		{
			SystemInitializing(System* system);
			System* mSystem;
		};

		struct SystemShuttingDown
		{
			SystemShuttingDown(System* system);
			System* mSystem;
		};


		struct SystemUpdater : public Task
		{
			SystemUpdater(System* s, unsigned int taskFlags = Task::SINGLETHREADED_REPEATING);

			virtual void run();

			System* mSystem;
		};


		System(const std::string& name, unsigned int taskFlags = Task::NONE);
		virtual ~System();

		virtual bool init();
		virtual void update();
		virtual void shutdown();

		template<typename T>
		void addSetting(const std::string& name_in_configfile, T* the_variable);


	protected:
		std::shared_ptr<SystemUpdater> mSystemUpdater;
	
		
		void enableUpdater(unsigned int taskFlags = Task::SINGLETHREADED_REPEATING);	
		
		Logger			mLog;
		EventChannel	mChannel;
		Engine*			mEngine;
	};

	template <typename T>
	void System::addSetting(const std::string& name, T* var) 
	{
		std::stringstream sstr;
		sstr << getName() << "." << name;
		
		//mSettings.add_options()(sstr.str().c_str(), boost::program_options::value<T>(var));
	}
}
