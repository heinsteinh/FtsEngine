

#pragma once

#include "lib.h"

#include<Windows.h>
namespace core {
	//windows-specific timer

	template <typename T>
	class Timer {
	public:
		Timer();

		void reset();
		T elapsed();

	private:
		T mTimeScale;
		bool mHighPerformance;
		__int64 mLastTime;
	};

	template <typename T>
	Timer<T>::Timer() :
		mTimeScale(0),
		mHighPerformance(false),
		mLastTime(0)
	{
		__int64 frequency = 0;

		if (QueryPerformanceFrequency((LARGE_INTEGER*)&frequency) == TRUE)
		{
			mTimeScale = static_cast<T>(1) / frequency;
			mHighPerformance = true;
		}
		else {
			mTimeScale = static_cast<T>(0.001);
			mHighPerformance = false;
		}

		reset();
	}

	template <typename T>
	T Timer<T>::elapsed() {
		__int64 current;
		if (mHighPerformance)
			QueryPerformanceCounter((LARGE_INTEGER*)&current);
		else
			current = GetTickCount();
		return (current - mLastTime) * mTimeScale;
	}

	template <typename T>
	void Timer<T>::reset() {
		if (mHighPerformance)
			QueryPerformanceCounter((LARGE_INTEGER*)&mLastTime);
		else
			mLastTime = GetTickCount();
	}
}

