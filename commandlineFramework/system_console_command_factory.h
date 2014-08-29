#pragma once



#include <string>


namespace wmdf
{
	class ConsoleCommand;
	class ConsoleCommandGroup;


	ConsoleCommand* CreateNullConsoleCommand();
	
	ConsoleCommandGroup* CreateSystemConsoleCommandGroup();


	ConsoleCommand* CreateSystemConsoleCommand(std::string command_name);

}