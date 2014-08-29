#pragma once
#ifndef _TaskManager_H_
#define _TaskManager_H_

#include <functional>
#include <string>
#include <unordered_map>
#include <map>
#include <list>
#include <thread>
#include <iostream>

#include "TSingleton.h"

namespace tin{
	typedef int64_t TaskId;
	typedef std::function<void(void)> TaskFunction;
	class WorkItem{
	public:
		WorkItem(TaskId task_id) : function_set_(false), task_id_(task_id) { };
		void SetFunction(TaskFunction function);
		void Execute();

		const TaskId task_id() { return task_id_; };
	private:
		std::function<void(void)> function_;
		bool function_set_;
		TaskId task_id_;
	};

	class Task{
	public:
		template<typename Func, typename FObj, typename ...Args>
		Task(Func &&func, FObj &&fobj, Args... args){
			task_id_ = GetNextTaskId();
			function_ = std::bind(func, fobj, std::forward<Args>(args)...);
			work_count_ = 1;
			parent_task_id_ = 0;
			dependency_task_id_ = 0;
			running_ = false;
			function_set_ = true;
			affinity_set_ = false;
		}

		static Task EmptyTask(){
			Task task;
			task.task_id_ = GetNextTaskId();
			task.work_count_ = 1;
			task.parent_task_id_ = 0;
			task.dependency_task_id_ = 0;
			task.running_ = false;
			task.function_set_ = false;
			task.affinity_set_ = false;
			return task;
		}

		Task() {};

		const TaskId task_id() { return task_id_; };
		const TaskId parent_task_id() { return parent_task_id_; };
		const TaskId dependency_task_id() { return dependency_task_id_; };
		const TaskFunction task_function() { return function_; };
		const std::string profiler_name(){ return profiler_name_; };
		const std::string thread_affinity() { return thread_affinity_; };
		void dependency_task_id(TaskId task_id) { dependency_task_id_ = task_id; };
		const int work_count() { return work_count_; };
		const bool running() { return running_; };
		const bool affinity_set() { return affinity_set_; };
		const bool function_set() { return function_set_; };
		void Execute();
		void thread_affinity(std::string name);

	private:
		friend class TaskManager;

		bool function_set_;
		bool running_;
		bool affinity_set_;
		TaskId task_id_;
		TaskFunction function_;
		int32_t work_count_;
		TaskId parent_task_id_;
		TaskId dependency_task_id_;
		std::string profiler_name_;
		std::string thread_affinity_;

		void parent_task_id(TaskId task_id) { parent_task_id_ = task_id; };
		void running(bool running) { running_ = running; };

		static TaskId GetNextTaskId();
		void AdjustWorkCount(int amount);
	};

	typedef enum{
		THREAD_TYPE_REGULAR = 0,
		THREAD_TYPE_REGISTERED
	} ThreadType;

	typedef enum{
		THREAD_STATUS_WAITING = 0,
		THREAD_STATUS_RUNNING
	} ThreadStatus;

	class WorkerThread{
	public:
		WorkerThread(ThreadType type, std::string name);
		~WorkerThread();

		static void Notify();
		ThreadStatus status(){ return status_; };
		const TaskId wait_task_id(){ return wait_task_id_; };
		void BeginWait(TaskId wait_task_id);
		void EndWait();
		TaskId CurrentTaskId();
		std::string name() { return name_; };
		std::thread::id GetId();
	private:
		void AddWorkItem(WorkItem &work_item);
		void ExecuteTasksLoop();
		void ExecuteTasksWaitLoop();
		void ExecuteTask();
		TaskId current_task_id_;
		bool running_;
		std::thread thread_;
		std::string name_;
		std::list<WorkItem> work_items_;
		ThreadStatus status_;
		TaskId wait_task_id_;
		ThreadType type_;
		std::thread::id thread_id_;

		friend class TaskManager;
	};

	class TaskManager : public CSingleton<TaskManager>
	{
		friend class  CSingleton<TaskManager>;

	public:
		~TaskManager();

		void CreateThreads(int max_count);
		void CreateThread(std::string name);
		void RegisterThread(std::string name);
		void AssignWorkItemToThread(WorkerThread &thread);
		void CompleteTaskWithId(TaskId task_id);

		void AddTask(Task task);
		void AddTaskWithParent(Task task, TaskId parent_id);
		void AddTaskWithDependency(Task task, TaskId dependency_id);

		void AddTaskToThread(Task task, std::string name);
		void AddTaskWithParentToThread(Task task, TaskId parent_id, std::string name);
		void AddTaskWithDependencyToThread(Task task, TaskId dependency_id, std::string name);

		void BeginAddTask(Task task);
		void BeginAddTaskWithParent(Task task, TaskId parent_id);
		void BeginAddTaskWithDependency(Task task, TaskId dependency_id);

		void BeginAddTaskToThread(Task task, std::string name);
		void BeginAddTaskWithParentToThread(Task task, TaskId parent_id, std::string name);
		void BeginAddTaskWithDependencyToThread(Task task, TaskId dependency_id, std::string name);

		void EndAddTask(TaskId task_id);

		const bool TasksAvailable() { return tasks_.size() > 0; };
		void WaitForTask(TaskId task_id);

		const bool TaskExists(TaskId task_id);
		const int NumberOfTasks() { return (int)tasks_.size(); };

		TaskId TaskIdForCurrentThread();

		void RemoveThreads();
	private:
		std::map<TaskId, Task> tasks_;
		std::map<std::string, WorkerThread *> thread_map_;
		std::map<std::thread::id, WorkerThread *> thread_id_map_;

		void Init();
		void Shutdown();

		bool SetThreadAffinityForTask(std::string thread_name, Task &task);

		
	};
} // tin
#endif