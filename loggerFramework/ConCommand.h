#pragma once

#include "TSingleton.h"
#include "Job.h"

#include <string>
#include <unordered_map>

//typedef void(*CommandFunction)(void);
typedef std::function<void(void)>  CommandFunction;

class ConCommand : public core::Job
{
public:
	explicit ConCommand(const char* name, CommandFunction func);
	~ConCommand();

	void Do() const;
	Job GetCmdFunct(){ return m_func; }

private:
	const char* m_name;
	Job m_func;
};


class ConCommandExecuter : public core::CSingleton<ConCommandExecuter>
{
	friend class core::CSingleton<ConCommandExecuter>;
	
public:
	explicit ConCommandExecuter();
	~ConCommandExecuter();

	void AddCommand(const char* commandName, ConCommand* command);
	void Execute(const char* commandName);
	ConCommand* FindCommand(const std::string& name) const;

private:
	std::unordered_map<std::string, ConCommand*> m_commands;
};


#define DECLARE_CONCOMMAND( name ) \
	void CommandFuction_##name(); \
	ConCommand conCommand_##name(#name, CommandFuction_##name); \
	void CommandFuction_##name()