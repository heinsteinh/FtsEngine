#include "stdafx.h"
#include "Scheduler.h"
#include <cassert>

///////////////////////////////////////////////////////////////////////////////

static const double kNoExpiration = 0;


///////////////////////////////////////////////////////////////////////////////
//
// STRUCT: sTaskInfo
//

////////////////////////////////////////

sTaskInfo::sTaskInfo()
: pTask(NULL)
, start(0)
, period(0)
, expiration(0)
, next(0)
{
}

////////////////////////////////////////

sTaskInfo::sTaskInfo(const sTaskInfo & other)
: pTask(other.pTask)
, start(other.start)
, period(other.period)
, expiration(other.expiration)
, next(other.next)
{
}

////////////////////////////////////////

sTaskInfo::~sTaskInfo()
{
}

////////////////////////////////////////

const sTaskInfo & sTaskInfo::operator =(const sTaskInfo & other)
{
	pTask = other.pTask;
	start = other.start;
	period = other.period;
	expiration = other.expiration;
	next = other.next;
	return *this;
}


///////////////////////////////////////////////////////////////////////////////
//
// CLASS: cScheduler
//

////////////////////////////////////////

cScheduler::cScheduler()
: m_lockRenderTaskQueue(0)
{
}

////////////////////////////////////////

cScheduler::~cScheduler()
{
}

////////////////////////////////////////

bool cScheduler::Init()
{
	return true;
}

////////////////////////////////////////

void cScheduler::Term()
{
	{
		for (std::deque<TaskPtr>::iterator it = m_renderTaskQueue.begin(); it != m_renderTaskQueue.end(); it++)
		{
			(*it).reset();
		}
		m_renderTaskQueue.clear();

		/*for_each(m_renderTaskQueue.begin(), m_renderTaskQueue.end(), (TaskPtr::reset));				
		m_renderTaskQueue.clear();*/
	}

	while (!m_frameTaskQueue.empty())
	{
		sTaskInfo * pTaskInfo = m_frameTaskQueue.top();
		m_frameTaskQueue.pop();
		delete pTaskInfo;
	}

	while (!m_timeTaskQueue.empty())
	{
		sTaskInfo * pTaskInfo = m_timeTaskQueue.top();
		m_timeTaskQueue.pop();
		delete pTaskInfo;
	}	
}

////////////////////////////////////////

void cScheduler::Start()
{
	m_clock.Start();
}

////////////////////////////////////////

void cScheduler::Stop()
{
	m_clock.Stop();
}

////////////////////////////////////////

bool cScheduler::IsRunning() const
{
	return m_clock.IsRunning();
}

////////////////////////////////////////

bool cScheduler::AddRenderTask(TaskPtr pTask)
{
	if (pTask == NULL)
	{
		return false;
	}

	if (m_lockRenderTaskQueue != 0)
	{
		return false;
	}

	printf("Adding render task %p\n", pTask);

	m_renderTaskQueue.push_back(std::ref(pTask));
	return true;
}

////////////////////////////////////////

bool cScheduler::RemoveRenderTask(TaskPtr pTask)
{
	if (pTask == NULL)
	{
		return false;
	}

	if (m_lockRenderTaskQueue != 0)
	{
		return false;
	}

	std::deque<TaskPtr>::iterator iter = m_renderTaskQueue.begin(), end = m_renderTaskQueue.end();

	for (; iter != end; ++iter)
	{
		if ((pTask == *iter))
		{
			(*iter).reset();

			m_renderTaskQueue.erase(iter);
			return true;
		}
	}

	return false;
}






////////////////////////////////////////

static bool AddTask(tTaskQueue * pQueue, std::shared_ptr<ITask> pTask, double start, double period, double duration)
{
	assert(pQueue != NULL);

	if (period == 0)
	{
		return false;
	}

	if (pTask == NULL)
	{
		return false;
	}

	sTaskInfo * pTaskInfo = new sTaskInfo;
	if (pTaskInfo == NULL)
	{
		return false;
	}

	pTaskInfo->pTask = (pTask);
	pTaskInfo->start = start;
	pTaskInfo->period = period;
	if (duration == 0)
	{
		pTaskInfo->expiration = kNoExpiration;
	}
	else
	{
		pTaskInfo->expiration = start + duration - 1;
	}
	pTaskInfo->next = start;

	pQueue->push(pTaskInfo);
	return true;
}

