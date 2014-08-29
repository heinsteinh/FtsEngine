#pragma once

#include "SignalThread.h"


namespace ANAS
{
	class ThreadLoader : public Signal
	{

	private:
		// for thread
		typedef	std::shared_ptr<std::thread> THREAD_PTR;
		THREAD_PTR	PollThread;


	public:
		ThreadLoader();
		~ThreadLoader();
		
		static std::shared_ptr<ThreadLoader> instance();
		bool Enqueue(const std::function<bool()>& doLoad, const std::function<void(bool)>& loadComplete);
		bool Enqueue(const std::function<bool()>& doLoad);



	};

}

