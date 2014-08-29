#ifndef INCLUDED_USER_THREAD_HPP
#define INCLUDED_USER_THREAD_HPP

#include "ThreadBase.h"

namespace fk {
	class UserThread : public Thread 
	{
	public:
		UserThread();
		virtual ~UserThread();
	private:
		virtual void Initialize() override final;
		virtual void LoopIteration() override final;
		virtual void Terminate() override final;
	};
}

#endif