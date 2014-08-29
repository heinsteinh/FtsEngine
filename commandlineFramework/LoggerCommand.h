#pragma once
#include "console_command.h"

namespace wmdf
{
	class LoggerCommand :public ConsoleCommand
	{
	public:
		LoggerCommand(std::string command_tag, std::string alias);
		virtual ~LoggerCommand(void);
		virtual void Execute(const std::string& command_line);
		virtual void OnHelp();
	};
}