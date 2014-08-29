#pragma once

#include "SceneManager.h"

namespace test {


	class TestScene : public GameScene::SceneBase 
	{
	private:
		float theta;			


		bool bInit;
	public:

		TestScene();
		~TestScene();

		
		void Init();
		void Process();
		void Render();
		void Shutdown();

		typedef std::shared_ptr<test::TestScene> TestScenePtr;
	};


	class TestSceneB : public GameScene::SceneBase
	{
	private:
		float theta;


		bool bInit;
	public:

		TestSceneB();
		~TestSceneB();


		void Init();
		void Process();
		void Render();
		void Shutdown();

		typedef std::shared_ptr<test::TestScene> TestScenePtr;
	};
}

