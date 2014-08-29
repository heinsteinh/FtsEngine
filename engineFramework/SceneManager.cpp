#include "stdafx.h"
#include "SceneManager.h"

#include "Lib.h"

namespace GameScene
{


	//*******************************************************************************************************************************/
	//*******************************************************************************************************************************/



	SceneContainer::SceneContainer()
	{
		mActiveScene = nullptr;
	}

	SceneContainer::~SceneContainer()
	{
	}

	void SceneContainer::InitSceneContainer()
	{
		core::EventChannel mEchan;
		mEchan.add<SceneContainer::SceneChangeEvent>(*this);
		mEchan.add<SceneContainer::SceneAddEvent>(*this);
	}

	void SceneContainer::ShutdownSceneContainer()
	{
		auto delete_scenes_function = [&](SceneContainerEntry entry) { entry.second.reset();		};
		for_each(mSceneContainer.begin(), mSceneContainer.end(), delete_scenes_function);

		core::EventChannel mEchan;
		mEchan.remove<SceneContainer::SceneChangeEvent>(*this);
		mEchan.remove<SceneContainer::SceneAddEvent>(*this);

	}


	void SceneContainer::addScene(const SceneBasePtr& newScene)
	{
		if (newScene != nullptr)
		if (mSceneContainer.find(newScene->getName()) == mSceneContainer.end())
		{
			mSceneContainer[newScene->getName()] = newScene;

			mActiveScene = newScene;
			mActiveScene->Init();
			//set Ressouce Mnger

			core::EventChannel mEchan;
			mEchan.broadcast(SceneAddEvent());
		}

		else
		{

			gLog << "newScene \'" << newScene->getName() << "\' already added!" << std::endl;
		}
	}

	void SceneContainer::removeScene(const std::string &s, bool destroy)
	{
		auto it = mSceneContainer.find(s);
		if (it != mSceneContainer.end())
		{
			if (destroy)
				it->second->Shutdown();

			mSceneContainer.erase(it);
		}
	}


	const SceneBasePtr& SceneContainer::getScene(const std::string &s)
	{
		return mSceneContainer[s];
	}
	
	const SceneBasePtr& SceneContainer::getScene(const GameScene::SceneBasePtr& scene)
	{
		return mSceneContainer[scene->getName()];
	}

	bool SceneContainer::changeScene(const GameScene::SceneBasePtr& nextScene)
	{		
		SceneMap::const_iterator find = mSceneContainer.find(nextScene->getName());
		if (find == mSceneContainer.cend())
			return false;

		if (mActiveScene != nullptr)
		{
			mActiveScene->Shutdown();
		}

		mActiveScene = find->second;
		mActiveScene->Init();
		
		return true;
		
	}
	
	

	bool SceneContainer::changeScene(const std::string& nextSceneName)
	{
		if (mSceneContainer.find(nextSceneName) != mSceneContainer.end()) { //the scene exists
			return changeScene(mSceneContainer[nextSceneName]);
		}

		return false;	
	}



	void SceneContainer::handle(const SceneContainer::SceneChangeEvent& event)
	{
		gLog.info() << "SSceneManager::handle: SceneChangeEvent" << std::endl;
		int i = 0;
	}


	void SceneContainer::handle(const SceneContainer::SceneAddEvent& event)
	{
		gLog.info() << "SSceneManager::handle: SceneAddEvent" << std::endl;
		int i = 0;
	}




	//*******************************************************************************************************************************/
	//*******************************************************************************************************************************/



	SceneBase::SceneBase(const std::string& sceneName) 
		: util::Named(sceneName)
		, pNextScene(NULL)
		, pContainer(NULL)
		, isSceneEnd(false)
		, isInitialized(false)
	{

	}


	SceneBase::~SceneBase()
	{
		gLog.info() << "SceneBase:	Destructor" << std::endl;
	}


	void SceneBase::SetContainer(SceneContainer * pC)
	{
		pContainer = pC;
	}



	//*******************************************************************************************************************************/
	//*******************************************************************************************************************************/




	SceneManager::SceneManager(SceneContainer* pC) :System("SceneManagerSystem", core::Task::REPEATING), pContainer(pC), mCurrentScene(pC->GetActiveScene())
	{
		//enableUpdater();
		mCurrentScene->SetContainer(pContainer);
		//pScene->SetResourceManager(&ResourceManager);	
	}


	SceneManager::~SceneManager()
	{

	}





	/////////////////////// SCENE UPDATING TASK ///////////////////////
	SceneManager::SceneUpdater::SceneUpdater(SceneManager *scm, uint8_t taskFlags) : pSceneManager(scm), Task(taskFlags) {}

	void SceneManager::SceneUpdater::run()
	{
		
		//gLog.info() << "SCM: running Scene Manager" << std::endl;
		
	}

	/////////////////////// !SCENE UPDATING TASK ///////////////////////


	bool SceneManager::init()
	{	
		pContainer->InitSceneContainer();	
		return true;
	}

	
	void SceneManager::update()
	{
		gLog.info() << "SCM: running Scene Manager" << std::endl;



		if (mCurrentScene)
		{

			if (mCurrentScene->CheckSceneEnd())
			{
				gLog.info() << "SCM: Detected Scene End" << std::endl;

				if (mCurrentScene->pNextScene)
				{
					gLog.info() << "SCM:	Step Scene" << std::endl;

					// Step
						pContainer->changeScene(mCurrentScene->pNextScene);
					//mCurrentScene->SetContainer(pContainer);
					//mCurrentScene->SetResourceManager(&ResourceManager);
					//mCurrentScene->Init();


				}
				else
				{
					// Exit.
					gLog.error() << "SCM:   Scene Not Found. and Exit" << std::endl;
					/*
					delete pScene;
					pScene = NULL;
					*/
					//pContainer->NotifySignal.Notification();
				}
			}
			else if (mCurrentScene->isInitialized)
			{
				mCurrentScene->Process();
				//pScene->Render();
			}
		}

		std::this_thread::sleep_for(std::chrono::seconds(1 / 60));
		//Timer.AdjustTime(1 / 60.0f);
	}


	void SceneManager::shutdown()
	{		
		mCurrentScene->GameExit();
		gLog.info() << "SCM: Complete Destruct" << std::endl;

		pContainer->ShutdownSceneContainer();
	}	

}