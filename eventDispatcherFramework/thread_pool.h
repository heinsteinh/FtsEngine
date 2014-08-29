#pragma once



#include <functional>
#include <thread>
#include <future>
#include <atomic>
#include <vector>
#include "concurrent_queue.h"

namespace P9927 {
	/*
	======================================================
	ThreadPool
	======================================================
	*/
	class ThreadPool {
	private:
		ThreadPool(const ThreadPool& other);
		ThreadPool& operator=(const ThreadPool& other);

	public:
		ThreadPool();
		~ThreadPool();

		void work();

		template <typename FunctionType>
		auto submit_job(FunctionType f) -> std::future<decltype(f())> {
			typedef typename std::result_of<FunctionType()>::type result_t;

			auto promise = make_shared<std::promise<result_t>>();
			auto future = promise->get_future();

			queue_.push([=] {
				try {
					auto result = f();
					promise->set_value(result);
				}
				catch (...) {
					promise->set_exception(std::current_exception());
				}
			});

			return future;
		}

	private:
		std::atomic<bool> done_;
		ConcurrentQueue<std::function<void()>> queue_;
		std::vector<std::thread> worker_threads_;
	};

} // namespace P9927


