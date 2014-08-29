#include "stdafx.h"
#include "TaskManager.h"

#include "LoggingSystem.h"


#include <memory>
#include <condition_variable>
#include <thread>
#include <mutex>




#include <sstream>

#define PRINT_DEBUG 1

namespace tin {
#pragma mark - WorkItem

	void WorkItem::Execute(){
		if (function_set_){
			function_();
		}
	}

	void WorkItem::SetFunction(TaskFunction function){
		function_set_ = true;
		function_ = function;
	}

#pragma mark - Task
	static TaskId global_task_id_count = 1;
	static std::mutex task_id_mutex_;

	TaskId Task::GetNextTaskId(){
		std::unique_lock<std::mutex> lock(task_id_mutex_);
		global_task_id_count++;
		return global_task_id_count;
	}

	void Task::Execute(){
		if (function_set_){
			function_();
		}
	}

	void Task::AdjustWorkCount(int amount) {
		work_count_ += amount;
	}

	void Task::thread_affinity(std::string name) {
		affinity_set_ = true;
		thread_affinity_ = name;
	};

#pragma mark - Thread
	std::condition_variable thread_cond_var_;
	std::mutex thread_lock_;

	WorkerThread::~WorkerThread(){
		running_ = false;
		WorkerThread::Notify();
		if (this->type_ == THREAD_TYPE_REGULAR){
			this->thread_.join();
		}
	}

	WorkerThread::WorkerThread(ThreadType type, std::string name)
	{
		if (type == THREAD_TYPE_REGULAR){
			running_ = true;
			thread_ = std::thread(&WorkerThread::ExecuteTasksLoop, this);
		}
		else if (type == THREAD_TYPE_REGISTERED){
			running_ = true;
			thread_id_ = std::this_thread::get_id();
			//thread_ = new Thread(name_);
		}
		type_ = type;
		name_ = name;
		wait_task_id_ = -1;
		status_ = THREAD_STATUS_RUNNING;
	}

	TaskId WorkerThread::CurrentTaskId(){
		return current_task_id_;
	}

	void WorkerThread::ExecuteTask(){
		TaskManager *task_manager = &TaskManager::GetInstance();
		while (!work_items_.empty()){
			WorkItem work_item = work_items_.front();
			work_items_.pop_front();
			current_task_id_ = work_item.task_id();
			work_item.Execute();
			task_manager->CompleteTaskWithId(work_item.task_id());
			current_task_id_ = -1;
		}

		task_manager->AssignWorkItemToThread(*this);
	}

	void WorkerThread::ExecuteTasksWaitLoop(){
		while (status_ == THREAD_STATUS_WAITING && running_){
			TaskManager *task_manager = &TaskManager::GetInstance();
			this->ExecuteTask();
			if (!task_manager->TaskExists(wait_task_id())){
				return;
			}
			std::unique_lock<std::mutex> lock(thread_lock_);
			while (!task_manager->TasksAvailable() && status_ == THREAD_STATUS_WAITING && task_manager->TaskExists(wait_task_id()) && running_){
				//thread_cond_var_.wait(lock);
				thread_cond_var_.wait(lock, [this]{return !work_items_.empty(); });
				
			}
		}
	}

	void WorkerThread::ExecuteTasksLoop(){
		while (running_){
			TaskManager *task_manager = &TaskManager::GetInstance();
			this->ExecuteTask();
			std::unique_lock<std::mutex> lock(thread_lock_);
			while (!task_manager->TasksAvailable() && running_){
				//thread_cond_var_.wait(lock);
				thread_cond_var_.wait(lock, [this]{return !work_items_.empty(); });
				
			}
		}
	}

	void WorkerThread::BeginWait(TaskId wait_task_id){
		wait_task_id_ = wait_task_id;
		status_ = THREAD_STATUS_WAITING;
		ExecuteTasksWaitLoop();
	}


	void WorkerThread::EndWait(){
		std::stringstream ss;
		ss << std::this_thread::get_id();
		LoggingSystem::LogError("End wait: %s\n", ss.str().c_str());
		status_ = THREAD_STATUS_RUNNING;
		wait_task_id_ = -1;
		WorkerThread::Notify();
	}

	void WorkerThread::Notify(){
		thread_cond_var_.notify_all();
	}

	void WorkerThread::AddWorkItem(tin::WorkItem &work_item){
		work_items_.push_back(work_item);
	}