static bool RemoveTask(tTaskQueue* pQueue, std::shared_ptr<ITask> pTask)
{
	if (pTask == NULL || pQueue == NULL)
	{
		return false;
	}

	bool bFound = false;
	tTaskQueue newQueue;

	while (!pQueue->empty())
	{
		sTaskInfo * pTaskInfo = pQueue->top();
		pQueue->pop();

		if ((pTask == pTaskInfo->pTask))
		{
			delete pTaskInfo;
			bFound = true;
		}
		else
		{
			newQueue.push(pTaskInfo);
		}
	}

	while (!newQueue.empty())
	{
		sTaskInfo * pTaskInfo = newQueue.top();
		newQueue.pop();

		pQueue->push(pTaskInfo);
	}

	return bFound ? true : false;
}

////////////////////////////////////////

bool cScheduler::AddFrameTask(TaskPtr pTask, ulong start, ulong period, ulong duration)
{
	printf("Adding frame-based task %p\n", pTask);
	return AddTask(&m_frameTaskQueue, pTask, static_cast<double>(start), static_cast<double>(period), static_cast<double>(duration));
}

////////////////////////////////////////

bool cScheduler::RemoveFrameTask(TaskPtr pTask)
{
	printf("Removing frame-based task %p\n", pTask);
	return RemoveTask(&m_frameTaskQueue, pTask);
}

////////////////////////////////////////

bool cScheduler::AddTimeTask(TaskPtr pTask, double start, double period, double duration)
{
	printf("Adding time-based task %p\n", pTask);
	return AddTask(&m_timeTaskQueue, pTask, start, period, duration);
}

////////////////////////////////////////

bool cScheduler::RemoveTimeTask(TaskPtr pTask)
{
	printf("Removing time-based task %p\n", pTask);
	return RemoveTask(&m_timeTaskQueue, pTask);
}

////////////////////////////////////////

void cScheduler::NextFrame()
{
	m_clock.BeginFrame();

	printf("Frame %d, Time %f: %d time tasks, %d frame tasks, %d render tasks\n",
		m_clock.GetFrameCount(), m_clock.GetFrameStart(),
		m_timeTaskQueue.size(), m_frameTaskQueue.size(), m_renderTaskQueue.size());

	// Run time-based tasks
	while (!m_timeTaskQueue.empty())
	{
		sTaskInfo * pTaskInfo = m_timeTaskQueue.top();
		if (pTaskInfo->next <= m_clock.GetFrameEnd())
		{
			m_timeTaskQueue.pop();

			m_clock.AdvanceTo(pTaskInfo->next);

			if (pTaskInfo->pTask->Execute(m_clock.GetSimTime()) != true)
			{
				delete pTaskInfo;
				continue;
			}

			pTaskInfo->next += pTaskInfo->period;

			if (pTaskInfo->expiration == kNoExpiration ||pTaskInfo->expiration >= pTaskInfo->next)
			{
				// Re-insert with updated time
				m_timeTaskQueue.push(pTaskInfo);
			}
			else
			{
				printf("Time task %p expiring at %f\n", pTaskInfo->pTask, pTaskInfo->expiration);
				delete pTaskInfo;
			}
		}
		else
		{
			break;
		}
	}

	m_clock.EndFrame();

	// Run frame tasks
	while (!m_frameTaskQueue.empty())
	{
		sTaskInfo * pTaskInfo = m_frameTaskQueue.top();
		if (pTaskInfo->next <= m_clock.GetFrameCount())
		{
			printf("Running frame task %p: time = %f\n", pTaskInfo->pTask, pTaskInfo->next);

			m_frameTaskQueue.pop();

			if (pTaskInfo->pTask->Execute(m_clock.GetSimTime()) != true)
			{
				delete pTaskInfo;
				continue;
			}

			pTaskInfo->next += pTaskInfo->period;

			if (pTaskInfo->expiration == kNoExpiration || pTaskInfo->expiration >= pTaskInfo->next)
			{
				// Re-insert with updated time
				m_frameTaskQueue.push(pTaskInfo);
			}
			else
			{
				printf("Frame task %p expiring at %f\n", pTaskInfo->pTask, pTaskInfo->expiration);
				delete pTaskInfo;
			}
		}
		else
		{
			break;
		}
	}

	// Run render tasks
	{
		++m_lockRenderTaskQueue;
		std::deque<std::shared_ptr<ITask>>::iterator iter = m_renderTaskQueue.begin(), end = m_renderTaskQueue.end();
		for (; iter != end; ++iter)
		{
			if ((*iter)->Execute(m_clock.GetFrameCount()) != true)
			{
				iter = m_renderTaskQueue.erase(iter);
			}
		}
		--m_lockRenderTaskQueue;
	}
}