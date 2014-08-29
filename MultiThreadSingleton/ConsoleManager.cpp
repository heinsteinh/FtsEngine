#include "stdafx.h"
#include "ConsoleManager.h"

#include "MyType.h"
#include "MyDefines.h"
#include "ParamCommand.h"

namespace core
{
	ConsoleManager::~ConsoleManager()
	{}

	void ConsoleManager::AddCommand(Command* command)
	{
		if (command == nullptr)
			return;

		Command* existCommand = FindCommand(command->GetCommandName());
		if (existCommand)
		{
			LOG("Command is Already Exist")
			
			return;
		}

		m_mapCommand.insert({ command->GetCommandName(), command });
	}

	Command* ConsoleManager::FindCommand(const string& name) const
	{
		auto commandIter = m_mapCommand.find(name);
		if (commandIter != m_mapCommand.end())
		{
			return commandIter->second;
		}

		return nullptr;
	}

	void ConsoleManager::ShowCommand(const string& name)
	{
		if (name == "all")
		{
			for (auto command : m_mapCommand)
			{
				command.second->ShowCommand();
			}
			return;
		}

		Command* command = FindCommand(name);
		if (command == nullptr)
		{
			LOG("Command is not Exist");
			return;
		}

		command->ShowCommand();
	}

	void ConsoleManager::CommandExecute(const char* cmd)
	{
		if (cmd == nullptr)
			return;

		vector<string> params = SpliteCommand<string>(string(cmd), string(" "));
		if (params.size() <= 0)
		{
			return;
		}

		string cmdName = params[0];
		Command* command = FindCommand(cmdName);
		if (command == nullptr)
		{
			LOG("Command is not Exist");
			return;
		}

		STD_ERASE(params, STD_REMOVE_IF(params, [&cmdName](const string& str){ return cmdName == str; }));

		command->Execute(initializer_list<string>(params.data(), params.data() + params.size()));
	}
};