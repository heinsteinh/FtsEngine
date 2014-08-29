// SchedulerTask.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "SchedulerClock.h"
#include "Scheduler.h"


#include <cassert>




namespace testschelduler
{

	class cCounterTask : public ITask
	{
	public:
		cCounterTask() : m_count(0) {}

		virtual bool Execute(double time)
		{
			++m_count;
			return true;
		}

		int GetCount() const { return m_count; }

	private:
		int m_count;
	};

	enum eSchedulerTaskType
	{
		kRenderTask, kFrameTask, kTimeTask
	};


	class cRemoveSelfTask : public ITask
	{
	public:
		cRemoveSelfTask(cScheduler* pScheduler, eSchedulerTaskType taskType) : m_pScheduler(pScheduler), m_taskType(taskType) {}

		virtual bool Execute(double time)
		{
			if (m_taskType == kRenderTask)
			{
				m_pScheduler->RemoveRenderTask(std::shared_ptr<ITask>(this));
			}
			else if (m_taskType == kFrameTask)
			{
				m_pScheduler->RemoveFrameTask(std::shared_ptr<ITask>(this));
			}
			else if (m_taskType == kTimeTask)
			{
				m_pScheduler->RemoveTimeTask(std::shared_ptr<ITask>(this));
			}
			return true;
		}

	private:
		cScheduler* m_pScheduler;
		eSchedulerTaskType m_taskType;
	};


	class cSchedulerTests
	{
	public:
		cSchedulerTests();
		~cSchedulerTests();

		cScheduler * AccessScheduler() { return static_cast<cScheduler*>(m_pScheduler.get()); }
		const cScheduler * AccessScheduler() const { return static_cast<const cScheduler*>(m_pScheduler.get()); }

	private:
		std::shared_ptr<cScheduler> m_pScheduler;
	};

	cSchedulerTests::cSchedulerTests()
	{
		m_pScheduler.reset();
		m_pScheduler = std::shared_ptr<cScheduler>(new cScheduler);
		m_pScheduler->Init();
	}

	cSchedulerTests::~cSchedulerTests()
	{
		if (!!m_pScheduler)
		{
			m_pScheduler->Term();
			(m_pScheduler.reset());
		}
	}



	class  SchedulerFrameTaskExpiration 
	{
	
	public:
		cSchedulerTests pSchedulerTests;

		SchedulerFrameTaskExpiration::SchedulerFrameTaskExpiration()
		{		
		}

		static const ulong kFrameTaskPeriod = 2;
		static const ulong kFrameTaskDuration = 6;
		static const ulong kMinFrames = static_cast<ulong>(kFrameTaskDuration / kFrameTaskPeriod);


		void Run()
		{
			std::shared_ptr<cCounterTask> pFrameTask(new cCounterTask);
			
			
			assert(pSchedulerTests.AccessScheduler()->AddFrameTask(pFrameTask, 0, kFrameTaskPeriod, kFrameTaskDuration) ==true);

			// run the scheduler for at least as many frames as it takes to expire the task
			pSchedulerTests.AccessScheduler()->Start();

			for (ulong nFrames = 0; nFrames < (kMinFrames + 2); ++nFrames)
			{
				pSchedulerTests.AccessScheduler()->NextFrame();
			}
			pSchedulerTests.AccessScheduler()->Stop();

			assert(static_cast<int>(kFrameTaskDuration / kFrameTaskPeriod) == pFrameTask->GetCount());
		}
	};


	class  SchedulerRemoveTaskDuringFrame
	{

	public:
		cSchedulerTests pSchedulerTests;

		SchedulerRemoveTaskDuringFrame::SchedulerRemoveTaskDuringFrame()
		{
		}

		void Run()
		{
			std::shared_ptr<ITask> pFrameTask(new cRemoveSelfTask(pSchedulerTests.AccessScheduler(), kFrameTask));
			std::shared_ptr<ITask> pRenderTask(new cRemoveSelfTask(pSchedulerTests.AccessScheduler(), kRenderTask));

			assert(pSchedulerTests.AccessScheduler()->AddFrameTask(pFrameTask, 0, 1, 1) == true);
			assert(pSchedulerTests.AccessScheduler()->AddRenderTask(pRenderTask) == true);

			pSchedulerTests.AccessScheduler()->Start();
			pSchedulerTests.AccessScheduler()->NextFrame();
			pSchedulerTests.AccessScheduler()->Stop();
		}
	};

}

int _tmain(int argc, _TCHAR* argv[])
{


	testschelduler::SchedulerFrameTaskExpiration schedulerFrameTaskExpiration;
	schedulerFrameTaskExpiration.Run();

	/*testschelduler::SchedulerRemoveTaskDuringFrame schedulerRemoveTaskDuringFrame;
	schedulerRemoveTaskDuringFrame.Ru*/;


	return 0;
}

