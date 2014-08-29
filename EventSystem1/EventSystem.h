#ifndef SAMPLE_EVENT_INCLUDED
#define SAMPLE_EVENT_INCLUDED

#include <cstdint>
#include <functional>
#include <vector>
#include <algorithm>
#include <memory>

#include "Callbacks.h"

namespace sample {

	///
	/// \relates Event
	/// \brief Type which can store the ID of a event's listener.
	/// \details This is the type returned by Event::add, and is an argument
	/// to the Event::remove and Event::has functions.
	///
	/// Warning: these are not unique across events. Currently the ID is identical
	/// to the subscription order of the listeners of a given event.
	///
	typedef uint32_t ListenerID;

	///
	/// \brief A class representing a event which clients may subscribe to.
	/// \details This code implements a basic pub/sub mechanism in C++.
	///
	/// Publishers declare an `Event<Args...>`, which subscribers then may
	/// bind functions (listeners) to. This is similar to a bare-bones
	/// implementation of the observer pattern, and is useful for games
	/// and GUI programs.
	///
	/// Listeners are moderately configurable, and may be configured in
	/// the following ways:
	///
	/// - Each listener may provide an priority (an int16_t) which defaults to 0.
	///   A listener with a higher priority will be called before one with a lower priority.
	///   If two listeners have identical priorities, then they are called in the order
	///   with which they were added.
	/// - A listener may opt to be called only once, in which case it's removed from the
	///   internal list after being called once.
	///
	/// Usage example:
	///
	/// \code{C++}
	/// Event<unsigned, unsigned> resize_hook;
	///
	/// // ...
	///
	/// resize_hook.add([&](unsigned w, unsigned h) {
	///   std::cout << "resized to " << w << " x " << h << std::endl;
	/// });
	///
	/// // ...
	///
	/// resize_hook.add([&](unsigned w, unsigned h) {
	///   glViewport(0, 0, w, h);
	/// }, 32); // priority of 32, this will be called first.
	///
	/// // ...
	///
	/// SDL_Event e;
	/// while (SDL_PollEvent(&e)) {
	///   switch (e.type) {
	///     // ...
	///     case SDL_VIDEORESIZE:
	///       resize_hook(static_cast<unsigned>(e.resize.w),
	///                   static_cast<unsigned>(e.resize.h));
	///     break;
	///     // ...
	///   }
	/// }
	/// \endcode
	///
	/// \tparam Args The type of the arguments taken by the handler functions (which should return void).
	///




	class EventHolder 
	{
		ListenerID holderId;

	}; // or EventListner ID 	
	typedef std::shared_ptr<EventHolder> EventHolderPtr;


	template <class ...Args>
	class Event {
	public:
		/** \brief Type of listener callbacks */
		typedef std::function<void(Args...)> CallbackFunction;		
		callbacks CallbackFunction_;

		

		/** \brief Default constructor. */
		Event() : listeners_(), counter_(0) 
		{
			
		}

		/** \brief Returns the number of active listeners on this event */
		size_t size() const
		{
			return listeners_.size();
		}

		/** \brief Clear all active listeners and reset listener ID's. */
		void clear() 
		{
			listeners_.clear();
			counter_ = 0;
		}

		/** \brief Add a callback to the list, with optional priority and once status. */
		ListenerID add(CallbackFunction fn, int16_t priority = 0, bool once = false);

		/** \brief Remove the listener with id `id` if any exists. */
		void remove(ListenerID id);

		/** \brief Invoke all listeners attached to this event. */
		void operator()(Args &&...args);

		/** \brief Returns true if there is an active listener on this event */
		bool has(ListenerID id) const;


		//ListenerID operator+= (CallbackFunction const& f, int16_t priority, bool once) const;
		void operator -= (ListenerID id);
		

	private:

		/** \brief Per-listener data */
		struct Data 
		{
			//std::weak_ptr<EventHolder> holder;

			ListenerID id;			 /**< Sequential id */
			int16_t priority;		 /**< Call priority (when equal, we defer to the id) */
			bool once;				 /**< Should we remove this listener from our vector after calling? */
		};


		/** \brief Type of the listener data itself. */
		typedef std::pair<CallbackFunction, Data> Listener;

		std::vector<Listener> listeners_;		/**< Vector of active listeners, sorted in call order. */
		ListenerID counter_;					/**< Current ID counter value (id of the next listener). */
	};


	// define these out of line to discourage compilers from inlining them everywhere.

	template <class ...Args>
	ListenerID Event<Args...>::add(CallbackFunction fn, int16_t priority, bool once)
	{

		
		ListenerID id = counter_++;
		listeners_.emplace_back(std::move(fn), Data{ id, priority, once });
		std::sort(listeners_.begin(), listeners_.end(), [](Listener const &lhs, Listener const &rhs) -> bool 
		{
			if (lhs.second.priority != rhs.second.priority) {
				// sort higher priority items first
				return lhs.second.priority > rhs.second.priority;
			}
			// for equal priorities, sort by the order the events were added.
			return lhs.second.id < rhs.second.id;
		});
		return id;
	}

	template <class ...Args>
	bool Event<Args...>::has(ListenerID id) const 
	{
		return std::find_if(listeners_.begin(), listeners_.end(), [id](Listener const &cb) {
			return cb.second.id == id;
		}) != listeners_.end();
	}

	template <class ...Args>
	void Event<Args...>::remove(ListenerID id) 
	{
		listeners_.erase(std::remove_if(listeners_.begin(), listeners_.end(), [id](Listener const &cb) {
			return cb.second.id == id;
		}), listeners_.end());
	}

	template <class ...Args>
	void Event<Args...>::operator()(Args &&...args) 
	{
		// iterate over each callback, erasing it after we call it
		// if it had a once flag set.
		auto i = listeners_.begin();
		while (i != listeners_.end()) 
		{
			i->first(std::forward<Args>(args)...);
			if (i->second.once)
			{
				i = listeners_.erase(i);
			}
			else
			{
				++i;
			}
		}
	}

	
	/*
	template <class ...Args>
	ListenerID Event<Args...>::operator+=(CallbackFunction const& f, int16_t priority, bool once) const
	{
		return add(f, priority, once);
	}*/


	template <class ...Args>
	void Event<Args...>::operator-=(ListenerID handle)
	{
		remove(handle);
	}


}

#endif
