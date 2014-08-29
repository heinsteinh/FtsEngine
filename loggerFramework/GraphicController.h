#pragma once
#include "Controller.h"
#include <list>
#include <mutex>
#include <condition_variable>

namespace core
{

	class Task {
	public:

		Task(){}
		virtual ~Task(){}
	
		virtual void Run() = 0;
	};


	typedef std::shared_ptr<Task> TaskPtr;
	class AnyTasking : public Task
	{
	public:
		std::function<void()> holder;

	
		AnyTasking(std::function<void()> function){
			holder = function;
		}

		
		inline void Run(){
			holder();
		}
	};
	

	class Job;
	class GraphicController : public Controller
	{
	public:
		GraphicController(std::shared_ptr<Dispatcher> dispatcher);
		~GraphicController();
		void start();
		void stop();

	private:
		bool shouldStop_;

		std::list<TaskPtr>		TaskList;

		std::mutex				LockMutex;
		bool					isLive;
		bool					isSleep;

		std::mutex				SleepMutex;
		std::condition_variable	SleepCondition;

	};

}

