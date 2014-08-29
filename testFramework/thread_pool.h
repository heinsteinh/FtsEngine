#pragma once



#include <thread>
#include <vector>
#include <atomic>
#include <future>
#include "safe_queue.h"

namespace alm
{

	class join_threads
	{
	public:
		explicit join_threads(std::vector<std::thread> &threads);

		~join_threads();

	private:
		std::vector<std::thread>& m_threads;
	};

	class thread_pool
	{
	public:
		thread_pool(unsigned int thread_count=0); //0 for autodetect

		~thread_pool();

		template<typename FunctionType>
		std::future<void> submit(FunctionType f)
		{
			std::packaged_task<void()> task(std::move(f));
			std::future<void> res(task.get_future());
			m_queue.push(std::move(task));
			return res;
		}

	
	/*	template <typename F, typename A>
		std::future<typename std::result_of<F(A&&)>::type> submit(F &&f, A &&a)
		{
			typedef typename std::result_of<F(A&&)>::type result_type;
			std::packaged_task<result_type(A&&)> task(std::move(f));
			std::future<result_type> res(task.get_future());
			m_queue.push(std::move(task));		

			return res;
		}*/



	private:
		alm::safe_queue<std::packaged_task<void()>> m_queue;

		std::atomic<bool> m_running;

		std::vector<std::thread> m_threads;

		join_threads m_joiner;

		void worker_thread();

		void clear_workers();

		static void clean_task();
	};

}

