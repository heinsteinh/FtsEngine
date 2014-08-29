#pragma once


///////////////////////////////////////////////////////////////////////////////
// $Id$

#ifndef INCLUDED_SCHEDULER_H
#define INCLUDED_SCHEDULER_H


#include <queue>
#include <deque>
#include <memory>



#ifdef _MSC_VER
#pragma once
#endif


#include "SchedulerClock.h"

///////////////////////////////////////////////////////////////////////////////
//
// STRUCT: sTaskInfo
//


class IUnknown
{
};


class ITask : public IUnknown
{
public:
	virtual bool Execute(double time) = 0;
};

struct sTaskInfo
{
	sTaskInfo();
	sTaskInfo(const sTaskInfo & other);
	~sTaskInfo();

	const sTaskInfo & operator =(const sTaskInfo & other);

	std::shared_ptr<ITask> pTask;

	double start;
	double period;
	double expiration;
	double next;
};

struct sTaskInfoCompare
{
	bool operator()(const sTaskInfo * pTask1, const sTaskInfo * pTask2) const
	{
		// Returning true puts the first argument toward the back of the
		// priority queue. Use a greater than test so that tasks with sooner
		// next run times are sorted toward the front of the priority queue.
		return pTask1->next > pTask2->next;
	}
};

typedef std::priority_queue<sTaskInfo *, std::deque<sTaskInfo *>, sTaskInfoCompare> tTaskQueue;

///////////////////////////////////////////////////////////////////////////////
//
// CLASS: cScheduler
//
//https://github.com/dpalma/sge/blob/98357c91eb77d6effe50dd11e926fb637f68a295/api/tech/schedulerapi.h

class cScheduler 
{
public:
	cScheduler();
	~cScheduler();
	

	virtual bool Init();
	virtual void Term();

	virtual void Start();
	virtual void Stop();
	virtual bool IsRunning() const;

	virtual void NextFrame();


	
	
	/// @brief Registers a task to run on every call to IScheduler::NextFrame
	/// @param pTask specifies the task to run every frame
	/// @return S_OK if successful, or an E_xxx error code
	typedef std::shared_ptr<ITask> TaskPtr;
	virtual bool AddRenderTask(TaskPtr pTask);
	virtual bool RemoveRenderTask(TaskPtr pTask);

	virtual bool AddFrameTask(TaskPtr pTask, ulong start, ulong period, ulong duration);
	virtual bool RemoveFrameTask(TaskPtr pTask);

	virtual bool AddTimeTask(TaskPtr pTask, double start, double period, double duration);
	virtual bool RemoveTimeTask(TaskPtr pTask);


	//static bool AddTask(tTaskQueue * pQueue, std::shared_ptr<ITask> pTask, double start, double period, double duration);
	//static bool RemoveTask(tTaskQueue* pQueue, std::shared_ptr<ITask> pTask);

private:
	cSchedulerClock m_clock;
	tTaskQueue m_frameTaskQueue;
	tTaskQueue m_timeTaskQueue;
	
	std::deque<TaskPtr> m_renderTaskQueue;

	uint m_lockRenderTaskQueue;

};

///////////////////////////////////////////////////////////////////////////////

#endif // INCLUDED_SCHEDULER_H