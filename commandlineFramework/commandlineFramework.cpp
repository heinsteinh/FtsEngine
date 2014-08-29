// commandlineFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//https://github.com/yxdtiger/Test/tree/d6fdf95bfccb4c0fea40d79c14eeca608fa9a6c9/Test/Src/V10/Src/commandline


#include <iostream>
using namespace std;

#include "console_command_processor.h"
using namespace wmdf;

int _tmain(int argc, _TCHAR* argv[])
{


	ConsoleCommandProcessor console_command_processor;


	console_command_processor.EnterMDFConsole();

	
	while (1)
	{
		string command_line;
		cin >> command_line;
		console_command_processor.ProcessConsoleCommand(command_line);
	}


	console_command_processor.ExitMDFConsole();
	return 0;
}

