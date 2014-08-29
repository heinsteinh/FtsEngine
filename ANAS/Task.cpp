#include "stdafx.h"
#include "Task.h"



namespace core
{

	Task::Task(unsigned int flags) :mTaskFlags(flags), mTaskState(taskState::TASK_CREATED)
	{
	}

	Task::~Task()
	{
	}

	unsigned int Task::getTaskFlags() const
	{
		return mTaskFlags;
	}

	Task::TaskBeginning::TaskBeginning(Task::TaskPtr t) :mTask(t)
	{
		mTask->mTaskState = taskState::TASK_STARTED;
	}

	Task::TaskCompleted::TaskCompleted(Task::TaskPtr t) : mTask(t)
	{
		mTask->mTaskState = taskState::TASK_COMPLETED;
	}
}