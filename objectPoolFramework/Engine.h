#pragma once

#ifndef _Engine_H_
#define _Engine_H_


#include "LoggerInterface.h"
#include "TaskManager.h"

#include "TSingleton.h"

#include <cstdint>
#include <condition_variable>

namespace tin{

	const std::string RENDER_THREAD = "RenderThread";
	const std::string MAIN_THREAD = "MainThread";

	enum RendererVersion{
		kOpenGLES20,
		kOpenGL3
	};

	class Timer;
	class Application;
	class LoggerInterface;
	struct EngineOptions{
		std::string basepath;
		std::string datapath;
		void* render_context;
		LoggerInterface *logger_interface;
		int render_version;
		bool use_web_backend;
		bool run_in_background;
		Application*    application;
		int window_width;
		int window_height;
	};

	class Game;
	class Engine : public CSingleton<Engine>
	{
		friend class CSingleton<Engine>;

	public:
		Engine();
		~Engine();
		// Engine API:
		// Engine commands
		void InitWithOptions(EngineOptions options);
		void Shutdown();

		void StartUpdate();
		void PauseUpdate();

		// Renderer commands

		void OnResize(int width, int height);
		void DrawSingleFrame();

		void StopRenderer();
		static uint64_t CurrentFrame();

		Application *application();

		void AddEndOfFrameTask(Task &task);
		void AddStartOfFrameTask(Task &task);

	private:
		unsigned long int frame_count_;
		bool running_;
		bool paused_;
		Timer *update_timer;
		uint64_t frame = 0;

		std::list<Task> start_of_frame_tasks_;
		std::list<Task> end_of_frame_tasks_;

		Application *application_;

		std::thread update_thread_;
		std::mutex update_mutex_;
		std::condition_variable update_cond_var_;

		void Init();
		void Update();
		
		void Loop();
		bool isRunning() { return running_; };

		friend class Singleton;
	};
} // tin
#endif