#ifndef INCLUDED_LOG_THREAD_HPP
#define INCLUDED_LOG_THREAD_HPP

#include <thread>
#include <mutex>
#include <memory>
#include <deque>
#include <string>
#include <map>
#include <iostream>

#include "ThreadBase.h"


//https://github.com/GodwinneLorayne/Bus/tree/e240c4507a7fc721b61b7dea94d436d589e74f21/fluffykitten

namespace fk {
	enum class LogLevel
	{
		Verbose,
		Debug,
		Warning,
		Error
	};

	class LogThread : public Thread {
	public:
		LogThread();
		virtual ~LogThread();

		void LogMessage(LogLevel level, std::string message);

		inline LogLevel log_level() { return level_; }
		inline void set_log_level(LogLevel level) { level_ = level; }
		inline bool show_time_stamp() { return show_time_stamp_; }
		inline void set_show_time_stamp(bool show_time_stamp) { show_time_stamp_ = show_time_stamp; }
		inline bool show_log_level() { return show_log_level_; }
		inline void set_show_log_level(bool show_log_level) { show_log_level_ = show_log_level; }

	private:
		virtual void Initialize() override final;
		virtual void LoopIteration() override final;
		virtual void Terminate() override final;
		std::mutex queuemutex_;
		std::unique_ptr<std::deque<std::string>> frontqueue_;
		std::unique_ptr<std::deque<std::string>> backqueue_;
		std::map<LogLevel, std::string> levelstrings_;
		bool show_time_stamp_ = true;
		bool show_log_level_ = true;
		LogLevel level_ = LogLevel::Debug;
	};

	class Log 
	{
	public:
		static std::function<void(LogLevel, std::string)> Message;
		static std::function<void(std::string)> Verbose;
		static std::function<void(std::string)> Debug;
		static std::function<void(std::string)> Warning;
		static std::function<void(std::string)> Error;
	};
}
#endif