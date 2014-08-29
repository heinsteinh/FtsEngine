
#ifndef CORE_CONTROLLER_H_
#define CORE_CONTROLLER_H_

#include <memory>
#include <thread>

//https://github.com/marcgreen/p2pbackup/blob/c87b5141a090df7e71d215c80ed87edcb6e27c20/src/core/Controller.h

namespace core {

	class Dispatcher;

	class Controller {
	public:
		Controller(std::shared_ptr<Dispatcher> dispatcher);
		
		virtual ~Controller();
		virtual void start() = 0;
		std::shared_ptr<std::thread> startInBackground();
		virtual void stop() = 0;
	protected:
		std::shared_ptr<Dispatcher> dispatcher_;
	}; // class Controller

} // namespace core

#endif // CORE_CONTROLLER_H_