	std::thread::id WorkerThread::GetId(){
		if (this->type_ == THREAD_TYPE_REGISTERED){
			return std::this_thread::get_id();
		}
		return this->thread_.get_id();
	}
#pragma mark - TaskManager
	std::mutex list_lock_;

	void LockList(){
#if PRINT_DEBUG == 1
		std::stringstream ss;
		ss << std::this_thread::get_id();
		LoggingSystem::LogError("Lock: %s\n", ss.str().c_str());
#endif
		list_lock_.lock();
	}

	void UnlockList(){
#if PRINT_DEBUG == 1
		std::stringstream ss;
		ss << std::this_thread::get_id();
		LoggingSystem::LogError("Unlock: %s\n", ss.str().c_str());
#endif
		list_lock_.unlock();
	}
	void TaskManager::Init(){

	}

	void TaskManager::Shutdown(){

	}

	TaskManager::~TaskManager(){

	}

	void TaskManager::RemoveThreads(){
		std::map<std::string, WorkerThread *>::iterator iter;
		for (iter = thread_map_.begin(); iter != thread_map_.end(); iter++){
			WorkerThread *worker_thread = iter->second;
			delete worker_thread;
		}
		thread_map_.clear();
	}

	void TaskManager::CreateThreads(int num_threads){
		int max_thread = std::thread::hardware_concurrency();
		int threads = max_thread - thread_map_.size();
		if (num_threads < threads){
			threads = num_threads;
		}
		for (int i = 0; i < threads; i++){
			std::string name("worker_");
			name += std::to_string(i);
			this->CreateThread(name);
		}
	}

	void TaskManager::CreateThread(std::string name){
		WorkerThread *thread = new WorkerThread(THREAD_TYPE_REGULAR, name);
		thread_map_[name] = thread;
		thread_id_map_[thread->GetId()] = thread;
	}

	void TaskManager::RegisterThread(std::string name){
		WorkerThread *thread = new WorkerThread(THREAD_TYPE_REGISTERED, name);

		thread_map_[name] = thread;
		thread_id_map_[thread->GetId()] = thread;
	}

	void TaskManager::AssignWorkItemToThread(WorkerThread &thread){
		LockList();
		for (auto task_map : tasks_){
			Task task = task_map.second;
			if (task.running()){
				continue;
			}
			if (task.dependency_task_id() != 0){
				if (tasks_.find(task.dependency_task_id()) != tasks_.end()){
					continue;
				}
			}
			if (task.affinity_set() && task.thread_affinity() != thread.name()){
				continue;
			}
			task.running(true);
			tasks_[task.task_id()] = task;
			WorkItem work_item(task.task_id_);
			if (task.function_set()){
				work_item.SetFunction(task.function_);
			}
			thread.AddWorkItem(work_item);

			UnlockList();
			return;
		}
		UnlockList();
	}

	void TaskManager::AddTask(tin::Task task){
		LockList();
		if (tasks_.find(task.task_id()) == tasks_.end()){
			tasks_[task.task_id()] = task;
		}
		UnlockList();
		WorkerThread::Notify();
	}

	void TaskManager::AddTaskWithParent(Task task, TaskId parent_id){
		LockList();

		

		if (tasks_.find(task.task_id()) == tasks_.end()){
			if (tasks_.find(parent_id) != tasks_.end()){
				Task parent_task = tasks_[parent_id];
				parent_task.AdjustWorkCount(1);
				tasks_[parent_id] = parent_task;

				task.parent_task_id(parent_id);
				tasks_[task.task_id()] = task;
			}
			else {
				LoggingSystem::LogError("Parent doesn't exist %d", task.task_id());
				
			}
		}
		else {
			LoggingSystem::LogError("Task exists :%d", task.task_id());
			
		}
		UnlockList();
		WorkerThread::Notify();
	}

	void TaskManager::AddTaskWithDependency(Task task, TaskId dependency_id){
		LockList();
		if (tasks_.find(task.task_id()) == tasks_.end()){
			if (tasks_.find(dependency_id) != tasks_.end()){
				task.dependency_task_id(dependency_id);
			}
			tasks_[task.task_id()] = task;
		}
		else {
			LoggingSystem::LogError("Task already exists in list: %d", task.task_id());
			
			
		}
		UnlockList();
		WorkerThread::Notify();
	}

