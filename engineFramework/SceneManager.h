#pragma once


#include "Taskmanager.h"
#include "System.h"
#include "WindowVideo.h"
#include "VideoSystem.h"

#include "Input.h"
#include "SceneGraph.h"


namespace GameScene
{

	class SceneBase;
	typedef std::shared_ptr<SceneBase> SceneBasePtr;
	class SceneManager;


	class SceneContainer: public zephyr::scene::SceneGraph
	{

	private:
		typedef std::map<std::string, SceneBasePtr> SceneMap;
		typedef std::pair< std::string, SceneBasePtr > SceneContainerEntry;

	
	public:
		SceneBasePtr				mActiveScene;		
		input::Input::InputPtr		mInput;
		video::VideoSystem			mGraphic;
		

	public:
		SceneContainer::SceneContainer();	
		SceneContainer::~SceneContainer();
		


		struct SceneChangeEvent { };
		struct SceneAddEvent {};

		void handle(const SceneChangeEvent& event);
		void handle(const SceneAddEvent& event);


		void InitSceneContainer();
		void ShutdownSceneContainer();

		void addScene(const SceneBasePtr& newScene);
		void removeScene(const std::string &s, bool destroy);

		
		bool changeScene(const std::string& nextSceneName);
		bool changeScene(const GameScene::SceneBasePtr& nextScene);
		
		const SceneBasePtr& getScene(const std::string &s);
		const SceneBasePtr& getScene(const GameScene::SceneBasePtr& scene);

		SceneMap			getContainer()	{ return mSceneContainer;	}
		const SceneBasePtr& GetActiveScene(){ return mActiveScene; }

	private:
		SceneMap			mSceneContainer;
	};




	class Resource;
	class SceneBase: public util::Named
	{
		friend class SceneManager;

	private:
		bool	isSceneEnd;
		bool	isInitialized;


		void SetContainer(SceneContainer * pC);


		
		inline void SetResourceManager(Resource *pResourceMgr)
		{
		pResource = pResourceMgr;
		}


	protected:

		SceneContainer	*pContainer;
		SceneBasePtr 	pNextScene;

		Resource	*pResource;

	public:

		static SceneBase	*pStartScene;

		SceneBase(const std::string& sceneName);
		virtual ~SceneBase();


		virtual void Init() = 0;

		virtual void Process() = 0;

		virtual void Render() = 0;

		virtual void Shutdown() = 0;


		void SetInitialized(){
			isInitialized = true;
		}


		void SetSceneEnd(){
			isSceneEnd = true;
		}


		bool CheckSceneEnd(){
			return isSceneEnd;
		}


		void GameExit()
		{
			
			isSceneEnd = true;
		}
	};



	class ResourceManager;
	class SceneManager : public core::System
	{

	public:
		typedef std::shared_ptr<SceneManager> SceneManagerPtr;		
		std::shared_ptr<core::Window> linkedWindow;

	public:
		SceneManager(SceneContainer *pContainer);
		~SceneManager();

		struct SceneUpdater : public core::Task
		{
			SceneUpdater(SceneManager *sceneManager, uint8_t taskFlags = Task::SINGLETHREADED_REPEATING);
			virtual void run();

			SceneManager* pSceneManager;
		};


		struct RenderItem {
			zephyr::scene::NodePtr node;
			//EntityPtr entity;
		};


		
		
		//bool addScene(const SceneBasePtr& newScene);
		//bool changeScene(const GameScene::SceneBasePtr& nextScene);
		//bool changeScene(const std::string& nextSceneName);
		
		bool setActiveScene(const std::string& nextSceneName);
		const SceneBasePtr& getActiveScene() const;
		



		bool init();
		void update();
		void shutdown();
		
	private:
		SceneContainer		*pContainer;

//		Resource*			ResourceManager;
				
		SceneBasePtr		mNextScene;
		SceneBasePtr		mCurrentScene;		

		

	};


}
