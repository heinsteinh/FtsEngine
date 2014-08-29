#pragma once



#pragma once

#include <thread>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <algorithm>

#include "concurrent_queue.h"

//
//#include "eventbridge.h"
//#include "eventhandler.h"
//#include "eventchannel.h"

#include "task.h"

namespace core
{
	class BackgroundDummyTask : public Task 
	{
	public:
		BackgroundDummyTask() : Task(BACKGROUND_REPEATING) {}
		virtual ~BackgroundDummyTask() {}
		virtual void run() {}
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

		void handle(const StopEvent&);
		void handle(const Task::TaskCompleted& tc);

	private:
		void worker();
		void execute(TaskPtr task);
		void synchronize();

		std::vector<std::thread> mThreads;
		unsigned int mNumThreads;

		mutable bool mRunning;
		//EventChannel mChan;

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