#include "stdafx.h"

#include "CommandSystem.h"
#include "LoggingSystem.h"

#include <list>
#include <string>
#include <unordered_map>


namespace tin {
	CommandSystem::~CommandSystem(){

	}

	void CommandSystem::Init(){

	}

	void CommandSystem::Shutdown(){

	}

	void CommandSystem::AddCommand(std::string name, command_function func){
		command_map_[name] = func;
	}

	void CommandSystem::QueueCommand(std::string name){
		command_function func = command_map_[name];
		if (!func){
			LoggingSystem::LogError("CommandSystem::QueueCommand: Missing command %s", name.c_str());
			return;
		}
		Command command;
		command.function = func;
		command_queue_.push_back(command);
	}

	void CommandSystem::QueueCommand(std::string name, Json::Value data)
	{
		command_function func = command_map_[name.c_str()];
		if (!func){
			LoggingSystem::LogError("CommandSystem::QueueCommand: Missing command %s", name.c_str());
			return;
		}
		Command command;
		command.function = func;
		command.data = data;
		command_queue_.push_back(command);
	}

	void CommandSystem::Frame(){
		CmdQueue::iterator iter;
		for (iter = command_queue_.begin(); iter != command_queue_.end(); ++iter){
			iter->function(iter->data);
			iter = command_queue_.erase(iter);
		}
	}

	command_function CommandSystem::FindCommand(std::string name){
		if (command_map_.find(name) != command_map_.end()){
			command_function command = command_map_[name];
			return command;
		}
		LoggingSystem::LogError("Command %s not found", name.c_str());
		return nullptr;
	}
}



