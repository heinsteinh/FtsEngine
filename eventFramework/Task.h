#pragma once

#include <memory>


namespace core
{


	class TaskManager;

	class Task {
	public:
		typedef std::shared_ptr<Task> TaskPtr;

		struct TaskBeginning 
		{
			TaskBeginning(TaskPtr t);
			TaskPtr mTask;
		};

		struct TaskCompleted 
		{
			TaskCompleted(TaskPtr t);
			TaskPtr mTask;
		};

		typedef enum task_state  
		{
			////https://github.com/nanayay/budding/blob/250e3d4ee5830e666451396abdf65c1a7da1f326/OGLESSample_NDK/jni/task.h
			TASK_CREATED,
			TASK_WAITING,
			TASK_STARTED,
			TASK_COMPLETED
		}taskState;

		typedef enum task_priority
		{
			PRIORITY_HIGHEST,
			PRIORITY_HIGH,
			PRIORITY_NORMAL,
			PRIORITY_LOW,
			PRIORITY_LOWEST			
		}taskPriority;


		enum {
			NONE = 0x0,

			REPEATING = 0x1 << 0,
			THREADSAFE = 0x1 << 1,
			FRAME_SYNC = 0x1 << 2,

			SINGLETHREADED = NONE,
			SINGLETHREADED_REPEATING = REPEATING,
			BACKGROUND = THREADSAFE,
			BACKGROUND_REPEATING = THREADSAFE | REPEATING,
			BACKGROUND_SYNC = THREADSAFE | FRAME_SYNC,
			BACKGROUND_SYNC_REPEATING = THREADSAFE | REPEATING | FRAME_SYNC,

			ALL = ~0x0
		};

			

		Task(unsigned int flags = SINGLETHREADED_REPEATING);
		virtual ~Task();

		virtual void run() = 0;

	protected:
		friend class TaskManager;

		unsigned int getTaskFlags() const;

	private:
		unsigned int	mTaskFlags;
		taskState		mTaskState;
		taskPriority    mTaskPriority;
	};
}