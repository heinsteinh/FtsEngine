#include "stdafx.h"
#include "thread_pool.h"



namespace P9927 {

	ThreadPool::ThreadPool() : done_(false) {
		unsigned numThreads = std::thread::hardware_concurrency();
		try {
			for (unsigned i = 0; i < numThreads; ++i)
				worker_threads_.push_back(std::thread(&ThreadPool::work, this));
		}
		catch (...) {
			done_ = true;
			throw;
		}
	}

	ThreadPool::~ThreadPool() {
		done_ = true;
		for (auto& thread : worker_threads_) {
			thread.join();
		}
	}

	//==========================
	// work
	//==========================
	void ThreadPool::work() {
		while (!done_) {
			std::function<void()> task;
			task = queue_.wait_pop();

			if (task)
			{
				task();
			}
			
		}
	}

} // namespace P9927