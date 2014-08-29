#include "stdafx.h"
#include "RenderThread.h"
#include "LogThread.h"

namespace fk {
	RenderThread::RenderThread()
	{
		Log::Verbose("[RenderThread] Constructor");
	}

	RenderThread::~RenderThread() 
	{
		Log::Verbose("[RenderThread] Destructor");
	}

	void RenderThread::Initialize()
	{
		Log::Verbose("[RenderThread] Initialize");
	}

	void RenderThread::LoopIteration() 
	{
		std::this_thread::sleep_for(std::chrono::seconds(10));

		NotifyStop();
	}

	void RenderThread::Terminate() {
		Log::Verbose("[RenderThread] Terminate");
	}
}