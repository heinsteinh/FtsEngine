#pragma once


#include "lib.h"
#include "system.h"
#include "timer.h"

namespace core 
{
	class Clock :
		public System
	{
	public:
		Clock();
		virtual ~Clock();

		void update();

		float delta() const;
		float getCurrentTime();

		float fps() const;

	private:
		Timer<float> mTimer;

		float mLastTime;
		float mLastFPSTime;
		float mDelta;
		float mFPS;
	};
}
