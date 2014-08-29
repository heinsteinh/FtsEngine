#include "stdafx.h"
#include "ConCommand.h"


#include <iostream>

ConCommand::ConCommand(const char* name, const CommandFunction func) :  Job(func), m_name(name), m_func(func)
{	
	ConCommandExecuter::GetInstance().AddCommand(name, this);
}

ConCommand::~ConCommand()
{
}

void ConCommand::Do() const
{
	if (m_func.func)
	{
		m_func.func();
	}
}

ConCommandExecuter::ConCommandExecuter()
{

}

ConCommandExecuter::~ConCommandExecuter()
{

}

void ConCommandExecuter::AddCommand(const char* commandName, ConCommand* func)
{
	if (m_commands.find(commandName) == m_commands.end())
	{
		m_commands.emplace(commandName, func);
	}
	else
	{
		std::cout << "A command that already exists" << std::endl;
	}
}

ConCommand* ConCommandExecuter::FindCommand(const std::string& name) const
{
	auto commandIter = m_commands.find(name);
	if (commandIter != m_commands.end())
	{
		return commandIter->second;
	}

	return nullptr;
}


void ConCommandExecuter::Execute(const char* commandName)
{
	if (commandName == nullptr)
	{
		return;
	}

	auto itr = m_commands.find(commandName);
	if (itr == m_commands.end())
	{
		std::cout << "Wrong command." << std::endl;
		return;
	}

	itr->second->Do();
}

DECLARE_CONCOMMAND(exit)
{
	std::exit(0);
}