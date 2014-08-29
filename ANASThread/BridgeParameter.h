#pragma once

#include "SignalThread.h"


namespace runApp
{

	class ANativeActivity;
	class BridgeParameter : public ANAS::Signal
	{

	public:
		ANativeActivity *activity;
		void	*savedState;
		int	savedStateSize;

	private:
		BridgeParameter();

	public:


		BridgeParameter(ANativeActivity *_activity, void *_state, int _statesize)
			: activity(_activity), savedState(_state), savedStateSize(_statesize)
		{

		}


	};

	void android_main(ANativeActivity* activity, void* savedState, size_t savedStateSize);
}