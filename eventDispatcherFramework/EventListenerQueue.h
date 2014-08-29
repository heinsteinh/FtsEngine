#pragma once

#include <vector>

#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "Interfaces.h"





namespace Framework
{
	using namespace module;

	//
	// TODO: Separate a non-modifiable base class to pass to dispatchers
	//

	/// Event listener container
	/** With requirement to deliver messages only to the objects who
	* exist at the time of the call in multi threaded environment, this
	* class uses Copy-on-Write pattern to copy data only when needed
	* @ingroup Framework */


		
	class CEventListenerQueue
	{
	public:
		CEventListenerQueue();

		CEventListenerQueue(const CEventListenerQueue& source);

		~CEventListenerQueue();

		void AddListener(IUnknown* listener);

		void RemoveListener(IUnknown* listener);

		size_t Size() const;

		IUnknown** getListeners() const;

	private:
		void PreModify();

	private:
		typedef std::vector<IUnknown*> TListenerQueue;
		typedef std::shared_ptr<TListenerQueue> TSharedQueue;

		TSharedQueue m_queue;

		mutable std::mutex m_lock;
		typedef std::unique_lock<std::mutex> scoped_lock;
	
	};

} // namespace