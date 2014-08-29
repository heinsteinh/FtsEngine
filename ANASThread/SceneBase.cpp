#include "stdafx.h"
#include "SceneBase.h"



ANAS::SceneBase::SceneBase()
:pNextScene(NULL), isSceneEnd(false), isInitialized(false){

}


ANAS::SceneBase::~SceneBase(){

	//ANAS::Log::i("SceneBase", "Destructor");

}


ANAS::SceneManager::SceneManager(SceneContainer *pC)
: pContainer(pC), pScene(pC->pStartScene){

	
	pScene->SetContainer(pC);

	
	//pScene->SetResourceManager(&ResourceManager);


	pScene->Init();


	pThread = new Thread(this);
}


ANAS::SceneManager::~SceneManager()
{

	if (pThread){
		delete pThread;
	}

	//ANAS::Log::i("SCM", "Complete Destruct");
}

void ANAS::SceneManager::run(){
	//ANAS::Log::i("SCM", "running Scene Manager");


	if (pScene){

		if (pScene->CheckSceneEnd()){
			//ANAS::Log::i("SCM", "Detected Scene End");

			if (pScene->pNextScene){

				//ANAS::Log::i("SCM", "Step Scene");

				// Step
				SceneBase *_scene = pScene->pNextScene;
				delete pScene;
				pScene = _scene;

	
				pScene->SetContainer(pContainer);

	
				//pScene->SetResourceManager(&ResourceManager);

		
				pScene->Init();


			}
			else {
				// Exit.

				//ANAS::Log::i("SCM", "Scene Not Found. and Exit");

				/*
				delete pScene;
				pScene = NULL;
				*/

				pContainer->NotifySignal.Notification();
			}
		}
		else if (pScene->isInitialized)
		{
			pScene->Process();

			
			//pScene->Render();
		}
	}

	//Timer.AdjustTime(1 / 60.0f);

}