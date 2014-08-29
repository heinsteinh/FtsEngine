#include "stdafx.h"
#include "SystemEntity.h"

#include "Engine.h"

namespace entityx {

	BaseSystem::Family BaseSystem::family_counter_;


	SystemManager::SystemManager() :core::System("SystemManager Entity")		
	{		
		enableUpdater();
	}

	
	/* general */
	bool SystemManager::init()
	{
		core::System::init();
		
		configure();
		return true;
	}

	void SystemManager::update()
	{

		core::System::update();

		//only 60 frames...
		if (mEngine->elapsedTime() < (double)(1.0 / 60.0))
			return;
		
		core::EventChannel event_manager_;
		std::vector<systems::iterator> remover;
		for (systems::iterator it = systems_.begin(); it != systems_.end(); ++it)
		{
			assert(initialized_ && "SystemManager::configure() not called");

			it->second->update(*mEngine->getEntityManager().get(), event_manager_, mEngine->elapsedTime());
		}

	}

	void SystemManager::shutdown()
	{
		core::System::shutdown();

		for (systems::iterator it = systems_.begin(); it != systems_.end(); ++it) {
			it->second->destroy();
			mLog << "Destroying systems entity \'" << it->first << "\'" << std::endl;
		}
	}
	
	void SystemManager::configure() 
	{
		core::EventChannel event_manager_;
		for (auto &pair : systems_)
		{			
			pair.second->configure(event_manager_);
		}
		initialized_ = true;
	}

} // namespace entityx