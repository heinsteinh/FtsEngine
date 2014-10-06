
#include <thread>
#include <functional>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <chrono>

#include "ThreadBase.h"



namespace Framework
{

	class ThreadBody
	{

	private:
		std::shared_ptr< std::thread >	pThread;
		std::mutex	LockMutex;
		bool	isLive;

		Framework::Runnable	*pRunnable;

	public:
		ThreadBody(Framework::Runnable *_run)
		{

			pRunnable = _run;

			isLive = true;
			pThread = std::shared_ptr<std::thread>(new std::thread(std::bind(&Framework::ThreadBody::Run, this)));

		}

		~ThreadBody()
		{
			{
				std::lock_guard<std::mutex> Lock(LockMutex);
				isLive = false;
			}

			pThread->join();
		}

		void Run(){

			while (isLive)
			{
				{
					std::lock_guard<std::mutex> Lock(LockMutex);
					pRunnable->Run();
				}
				
				std::this_thread::sleep_for(std::chrono::seconds(1));				
			}
		}
	};
}

Framework::Thread::Thread(Framework::Runnable *pRunnable)
{
	pImpl = new ThreadBody(pRunnable);
}

Framework::Thread::~Thread(){

	if (pImpl){
		delete pImpl;
		pImpl = NULL;
	}
}