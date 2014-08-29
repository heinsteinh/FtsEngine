#include "stdafx.h"
#include "UserThread.h"
#include "LogThread.h"



namespace fk {
	UserThread::UserThread() {
		Log::Verbose("[UserThread] Constructor");
	}

	UserThread::~UserThread() {
		Log::Verbose("[UserThread] Destructor");
	}

	void UserThread::Initialize() {
		Log::Verbose("[UserThread] Initialize");
	}

	void UserThread::LoopIteration() 
	{

		/*
		if (KEYDOWN(ESCAPE)) {
			NotifyStop();
			return;
		}*/

		std::this_thread::sleep_for(std::chrono::seconds(10));

		NotifyStop();

	}

	void UserThread::Terminate() 
	{
		Log::Verbose("[UserThread] Terminate");
	}
}