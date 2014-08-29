#include "stdafx.h"
#include "ThreadBase.h"



namespace fk
{
	Thread::Thread()
	{

	}

	Thread::~Thread()
	{
		if (!stopped_) throw std::exception("Thread destructor called when thread running.");

		if (thread_.joinable()) 
			thread_.join();
	}

	void Thread::NotifyStart() 
	{
		if (!stopped_) 
			throw std::exception("Thread NotifyStart called when thread running.");

		stopped_ = false;
		loop_ = true;
		thread_ = std::thread(&Thread::Loop, this);
	}

	void Thread::StartOnThisThread() 
	{
		if (!stopped_) throw std::exception("Thread StartOnThisThread called when thread running.");
		stopped_ = false;
		loop_ = true;
		Loop();
	}

	void Thread::NotifyStop() {
		loop_ = false;
	}

	void Thread::WaitForStop()
	{
		std::unique_lock<std::mutex> lock(stoppedmutex_);
		
		if (stopped_)
			return;

		stoppedcondition_.wait(lock, [this]{return stopped_; });
	}

	void Thread::Loop() 
	{
		Initialize();
		
		while (loop_)
		{
			LoopIteration();
		}

		Terminate();

		std::unique_lock<std::mutex> lock(stoppedmutex_);
		stopped_ = true;
		stoppedcondition_.notify_all();
	}
}



