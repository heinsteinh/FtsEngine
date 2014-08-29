#include "stdafx.h"
#include "EventListenerQueue.h"

#include <cassert>


namespace Framework
{
	//////////////////////////////////////////////////////////////////////////

	CEventListenerQueue::CEventListenerQueue()
		: m_queue(new TListenerQueue)
	{
	}

	//////////////////////////////////////////////////////////////////////////

	CEventListenerQueue::CEventListenerQueue(const CEventListenerQueue& source)
	{

		// Protect source queue against simultaneous read/write access
		scoped_lock l(source.m_lock);

		m_queue = source.m_queue;
	}

	//////////////////////////////////////////////////////////////////////////

	CEventListenerQueue::~CEventListenerQueue()
	{

		// Safe - writes on different pointers (even sharing the ref count) are allowed
		m_queue.reset();
	}

	//////////////////////////////////////////////////////////////////////////

	void CEventListenerQueue::AddListener(IUnknown* listener)
	{
		scoped_lock l(m_lock);

		PreModify();

		m_queue->push_back(listener);
	}

	//////////////////////////////////////////////////////////////////////////

	void CEventListenerQueue::RemoveListener(IUnknown* listener)
	{

		scoped_lock l(m_lock);

		PreModify();

		TListenerQueue::iterator it = std::find(m_queue->begin(), m_queue->end(), listener);
		assert(it != m_queue->end());

		if (it != m_queue->end())
		{
			m_queue->erase(it);
		}
	}

	//////////////////////////////////////////////////////////////////////////

	size_t CEventListenerQueue::Size() const
	{
		return m_queue->size();
	}

	//////////////////////////////////////////////////////////////////////////

	module::IUnknown** CEventListenerQueue::getListeners() const
	{
		return Size() != 0 ? &(*m_queue)[0] : 0;
	}

	//////////////////////////////////////////////////////////////////////////

	void CEventListenerQueue::PreModify()
	{
		if (m_queue.unique()) 
			return;

		TListenerQueue* old = m_queue.get();
		m_queue.reset(new TListenerQueue(*old));
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace