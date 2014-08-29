#include "stdafx.h"
#include "StateMachine.h"
#include "Engine.h"


namespace core
{

	cStateManager::cStateManager() :System("StateMachine")
	{
		enableUpdater();

	}


	cStateManager::~cStateManager()
	{
	}


	bool cStateManager::init()
	{
		System::init();

		
		for (StateMachineMap::iterator it = mStateMachineMap.begin(); it != mStateMachineMap.end(); ++it)
		{
			if (!it->second->GetActiveState()->ExecuteStateEnter(this))
			{
				mLog << "Failed to create window \'" << it->first << "\'";
				mLog << "Aborting" << std::endl;
				return false;
			}
			else 
			{
				///chan.broadcast(StateMachineEnter(it->second));
				mLog << "Init StateMachineEnter \'" << it->first << "\'" << std::endl;
			}
		}

		return true;
	}


	void cStateManager::update()
	{
		System::update();


		std::vector<StateMachineMap::iterator> remover;
		for (StateMachineMap::iterator it = mStateMachineMap.begin(); it != mStateMachineMap.end(); ++it)
		{
			core::UpdateDelay updater(mEngine->elapsedTime());
			//it->second->Update(updater);			
			it->second->GetActiveState()->ExecuteStateUpdate(this, updater);

			// save elapsed time
			//it->second->mTimeElapsedSinceLastFrame = mEngine->elapsedTime();				
		}
	}
	

	void cStateManager::shutdown()
	{
		System::shutdown();

		for (StateMachineMap::iterator it = mStateMachineMap.begin(); it != mStateMachineMap.end(); ++it) 
		{
			it->second->GetActiveState()->ExecuteStateExit(this);
			mLog << "Destroying Active State StateMachineMap \'" << it->first << "\'" << std::endl;
		}
	}


	void cStateManager::addStateMachine(StateMachinePtr stateMachine, const std::string &s)
	{
		if (stateMachine != nullptr)
		if (mStateMachineMap.find(s) == mStateMachineMap.end())
		{
			mStateMachineMap[s] = stateMachine;
		}
		else
			mLog << "StateMachine \'" << s << "\' already added!" << std::endl;
	}

	const cStateManager::StateMachinePtr& cStateManager::getStateMachine(const std::string &s)
	{
		return mStateMachineMap[s];
	}


	void cStateManager::removeStateMachine(const std::string &s, bool destroy)
	{
		auto it = mStateMachineMap.find(s);
		if (it != mStateMachineMap.end())
		{
			if (destroy)
				it->second->GetActiveState()->ExecuteStateExit(this);

			mStateMachineMap.erase(it);
		}
	}

}