	void TaskManager::BeginAddTask(tin::Task task){
		task.AdjustWorkCount(1);
		LockList();
		if (tasks_.find(task.task_id()) == tasks_.end()){
			tasks_[task.task_id()] = task;
		}
		UnlockList();
		WorkerThread::Notify();
	}

	void TaskManager::BeginAddTaskWithParent(Task task, TaskId parent_id){
		task.AdjustWorkCount(1);
		this->AddTaskWithParent(task, parent_id);
	}

	void TaskManager::BeginAddTaskWithDependency(Task task, TaskId dependency_id){
		task.AdjustWorkCount(1);
		this->AddTaskWithDependency(task, dependency_id);
	}

	void TaskManager::AddTaskToThread(Task task, std::string name){
		if (SetThreadAffinityForTask(name, task)){
			this->AddTask(task);
		}
	}

	void TaskManager::AddTaskWithParentToThread(Task task, TaskId parent_id, std::string name){
		if (SetThreadAffinityForTask(name, task)){
			this->AddTaskWithParent(task, parent_id);
		}
	}

	void TaskManager::AddTaskWithDependencyToThread(Task task, TaskId dependency_id, std::string name){
		if (SetThreadAffinityForTask(name, task)){
			this->AddTaskWithDependency(task, dependency_id);
		}
	}

	void TaskManager::BeginAddTaskToThread(Task task, std::string name){
		if (SetThreadAffinityForTask(name, task)){
			this->BeginAddTask(task);
		}
	}

	void TaskManager::BeginAddTaskWithParentToThread(Task task, TaskId parent_id, std::string name){
		if (SetThreadAffinityForTask(name, task)){
			this->BeginAddTaskWithParent(task, parent_id);
		}
	}

	void TaskManager::BeginAddTaskWithDependencyToThread(Task task, TaskId dependency_id, std::string name){
		if (SetThreadAffinityForTask(name, task)){
			this->BeginAddTaskWithDependency(task, dependency_id);
		}
	}

	bool TaskManager::SetThreadAffinityForTask(std::string thread_name, Task &task){
		for (auto thread_map : thread_map_){
			WorkerThread *thread = thread_map.second;
			if (thread->name() == thread_name){
				task.thread_affinity(thread_name);
				return true;
			}
		}
		LoggingSystem::LogError("Thread %s not found", thread_name.c_str());
		
		return false;
	}

	void TaskManager::EndAddTask(TaskId task_id){
		// Checks task for completion
		CompleteTaskWithId(task_id);
	}

	void TaskManager::CompleteTaskWithId(TaskId task_id){
		LockList();
		if (tasks_.find(task_id) == tasks_.end()){
			LoggingSystem::LogError("Task with id not found: %d\n", task_id);
		}
		else {
			Task task = tasks_[task_id];
			task.AdjustWorkCount(-1);
			tasks_[task_id] = task;
			if (task.work_count() <= 0){
				tasks_.erase(task_id);

				if (task.parent_task_id() != 0){
					if (tasks_.find(task.parent_task_id()) != tasks_.end()){
						Task parent_task = tasks_[task.parent_task_id()];
						parent_task.AdjustWorkCount(-1);
						tasks_[parent_task.task_id()] = parent_task;
						if (parent_task.work_count() == 0){
							UnlockList();
							this->CompleteTaskWithId(parent_task.task_id());
							LockList();
						}
					}
				}
				for (auto thread_map : thread_map_) {
					WorkerThread *thread = thread_map.second;
					if (thread->wait_task_id() == task_id){
						thread->EndWait();
					}
				}
			}
		}
		UnlockList();
	}

	void TaskManager::WaitForTask(TaskId task_id){
		if (thread_id_map_.find(std::this_thread::get_id()) == thread_id_map_.end()){
			LoggingSystem::LogError("Thread not found");
		}
		else{
			WorkerThread *thread = thread_id_map_[std::this_thread::get_id()];
			thread->BeginWait(task_id);
		}
	}

	const bool TaskManager::TaskExists(TaskId task_id){
		LockList();
		if (tasks_.find(task_id) != tasks_.end()){
			UnlockList();
			return true;
		}
		UnlockList();
		return false;
	}

	TaskId TaskManager::TaskIdForCurrentThread(){
		if (thread_id_map_.find(std::this_thread::get_id()) == thread_id_map_.end()){
			LoggingSystem::LogError("Current thread is available to task manager");
			return -1;
		}
		WorkerThread *thread = thread_id_map_[std::this_thread::get_id()];
		return thread->CurrentTaskId();
	}
}