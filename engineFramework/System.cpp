#include "stdafx.h"
#include "System.h"

namespace core {

	System::System(const std::string& name, unsigned int taskFlags) : util::Named(name)
	{
			if (taskFlags != Task::NONE)
				mSystemUpdater.reset(new SystemUpdater(this, taskFlags));
		}

	System::~System() {
	}

	System::SystemInitializing::SystemInitializing(System* s) : mSystem(s) 
	{
	}

	System::SystemShuttingDown::SystemShuttingDown(System* s) : mSystem(s)
	{
	}

	bool System::init() 
	{
		mChannel.broadcast(SystemInitializing(this));
		mLog.setPrefix("[" + getName() + "] ");
		mLog.add(new std::ofstream(getName() + ".log"));
		return true;
	}

	void System::update() 
	{
	}

	void System::shutdown() 
	{
		mChannel.broadcast(SystemShuttingDown(this));
	}

	System::SystemUpdater::SystemUpdater(System* s, unsigned int taskFlags) : Task(taskFlags), mSystem(s)
	{
	}

	void System::enableUpdater(unsigned int taskFlags )
	{
		mSystemUpdater.reset(new SystemUpdater(this, taskFlags));
	}

	void System::SystemUpdater::run()
	{
		mSystem->update();
	}


}