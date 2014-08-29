#pragma once

#include "TSingleton.h"

#include <string>
#include <unordered_map>

//typedef void(*CommandFunction)(void);
typedef std::function<void(void)>  CommandFunction; // void(*CommandFunction)(void);

class ConCommand
{
public:
	explicit ConCommand(const char* name, CommandFunction func);
	~ConCommand();

	void Do() const;
private:
	const char* m_name;
	CommandFunction m_func;
};


class ConCommandExecuter : public core::CSingleton<ConCommandExecuter>
{
	friend class core::CSingleton<ConCommandExecuter>;
	
public:
	explicit ConCommandExecuter();
	~ConCommandExecuter();

	void AddCommand(const char* commandName, ConCommand* command);
	void Execute(const char* commandName);

private:
	std::unordered_map<std::string, ConCommand*> m_commands;
};


#define DECLARE_CONCOMMAND( name ) \
	void CommandFuction_##name(); \
	ConCommand conCommand_##name(#name, CommandFuction_##name); \
	void CommandFuction_##name()