#pragma once

#include "InputActivity.h"
#include "Graphic.h"
#include "ThreadBase.h"
#include "Timer.h"
#include "Logger.h"


namespace ANAS {

	class SceneBase;
	class SceneManager;


	class SceneContainer {
	public:

		SceneBase	*pStartScene;

		
		ANAS::InputActivity	*pInput;
		ANAS::Graphic	*pGraphic;
		ANAS::Signal	NotifySignal;


	};


	class SceneBase {
		friend class SceneManager;

	private:
		bool	isSceneEnd;
		bool	isInitialized;

	
		inline void SetContainer(SceneContainer * pC){
			pContainer = pC;
		}

		


	protected:

		SceneContainer	*pContainer;
		SceneBase	*pNextScene;


	public:

		static SceneBase	*pStartScene;

		SceneBase();
		virtual ~SceneBase();

		
		virtual void Init() = 0;

		
		virtual void Process() = 0;
		
		virtual void Render() = 0;


		void SetInitialized(){
			isInitialized = true;
		}

	
		void SetSceneEnd(){
			isSceneEnd = true;
		}


		bool CheckSceneEnd(){
			return isSceneEnd;
		}

	
		void GameExit(){
			if (pNextScene){
				delete pNextScene;
				pNextScene = NULL;
			}
			isSceneEnd = true;
		}
	};

	class SceneManager : public Runnable {

	private:

		SceneContainer	*pContainer;
		SceneBase	*pScene;
		Thread	*pThread;
		Time				Timer;


		SceneManager();
	public:


		SceneManager(SceneContainer *pContainer);

		~SceneManager();

		
		void run();
	};
}



