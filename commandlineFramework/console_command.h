#pragma once

#include <string>
#include <list>

//https://github.com/yxdtiger/Test/tree/d6fdf95bfccb4c0fea40d79c14eeca608fa9a6c9/Test/Src/V10/Src/commandline

namespace wmdf
{
	class ConsoleCommandProcessor;


	
	class ConsoleCommand
	{
	public:
		ConsoleCommand(const std::string& command_tag, const std::string& alias);
		virtual ~ConsoleCommand(void);
		virtual void Execute(const std::string& command_line) = 0;
		virtual std::list<std::string>& result_list();
		virtual std::string command_tag();
		virtual std::string alias();
		virtual void OnHelp();
	protected:
		std::string command_tag_;
		std::string alias_;
		std::list<std::string> result_list_;
	};

	
	class NullConsoleCommand : public ConsoleCommand
	{
	public:
		NullConsoleCommand(const std::string& command_tag, const std::string& alias);
		~NullConsoleCommand(void);
	public:
		void Execute(const std::string& command_line);
	};

	class SystemGroupConsoleCommand :public ConsoleCommand
	{
	public:
		SystemGroupConsoleCommand(const std::string& command_tag, const std::string& alias);
		~SystemGroupConsoleCommand(void);
	public:
		void Execute(const std::string& command_line);
	};

	
	class ExitConsoleCommand : public ConsoleCommand
	{
	public:
		ExitConsoleCommand(const std::string& command_tag, const std::string& alias);
		~ExitConsoleCommand(void);
	public:
		void Execute(const std::string& command_line);
	};

	//
	class HelpConsoleCommand : public ConsoleCommand
	{
	public:
		HelpConsoleCommand(const std::string& command_tag, const std::string& alias);
		~HelpConsoleCommand(void);
	public:
		void Execute(const std::string& command_line);
	};

	//
	class ClearScreenConsoleCommand : public ConsoleCommand
	{
	public:
		ClearScreenConsoleCommand(const std::string& command_tag, const std::string& alias);
		~ClearScreenConsoleCommand(void);
		void Execute(const std::string& command_line);
		virtual void OnHelp();
	};

}