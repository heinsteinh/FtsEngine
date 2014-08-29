//
// CommandSystem.h
// Engine
//
// Created by Tobias Boogh on 9/23/12.
// Copyright (c) 2012 Tobias Boogh. All rights reserved.
//

/* Cheep command system will be replaces with LUA commands in v.1.1
I created this only to have a simple method to queue commands */

#ifndef _CommandSystem_H_
#define _CommandSystem_H_

#include <functional>
#include <unordered_map>

#include "TSingleton.h"



#define BIND_COMMAND(X) std::bind(&X, this, std::placeholders::_1)

namespace tin
{
	class Json_
	{
	public:
		Json_()	{}
		~Json_()	{}

		static std::string Value;
	private:
	};

	typedef struct _Json_
	{
		typedef std::string Value;
	}Json;


	typedef enum{
		CommandPriorityLow,
		CommandPriorityMedium,
		CommandPriorityHigh,
		CommandPriorityCount
	} CommandPriority;

	
	typedef std::function<void(Json::Value &)> command_function;

	typedef struct Command {
		Command() : priority(CommandPriorityMedium) { };
		command_function function;
		CommandPriority priority;
		std::function<void(void)> callback;
		Json::Value data;
	} Command;


	class CommandSystem : public CSingleton<CommandSystem>
	{
		friend class CSingleton<CommandSystem>;

	public:
		~CommandSystem();
		void AddCommand(std::string name, command_function func);
		command_function FindCommand(std::string name);
		void QueueCommand(std::string name, Json::Value data);
		void QueueCommand(std::string name);
		void Frame();


	private:

		typedef std::unordered_map<std::string, command_function> CmdMap;
		typedef std::list<Command> CmdQueue;

		CmdMap command_map_;
		CmdQueue command_queue_;

		void Init();
		void Shutdown();
		void Update();
	};

} // tin
#endif