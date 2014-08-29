#include "stdafx.h"
#include "LogThread.h"


#include <iostream>
#include <ctime>
#include <iomanip>

namespace fk 

{
	std::function<void(LogLevel level, std::string)> Log::Message = [](LogLevel level, std::string s){ throw std::exception("Function Not Initialized"); };
	std::function<void(std::string)> Log::Verbose = [](std::string s){ throw std::exception("Function Not Initialized"); };
	std::function<void(std::string)> Log::Debug = [](std::string s){ throw std::exception("Function Not Initialized"); };
	std::function<void(std::string)> Log::Warning = [](std::string s){ throw std::exception("Function Not Initialized"); };
	std::function<void(std::string)> Log::Error = [](std::string s){ throw std::exception("Function Not Initialized"); };

	LogThread::LogThread() 
	{
		std::lock_guard<std::mutex> guard(queuemutex_);
		frontqueue_ = std::make_unique<std::deque<std::string>>();
		backqueue_ = std::make_unique<std::deque<std::string>>();

		levelstrings_.emplace(LogLevel::Verbose, "Verbose");
		levelstrings_.emplace(LogLevel::Debug, "Debug");
		levelstrings_.emplace(LogLevel::Warning, "Warning");
		levelstrings_.emplace(LogLevel::Error, "Error");

		Log::Message	= std::bind(&LogThread::LogMessage, this, std::placeholders::_1, std::placeholders::_2);
		Log::Verbose	= std::bind(&LogThread::LogMessage, this, LogLevel::Verbose, std::placeholders::_1);
		Log::Debug		= std::bind(&LogThread::LogMessage, this, LogLevel::Debug, std::placeholders::_1);
		Log::Warning	= std::bind(&LogThread::LogMessage, this, LogLevel::Warning, std::placeholders::_1);
		Log::Error		= std::bind(&LogThread::LogMessage, this, LogLevel::Error, std::placeholders::_1);
	}

	LogThread::~LogThread()
	{
		frontqueue_ = nullptr;
		backqueue_ = nullptr;
	}

	void LogThread::LogMessage(LogLevel level, std::string message) 
	{
		if (level < level_) return;
		std::lock_guard<std::mutex> guard(queuemutex_);
		frontqueue_->emplace_back(std::move(message));
	}

	void LogThread::Initialize() {

	}

	void LogThread::LoopIteration() 
	{
		std::time_t time = std::time(nullptr);
		std::tm tm;
		localtime_s(&tm, &time);
		auto tObj = std::put_time(&tm, "%H:%M:%S");
		for (auto iter = backqueue_->begin(); iter != backqueue_->end(); ++iter) {
			if (show_time_stamp_) std::cout << "[" << tObj << "]";
			if (show_log_level_) std::cout << "[" << levelstrings_[level_] << "]";
			std::cout << *iter << std::endl;
		}
		backqueue_->clear();
		std::lock_guard<std::mutex> guard(queuemutex_);
		std::swap(frontqueue_, backqueue_);
	}

	void LogThread::Terminate() 
	{

	}
}



