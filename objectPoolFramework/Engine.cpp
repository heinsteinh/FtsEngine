#include "stdafx.h"
#include "Engine.h"


#include "LoggingSystem.h"
#include "VariableSystem.h"
#include "RenderSystem.h"


namespace tin {

	uint64_t Engine::CurrentFrame(){
		return Engine::GetInstance().frame;
	}

	Engine::Engine(){
	}

	Engine::~Engine(){
	}

	void Engine::Init(){
	}

	void Engine::InitWithOptions(tin::EngineOptions options){
		// Create static instances here

		
		LoggingSystem::GetInstance().AddInterface(options.logger_interface);		
		frame_count_ = 0;

		VariableSystem::GetInstance().Set("r_renderer",  	options.render_version);		
		VariableSystem::GetInstance().Set("fs_basepath",	options.basepath);							
		VariableSystem::GetInstance().Set("r_width",		options.window_width);
		VariableSystem::GetInstance().Set("r_height",		options.window_height);


		/*if (options.use_web_backend){
			ServerSystem::Create();
		}*/

		application_ = options.application;
		if (options.run_in_background){
			running_ = true;
			paused_ = false;
			// TaskManager::SharedInstance()->RegisterThread(RENDER_THREAD);
			update_thread_ = std::thread(&Engine::Loop, this);
		}
		else {
			// TaskManager::SharedInstance()->RegisterThread(RENDER_THREAD);
			// TaskManager::SharedInstance()->CreateThreads(7);
		}
	}


	Application* Engine::application(){
		return application_;
	}

	void Engine::StartUpdate(){
		paused_ = true;
	}

	void Engine::PauseUpdate(){
		paused_ = false;
		update_cond_var_.notify_one();
	}

	void Engine::OnResize(int width, int height){
		VariableSystem::GetInstance().Set("r_width", width);
		VariableSystem::GetInstance().Set("r_height", height);

		Task resize(&RenderSystem::OnResize, RenderSystem::GetInstance(), width, height);
		resize.thread_affinity(RENDER_THREAD);
		end_of_frame_tasks_.push_back(resize);
	}

	void Engine::StopRenderer(){
		Task destroy_frame_buffer(&RenderSystem::StopRenderer, RenderSystem::GetInstance());
		destroy_frame_buffer.thread_affinity(RENDER_THREAD);
		start_of_frame_tasks_.push_back(destroy_frame_buffer);


		Task init_frame_buffer(&RenderSystem::StartRenderer, RenderSystem::GetInstance());
		init_frame_buffer.dependency_task_id(destroy_frame_buffer.task_id());
		init_frame_buffer.thread_affinity(MAIN_THREAD);
		start_of_frame_tasks_.push_back(init_frame_buffer);
	}

	void Engine::DrawSingleFrame(){
		if (!paused_){
			Update();
		}
	}



	void Engine::Shutdown(){
		// Stop the runloop
		running_ = false;
		// Join the thread

		update_thread_.join();

		
		/*CommandSystem::Destroy();
		VariableSystem::Destroy();
		RenderSystem::Destroy();
		
		TaskManager::GetInstance();
		LoggingSystem::Destroy();*/
		
		delete update_timer;
	}

	void Engine::Loop()
	{
		//TaskManager::GetInstance().RegisterThread(RENDER_THREAD);
		TaskManager::GetInstance().CreateThreads(7);
		RenderSystem::GetInstance().Start();

		/*
		if (application_){
			application_->Start();
		}*/

		uint64_t frame = 0;
		while (running_)
		{
			if (paused_){
				std::unique_lock<std::mutex> lock(update_mutex_);
				while (paused_) {
					update_cond_var_.wait(lock);
				}
			}
			frame++;
			// Giving OpenGL Some space
			// And on the fifth frame he started the renderer
			// if (frame == 5){

			// }

			//update_timer->Start();

			// if (frame > 6){
			Update();
			// }

			/*long frame_target_time = (1.0 / 60.0 * 1000);
			std::chrono::milliseconds frame_target_duration(frame_target_time);
			uint64_t max = frame_target_duration.count();

			update_timer->Stop();
			uint64_t elapsed = update_timer->TicksElapsed();
			
			if (elapsed <= max){
				uint64_t rest = frame_target_time - elapsed;
				std::this_thread::sleep_for(std::chrono::milliseconds(rest));
			}*/
		}


		// Rendersystem shutdown
		Task unload_resources(&RenderSystem::RemoveResources, RenderSystem::GetInstance());
		TaskManager::GetInstance().AddTaskToThread(unload_resources, RENDER_THREAD);
		TaskManager::GetInstance().WaitForTask(unload_resources.task_id());
		RenderSystem::GetInstance().Stop();
		TaskManager::GetInstance().RemoveThreads();
	}

	void Engine::AddEndOfFrameTask(Task &task){
		end_of_frame_tasks_.push_back(task);
	}

	void Engine::AddStartOfFrameTask(Task &task){
		start_of_frame_tasks_.push_back(task);
	}

	void Engine::Update()
	{

		TaskManager *task_manager = &TaskManager::GetInstance();

		Task begin_frame_task = Task::EmptyTask();
		task_manager->BeginAddTask(begin_frame_task);
		for (Task task : start_of_frame_tasks_){
			task_manager->AddTaskWithParent(task, begin_frame_task.task_id());
		}
		start_of_frame_tasks_.clear();
		task_manager->EndAddTask(begin_frame_task.task_id());
		task_manager->WaitForTask(begin_frame_task.task_id());

		/*Task input_task = Task(&InputManager::Frame, InputManager::SharedInstance());
		task_manager->AddTask(input_task);*/

		Task command_task = Task(&CommandSystem::Frame, CommandSystem::GetInstance());
		task_manager->AddTask(command_task);

		/*Task run_server_commands(&ServerSystem::Frame, ServerSystem::GetInstance());
		task_manager->AddTaskWithDependency(run_server_commands, command_task.task_id());*/

		/*Task update_render_worlds(&RenderWorldManager::UpdateRenderWorlds, RenderWorldManager::SharedInstance());

		if (application_){
			Task application_update(&Application::Frame, application_);
			task_manager->AddTaskWithDependency(application_update, run_server_commands.task_id());
			task_manager->AddTaskWithDependency(update_render_worlds, application_update.task_id());
		}


		Task render_task = Task(&RenderSystem::DrawFrame, RenderSystem::GetInstance());
		task_manager->AddTaskWithDependencyToThread(render_task, update_render_worlds.task_id(), RENDER_THREAD);
		task_manager->WaitForTask(render_task.task_id());
		*/


		Task eof_task = Task::EmptyTask();
		task_manager->BeginAddTask(eof_task);
		for (Task task : end_of_frame_tasks_){
			task_manager->AddTaskWithParent(task, eof_task.task_id());
		}
		end_of_frame_tasks_.clear();
		task_manager->EndAddTask(eof_task.task_id());
		task_manager->WaitForTask(eof_task.task_id());
		frame++;
	}


}