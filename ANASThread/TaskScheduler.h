#pragma once

#include <queue>
#include <vector>
#include <iostream>

#include <memory>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>


#include "debug.h"


using std::queue;
using std::vector;
using std::shared_ptr;



namespace ANAS
{


	class Task
	{
	public:

		Task(){}
		virtual ~Task() throw() {}

		virtual void Run() = 0;
	};

	class AnyTasking : public Task
	{
	public:
		typedef std::function<void()> Holder;

		AnyTasking(std::function<void()> function)
		{
			any_task_holder = function;
		}



		inline void Run()
		{
			any_task_holder();
		}


	private:
		Holder any_task_holder;


	};



	template<typename Fn, typename Arg >
	class GenericTasking : public Task
	{
	public:
		GenericTasking(Fn fn, Arg* arg)
			: fn(fn)
			, arg(arg)
		{
		}

		inline void Run()
		{
			fn(arg);
		}

	private:
		Fn fn;
		Arg* arg;
	};

	//https://github.com/projectsf/snippets/blob/f85f287a8b63d2e3ef5ddd861c01d60cc4f96cc4/cpp/examples/genericExamples/functionObjectsExamples/memFunAdapterExample.cpp


	//submit(new TaskPool::GenericTasking<std::mem_fun_t<void, TestThread::logger_mgnt>, TestThread::logger_mgnt>
	//(std::mem_fun(&TestThread::logger_mgnt::TermTask), this));

	//Usage
	class Foo
	{
	public:
		Foo() : runnable(std::mem_fun(&Foo::doSomething), this)
		{
		}

		void doSomething()
		{
			int iTest = 0;
			//cout << "Foo's doing something" << endl;
		}

		void operator()()
		{
			runnable.Run();
		}
	private:
		GenericTasking<std::mem_fun_t<void, Foo>, Foo> runnable;
	};

	//Foo foo;
	//foo();





	class join_threads
	{
		std::vector<std::thread>& threads;
	public:
		explicit join_threads(std::vector<std::thread>& threads_) :threads(threads_)
		{}
		~join_threads()
		{
			for (unsigned long i = 0; i<threads.size(); ++i)
			{
				if (threads[i].joinable())
					threads[i].join();
			}
		}
	};

	template<typename T>
	class thread_safe_queue
	{
	private:
		mutable std::mutex mut;
		std::queue<T> data_queue;
		std::condition_variable data_cond;
	public:
		thread_safe_queue(){}
		thread_safe_queue(thread_safe_queue const& other)
		{
			std::lock_guard<std::mutex> lk(other.mut);
			data_queue = other.data_queue;
		}
		void push(T new_value)
		{
			std::lock_guard<std::mutex> lk(mut);
			data_queue.push(new_value);
			data_cond.notify_one();
		}
		void wait_and_pop(T& value)
		{
			std::unique_lock<std::mutex> lk(mut);
			data_cond.wait(lk, [this]{return !data_queue.empty(); });
			//data_cond.wait(lk);
			value = data_queue.front();
			data_queue.pop();
		}
		std::shared_ptr<T> wait_and_pop()
		{
			std::unique_lock<std::mutex> lk(mut);
			data_cond.wait(lk, [this]{return !data_queue.empty(); });
			//data_cond.wait(lk);
			std::shared_ptr<T> res(new T(data_queue.front()));
			data_queue.pop();
			return res;
		}

		bool try_pop(T& value)
		{
			std::lock_guard<std::mutex> lk(mut);
			if (data_queue.empty())
				return false;
			value = data_queue.front();
			data_queue.pop();

			return true;
		}
		std::shared_ptr<T> try_pop()
		{
			std::lock_guard<std::mutex> lk(mut);
			if (data_queue.empty())
				return std::shared_ptr<T>();
			std::shared_ptr<T> res(new T(data_queue.front()));
			data_queue.pop();
			return res;
		}
		bool empty() const
		{
			std::lock_guard<std::mutex> lk(mut);
			return data_queue.empty();
		}
	};


	class  TaskScheduler //thread_pool
	{

	protected:
		std::atomic<bool> done;
		thread_safe_queue<Task*> work_queue;

		std::vector<std::thread> threads;
		join_threads joiner;

		void worker_thread()
		{
			while (!done)
			{


				Task* task = NULL;
				if (work_queue.try_pop(task))
				{

					task->Run();

					if (task != NULL)
						delete task;

					task = NULL;
				}
				else
				{
					std::this_thread::yield();
				}

			}
		}


	public:
		TaskScheduler() : joiner(threads), done(false)
		{
			unsigned const thread_count=std::thread::hardware_concurrency();
			try
			{
				for (unsigned i = 0; i<thread_count; ++i)
				{
					threads.push_back(std::thread(&TaskScheduler::worker_thread, this));
				}
			}
			catch (std::bad_alloc)
			{
				done = true;
				throw;
			}
		}
		~TaskScheduler()
		{
			done = true;
		}


		bool GetDone()
		{
			return done.load(std::memory_order_acquire);
		}


		//https://github.com/ouonline/threadpool/blob/0c208abe1d26f527aebd4c8595fc6c92537581b4/cpp/mythreadpool.hpp
		//const shared_ptr<MyThreadTask>& t
		void submit(Task* task)
		{
			//make_shared<Task>(task));
			work_queue.push(task);
		}
	};

}