
#pragma once

#include <thread>
#include <memory>
#include <mutex>
#include <future>
#include <condition_variable>
#include <algorithm>

#include "concurrent_queue.h"


#include "eventbridge.h"
#include "eventhandler.h"
#include "eventchannel.h"

#include "task.h"

namespace core
{
	class BackgroundDummyTask : public Task {
	public:
		BackgroundDummyTask() : Task(BACKGROUND_REPEATING) {}
		virtual ~BackgroundDummyTask() {}
		virtual void run() 
		{		
			
			for (int i = 0; i < 1; i++)
			{
				{
					// This is the code of the job.
					long long sum = 0;
					for (int j = 0; j < 100000000L; j++)
						sum += rand();
					printf("AI: The sum was %lld\n", sum);
				}

				{
					long long sum = 0;
					for (int j = 0; j < 200000000L; j++)
						sum += rand();
					printf("Graphics job: got %lld\n", sum); // this makes no sense, its just code that runs.
				}
			}

		}
	};

	class join_threads
	{
		std::vector<std::thread>& threads;
	public:
		explicit join_threads(std::vector<std::thread>& threads_) :threads(threads_)
		{}
		~join_threads()
		{
			for (unsigned long i = 0; i < threads.size(); ++i)
			{
				if (threads[i].joinable())
					threads[i].join();
			}
		}
	};


	

	class  TaskManager
	{
	public:
		typedef std::shared_ptr<Task> TaskPtr;
		typedef ConcurrentQueue<TaskPtr> TaskList;

		join_threads joiner;
		struct StopEvent {};

		TaskManager(unsigned int numThreads = 0); //0 for autodetect
		~TaskManager();
		
		


		void add(TaskPtr task);
		void start();
		void stop();

		void handle(const StopEvent& se);
		void handle(const Task::TaskCompleted& tc);
		void handle(const Task::TaskBeginning& tb);
		
	private:
		void worker();
		void execute(TaskPtr task);
		void synchronize();

		std::vector<std::thread> mThreads;
		unsigned int mNumThreads;

		std::atomic<bool> mRunning;

		EventChannel mChan;

		TaskList mTaskList[2];
		TaskList mBackgroundTasks;
		TaskList mSyncTasks;

		unsigned int mReadList;
		unsigned int mWriteList;

		typedef std::mutex Mutex;
		typedef std::condition_variable Condition;
		typedef std::unique_lock<Mutex> ScopedLock;

		mutable Mutex mSyncMutex;
		Condition mCondition;
		unsigned int mNumTasksToWaitFor;

	};


}
