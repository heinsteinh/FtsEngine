#ifndef INCLUDED_THREAD_HPP
#define INCLUDED_THREAD_HPP

#include <thread>
#include <mutex>
#include <condition_variable>


#include <chrono>
#include <thread>

namespace fk 
{
	class Thread {
	public:
		Thread();
		virtual ~Thread();
		void NotifyStart();
		void StartOnThisThread();
		void NotifyStop();
		void WaitForStop();
	protected:
		virtual void Initialize() = 0;
		virtual void LoopIteration() = 0;
		virtual void Terminate() = 0;
	private:
		void Loop();
		std::thread thread_;
		bool loop_ = true;
		bool stopped_ = true;
		std::mutex stoppedmutex_;
		std::condition_variable stoppedcondition_;
	};
}

#endif