#pragma once

#include <string>
#include <map>

#include "t_singleton.h"


namespace wmdf
{
	class ConsoleCommand;
	class ConsoleCommandGroup;

	class ConsoleCommandManager : public core::CSingleton<ConsoleCommandManager>
	{
		friend class core::CSingleton<ConsoleCommandManager>;

	public:
		ConsoleCommandManager(void);
		~ConsoleCommandManager(void);
	public:
		
		ConsoleCommand* GetConsoleCommand(std::string group_tag, std::string command_tag);
		void RegisterCommandGroup(ConsoleCommandGroup* command_group, ConsoleCommand* entry_command);
		ConsoleCommand* GetEntryCommand(std::string command_id);

		void OnHelp();

	private:
		std::map<std::string, ConsoleCommandGroup*> map_command_groups_;
		std::map<std::string, ConsoleCommand*> map_entry_command_;
		ConsoleCommand* null_command_;
	};
}