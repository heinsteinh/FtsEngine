#include "stdafx.h"
#include "BridgeParameter.h"


namespace ANAS
{


	BridgeParameter::BridgeParameter(ANativeActivity *_activity, void *_state, int _statesize)
		: activity(_activity)
		, savedState(_state)
		, savedStateSize(_statesize)
		, pApp(new ANAS::ANGLETestEnvironment())
		, pGrpahic(new ANAS::ClearTest())
	{
		/*pApp->InitUp();
		pGrpahic->Init();*/
	}



	BridgeParameter::~BridgeParameter()
	{
		/*pGrpahic->ShutDown();
		pApp->ShutDown();*/
	}

}



