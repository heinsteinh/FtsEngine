#include "stdafx.h"
#include "taskmanager.h"
#include "log.h"


#include "XFormBuffer.h"
#include "GameObject.h"


namespace core
{

	TaskManager::TaskManager(unsigned int numThreads) :joiner(mThreads)
	{
		mNumThreads = numThreads;
		if (numThreads == 0)
			mNumThreads = std::thread::hardware_concurrency() + 1;

		mWriteList = 0;
		mReadList = 1;

		mNumTasksToWaitFor = 0;
	}

	TaskManager::~TaskManager()
	{		
		joiner.~join_threads();
	}


	void TaskManager::add(TaskPtr task) {
		unsigned flags = task->getTaskFlags();

		if (flags & Task::THREADSAFE) {
			if (flags & Task::FRAME_SYNC)
				mSyncTasks.push(task);
			else
				mBackgroundTasks.push(task);
		}
		else
			mTaskList[mWriteList].push(task);
	}



	void TaskManager::start() 
	{
		mRunning = true;
						
		add(TaskPtr(new BackgroundDummyTask()));
		
		EventChannel chan;
		chan.add<Task::TaskBeginning>(*this);
		chan.add<Task::TaskCompleted>(*this);
		chan.add<StopEvent>(*this);

		for (unsigned int i = 0; i < mNumThreads; ++i)
			mThreads.push_back(std::thread(std::bind(&TaskManager::worker, this)));



		while (mRunning)
		{
			if (!mTaskList[mReadList].empty())
			{
				TaskPtr t = mTaskList[mReadList].wait_pop();
				execute(t);
			}
			else 
			{
			
				//// Read from other buffer
				//if (BubbleBattleBoids::XFormBufferManager::GetInstance().ReadBufferDirty())
				//{
				//	BubbleBattleBoids::XFormBufferManager::GetInstance().SwapReadBuffers();

				//	// Remove dead objects from write data
				//	BubbleBattleBoids::GameObject::CleanUp();
				//}

				synchronize();
				std::swap(mReadList, mWriteList);
			}

			std::this_thread::yield();
		}
	}

	void TaskManager::synchronize()
	{
		ScopedLock lock(mSyncMutex);

		while (mNumTasksToWaitFor > 0)
			mCondition.wait(lock);

		mNumTasksToWaitFor = mSyncTasks.size();

		while (!mSyncTasks.empty())
		{
			TaskPtr t = mSyncTasks.wait_pop();
			mBackgroundTasks.push(t);
		}

	}

	void TaskManager::stop() 
	{
		mRunning = false;
	}

	void TaskManager::execute(TaskPtr t) 
	{
		EventChannel chan;
		chan.broadcast(Task::TaskBeginning(t));
		t->run();
		chan.broadcast(Task::TaskCompleted(t));
	}

	void TaskManager::handle(const TaskManager::StopEvent&) 
	{
		stop();
	}

	void TaskManager::handle(const Task::TaskCompleted& tc) 
	{
		tc.mTask->mTaskState = Task::TASK_COMPLETED;

		if (tc.mTask->getTaskFlags() & Task::REPEATING)
			add(tc.mTask);
	}

	void TaskManager::handle(const Task::TaskBeginning& tb)
	{
		tb.mTask->mTaskState = Task::TASK_STARTED;
	}


	void TaskManager::worker() 
	{
		TaskPtr task;
		bool exec;
		while (mRunning)
		{
	
			exec = mBackgroundTasks.try_pop(task);

			if (exec)
			{
				execute(task);

				if (task->getTaskFlags() & Task::FRAME_SYNC)
				{
					ScopedLock lock(mSyncMutex);
					--mNumTasksToWaitFor;
					lock.unlock();

					mCondition.notify_one();
				}
			}
			std::this_thread::yield();
		}
	}



}