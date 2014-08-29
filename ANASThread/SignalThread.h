

#pragma once


#include <thread>
#include <future>


namespace ANAS 
{
	
	class Signal
	{
	private:
		std::future<void> SyncFuture;
		std::promise<void> SyncPromise;		//promise used to determine when task is finished

	public:

		
		Signal(){
			SyncFuture = SyncPromise.get_future();
		}

		
		void Notification(){

			SyncPromise.set_value();
		}

		
		void Wait(){

			SyncFuture.get();

		}
	};
}




