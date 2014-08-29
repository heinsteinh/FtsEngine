#ifndef INCLUDED_RENDER_THREAD_HPP
#define INCLUDED_RENDER_THREAD_HPP

#include "ThreadBase.h"

namespace fk {
	class RenderThread : public Thread {
	public:
		RenderThread();
		virtual ~RenderThread();
	private:
		virtual void Initialize() override final;
		virtual void LoopIteration() override final;
		virtual void Terminate() override final;
	};
}

#endif