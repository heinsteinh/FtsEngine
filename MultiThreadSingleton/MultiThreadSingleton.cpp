// MultiThreadSingleton.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include "ParamCommand.h"
#include "ConsoleManager.h"


#include "ConCommand.h"
#include "ObjectPoolTest.h"



float g_matWorld[3];


static core::FunctionCommand ShowCommand("show_command", [](std::initializer_list<std::string> commandNameList)
{
	for (auto& commandName : commandNameList)
	{
		GETSINGLE(ConsoleManager).ShowCommand(commandName);
	}
});

DECLARE_CONCOMMAND(quit)
{
	std::exit(0);
}

DECLARE_CONCOMMAND(stdprint)
{
	printf("test: stdprint  ");
}

int _tmain(int argc, _TCHAR* argv[])
{

	TestFunction();
	
	MemAllocTest();

	ObjectPoolTest();

	/*ConCommandExecuter::GetInstance().Execute("stdprint");



	core::VariableCommand cc_x_move("cc_x_move", "0");
	core::VariableCommand cc_y_move("cc_y_move", "0");
	core::VariableCommand cc_z_move("cc_z_move", "0");
	core::VariableCommand cc_adjust_zn("cc_adjust_zn", "0");
	core::VariableCommand cc_adjust_zf("cc_adjust_zf", "0");

	cc_x_move.SetValue(1.0f);
	cc_y_move.SetValue(2.0f);
	cc_z_move.SetValue(3.0f);
	
	core::ConsoleManager::GetInstance().ShowCommand("all");
	core::ConsoleManager::GetInstance().CommandExecute("cc_x_move 1");
	core::ConsoleManager::GetInstance().CommandExecute("cc_adjust_zn 2");

	core::ConsoleManager::GetInstance().ShowCommand("all");
*/
	ConCommandExecuter::GetInstance().Execute("quit");

	return 0;
}

