#pragma once

#include "ThreadSync.h"

#include "ClearTest.h"
#include "Input.h"

namespace ANAS
{
	class ANativeActivity;
	class BridgeParameter : public ANAS::Signal
	{

	public:		
		ANativeActivity*	activity;
		void*				savedState;
		int					savedStateSize;

		BOOL bDone = FALSE;
		std::shared_ptr<ANAS::ANGLETestEnvironment> pApp;
		std::shared_ptr<ANAS::ClearTest> pGrpahic;		
		
		ANAS::Input*   mInput;
		


	public:
		BridgeParameter(ANativeActivity *_activity, void *_state, int _statesize);
		~BridgeParameter();
	
	};

}
