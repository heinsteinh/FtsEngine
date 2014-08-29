#include "stdafx.h"



#include <Windows.h>  // forl sleep
#include <thread>
#include <functional>
#include <memory>
#include <mutex>
#include <condition_variable>



#include <chrono>


#include "ThreadBase.h"



namespace ANAS
{

	class ThreadBody
	{

	private:
		std::shared_ptr< std::thread >	pThread;
		std::mutex	LockMutex;
		bool	isLive;

		ANAS::Runnable	*pRunnable;

	public:
		ThreadBody(ANAS::Runnable *_run)
		{

			pRunnable = _run;

			isLive = true;
			pThread = std::shared_ptr<std::thread>(new std::thread(std::bind(&ANAS::ThreadBody::Run, this)));

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
					pRunnable->run();
				}
				
				Sleep(0);
				//usleep(0);				
			}
		}
	};
}

ANAS::Thread::Thread(ANAS::Runnable *pRunnable)
{
	pImpl = new ThreadBody(pRunnable);
}

ANAS::Thread::~Thread(){

	if (pImpl){

		delete pImpl;
	}
}