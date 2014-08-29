#include "stdafx.h"
#include "TestScene.h"




test::testScene::testScene()
{

}
test::testScene::~testScene()
{

}

void test::testScene::Init(){
	theta = 0;


	fts::Log::printf("testScene::Init()");

	// set flag initialized.
	SetInitialized();
}

void test::testScene::Process()
{

	//ANAS::InputData State;
	//do {
	//	State = pContainer->pInput->PopState();

	//	if (State.InputType == ANAS::IT_KEY){
	//		if (State.KeyChar == ANAS::IK_BACK){

	//			ANAS::Log::i("test Scene", "Detect Back Key");

	//			GameExit();
	//			//pNextScene = new test::testScene;
	//			//SetSceneEnd();

	//			break;
	//		}
	//	}
	//	else if (State.InputType == ANAS::IT_MOTION){
	//		mTestSprite.Pos[0] = State.Pos.x;
	//		mTestSprite.Pos[1] = State.Pos.y;
	//	}


	//} while (State.KeyChar != -1);


	//if( pContainer->pGraphic->CheckSleep() )
	{
		theta += 0.02f;

		fts::Log::printf("testScene::Process()");

		pContainer->pGraphic->submit(new ANAS::AnyTasking(std::bind(&testScene::Render, this)));
		pContainer->pGraphic->Swap(fabs(sin(theta)), fabs(cos(theta)), 0, 1);
	}


}

void test::testScene::Render()
{

	fts::Log::printf("testScene::Render()");

}