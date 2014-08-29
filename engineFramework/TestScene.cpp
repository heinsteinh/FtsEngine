#include "stdafx.h"
#include "TestScene.h"



namespace test
{

	TestScene::TestScene() :SceneBase("TestScene")
	{
		bInit = false;
		theta = 0;
	}

	TestScene::~TestScene()
	{		
		bInit = false;
		theta = 0;
	}


	void TestScene::Init()
	{
		if (bInit)
			return;

		theta = 0;
		
		
		// set flag initialized.
		SetInitialized();

		bInit = true;
	}

	void TestScene::Process()
	{
		gLog << "Process  Test Scene" << std::endl;		

		
	}


	void TestScene::Render()	
	{
		
		gLog << "Render  Test Scene" << std::endl;		
	}



	void TestScene::Shutdown()
	{
		bInit = false;
	}




	/***************************************************/

	TestSceneB::TestSceneB() :SceneBase("TestSceneB")
	{
		bInit = false;
		theta = 0;
	}

	TestSceneB::~TestSceneB()
	{
		bInit = false;
		theta = 0;
	}


	void TestSceneB::Init()
	{
		if (bInit)
			return;

		theta = 0;


		// set flag initialized.
		SetInitialized();

		bInit = true;
	}

	void TestSceneB::Process()
	{
		gLog << "Process  Test Scene" << std::endl;
	}


	void TestSceneB::Render()
	{
		gLog << "Render  Test Scene" << std::endl;
	}



	void TestSceneB::Shutdown()
	{
		bInit = false;
	}
}