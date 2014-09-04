#pragma once


#ifndef _TASK_QUEUE_H__
#define _TASK_QUEUE_H__
#include <set>

#include <thread>
#include <memory>
#include <condition_variable>
#include <map>
#include <atomic>
#include <vector>

#include "Compack.h"



namespace Framework
{


	class NoneCopyable
	{
	protected:
		NoneCopyable(){}
		virtual ~NoneCopyable(){}
	private:
		NoneCopyable(const NoneCopyable &){}
		NoneCopyable &operator=(const NoneCopyable &){	return *this;}
	};


	typedef std::function<void()> TaskCallBack;
	class Task : public  NoneCopyable , public std::enable_shared_from_this<Framework::Task>
	{

		friend class TaskQueue;

	public:
		Task(){}
		virtual ~Task(){}
		virtual void Run() = 0;
		
		typedef std::shared_ptr<Task> Ptr;
	};


	class AnyTasking : public Task
	{
	public:
		TaskCallBack holder;
		AnyTasking(const TaskCallBack& callback){ holder = callback; }
		inline void Run(){ holder(); }
	};


	class TaskQueue
	{

		struct HandlerElm
		{
			int priority;
			const Task* handler;

			HandlerElm(const Task* h, int p) : priority(p), handler(h){}
		};

		struct PriorityGreater
		{
			bool operator()(const HandlerElm&e1, const HandlerElm& e2)const
			{
				return e1.priority > e2.priority;
			}
		};

		typedef std::multiset<HandlerElm, PriorityGreater, std::allocator<HandlerElm> > TaskContainer;
		typedef std::unique_lock<std::mutex>  scoped_lock;

	public:
		TaskQueue();
		virtual ~TaskQueue();
		void Start(int thread_cnt = std::thread::hardware_concurrency() -1);
		
		void Stop();
		void Reset();
		void Pause();
		void Resume();
		void Post(const Task* h, int priority = 0);

	private:
		void ExecLoop();

	private:
		mutable std::mutex start_stop_mutex_;
		mutable std::mutex work_mutex_;

		std::condition_variable	condition_;
		std::atomic<bool> stop_;
		std::atomic<bool> pause_;
		std::atomic<int> runing_threads_count_;

		std::vector<std::thread*> threads_;

		TaskContainer	task_que_;
	};
}
#endif


/*

//https://github.com/bupthongyi/BoostUseCase/blob/3ee1b64ac6a446a272572f832f21eb9a63300032/src/TaskQueue/TaskQueueTest.cpp
TaskQueue tq;

void Print(std::wstring str)
{
printf("%d\t%ws\n", GetCurrentThreadId(), str.c_str());
Sleep(5);
}
void Test()
{
while (true)
{
tq.Post(std::bind(&Print, L"hello world"));
Sleep(1000);
}
}
bool GetCmd()
{
std::wstring s;
std::wcin >> s;
if (s.compare(L"quit") == 0)
{
return false;
}
else if (s.compare(L"start") == 0)
{
tq.Start(10);
}
else if (s.compare(L"stop") == 0)
{
tq.Stop();
}
else if (s.compare(L"pause") == 0)
{
tq.Pause();
}
else if (s.compare(L"resume") == 0)
{
tq.Resume();
}
else if (s.compare(L"reset") == 0)
{
tq.Reset();
}
return true;
}

int _tmain(int argc, _TCHAR* argv[])
{

std::thread* pthread = new std::thread(std::bind(&Test));
std::wcout << L"......\n";
while (true)
{
if (GetCmd() == false)
break;
}
TerminateThread(pthread->native_handle(), 0);

return 0;
}


*/