#include "stdafx.h"
#include "ThreadBase.h"


#include <Windows.h>  // forl sleep
#include <thread>
#include <functional>
#include <memory>
#include <mutex>
#include <condition_variable>



#include <chrono>


#include "ThreadBase.h"



namespace BubbleBattleBoids
{

	class ThreadBody
	{

	private:
		std::shared_ptr< std::thread >	pThread;
		std::mutex	LockMutex;
		bool	isLive;

		BubbleBattleBoids::Runnable	*pRunnable;

	public:
		ThreadBody(Runnable *_run)
		{

			pRunnable = _run;

			isLive = true;
			pThread = std::shared_ptr<std::thread>(new std::thread(std::bind(&ThreadBody::Run, this)));

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

	Thread::Thread(Runnable *pRunnable)
	{
		pImpl = new ThreadBody(pRunnable);
	}

	Thread::~Thread(){

		if (pImpl){

			delete pImpl;
		}
	}
}

