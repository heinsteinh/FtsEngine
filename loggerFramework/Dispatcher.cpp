#include "stdafx.h"

#include "Dispatcher.h"
#include "Worker.h"

namespace core {

	Dispatcher::Dispatcher(int numWorkerThreads) :
		numWorkerThreads_(numWorkerThreads),
		stopped_(false) {
		workers_.reserve(numWorkerThreads);
		workerThreads_.reserve(numWorkerThreads);

		if (numWorkerThreads == 0)
			numWorkerThreads = std::thread::hardware_concurrency();

		
		for (int index = 0; index < numWorkerThreads; ++index)
		{
			Worker *next = new Worker(this);
			workers_.push_back(std::shared_ptr<Worker>(next));
			workerThreads_.push_back(std::thread(&Worker::threadMain, next));
		}		
	}


	Dispatcher::~Dispatcher()
	{
		this->stop();
	}

	void Dispatcher::scheduleJob(const Job& job)
	{
		jobQueueMutex_.lock();
		pendingJobs_.push(job);
		jobQueueMutex_.unlock();
		jobNotifier_.notify_one();
	}

	bool Dispatcher::doJob()
	{
		std::unique_lock<std::mutex> jobQueueLock(jobQueueMutex_);
		jobNotifier_.wait(jobQueueLock, [this] {
			return !pendingJobs_.empty() || stopped_;
		});

		if (stopped_ && pendingJobs_.empty())
			return false; // lock is automatically freed

		// Take the next job
		Job takenJob = pendingJobs_.front();
		pendingJobs_.pop();
		jobQueueLock.unlock();

	
		// Run the job
		takenJob.func();
		
		return true; // Success!
	}


	void Dispatcher::stop() 
	{
		jobQueueMutex_.lock();
		stopped_ = true;
		jobQueueMutex_.unlock();
		jobNotifier_.notify_all();

		std::vector<std::thread>::iterator iter;
		for (iter = workerThreads_.begin(); iter != workerThreads_.end(); ++iter) {
			(*iter).join();
		}
	}


	

} // namespace core