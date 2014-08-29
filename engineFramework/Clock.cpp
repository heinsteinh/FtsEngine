#include "stdafx.h"
#include "Clock.h"

namespace core 
{
	Clock::Clock() : System("Clock", Task::SINGLETHREADED_REPEATING)
	{
		mLastTime = mTimer.elapsed();
		mLastFPSTime = mLastTime;
		mFPS = 60.0f;
	}

	Clock::~Clock() {
	}

	void Clock::update() 
	{
		static int tick = 0;

		++tick;
		float currentTime = mTimer.elapsed();
		mDelta = currentTime - mLastTime;
		mLastTime = currentTime;

		//reevaluate fps across the last couple of frames (at least 5)
		if ((tick >= 5) && ((currentTime - mLastFPSTime) > 0.1f)) {
			mFPS = tick / (currentTime - mLastFPSTime);
			tick = 0;
			mLastFPSTime = currentTime;
		}
	}

	float Clock::delta() const {
		return mDelta;
	}

	float Clock::getCurrentTime() {
		return mTimer.elapsed();
	}

	float Clock::fps() const {
		return mFPS;
	}
}
