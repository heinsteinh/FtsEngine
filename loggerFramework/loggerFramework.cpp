// loggerFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Logger.h"

#include <cassert>
#include <iostream>

#include <Windows.h>  // used for sleep 

#include "Helper.h"


#include "Dispatcher.h"
#include "GraphicController.h"
#include "ConCommand.h"

#include "ParamCommand.h"
#include "ConsoleManager.h"

void printValue(void)
{
	printf("Value: ThreadId:: %d \n", std::this_thread::get_id() );
}

void runJob2(int iValue)
{
	for (int i = 0; i < 1; i++)
	{
		{
			// This is the code of the job.
			long long sum = 0;
			for (int j = 0; j < iValue; j++)
				sum += rand();
			printf("AI: The sum was %lld\n", sum);
		}

		{
		long long sum = 0;
		for (int j = 0; j < iValue; j++)
			sum += rand();
		printf("Graphics job: got %lld\n", sum); // this makes no sense, its just code that runs.
	}
	}
}

void runJob()
{
	for (int i = 0; i < 1; i++)
	{
		{
			// This is the code of the job.
			long long sum = 0;
			for (int j = 0; j < 100000000L; j++)
				sum += rand();
			printf("AI: The sum was %lld\n", sum);
		}

		{
		long long sum = 0;
		for (int j = 0; j < 200000000L; j++)
			sum += rand();
		printf("Graphics job: got %lld\n", sum); // this makes no sense, its just code that runs.
	}
	}
}




DECLARE_CONCOMMAND(Exit)
{
	printf(": Exit  \n");
}

DECLARE_CONCOMMAND(Up)
{
	printf(": Up  \n");
}

DECLARE_CONCOMMAND(Down)
{
	printf(": Down  \n");
}

DECLARE_CONCOMMAND(Space)
{
	printf(": Space  \n");
}
DECLARE_CONCOMMAND(stdprint)
{
	printf(": stdprint  \n");
}



int _tmain(int argc, _TCHAR* argv[])
{

	ConCommandExecuter::GetInstance().Execute("Exit");
	ConCommandExecuter::GetInstance().Execute("Up");
	ConCommandExecuter::GetInstance().Execute("Down");
	ConCommandExecuter::GetInstance().Execute("Space");


	std::shared_ptr<core::Dispatcher> dispatcher(new core::Dispatcher());
	std::shared_ptr<core::Controller> controller(new core::GraphicController(dispatcher));

	ConCommand* jobCmd = ConCommandExecuter::GetInstance().FindCommand("stdprint");
	dispatcher->scheduleJob(*jobCmd);

	core::Job job(printValue);
	dispatcher->scheduleJob(job);
	
	int count = 0;
	for (int i = 0; i < 32; ++i)
	{			
		job = core::Job(runJob);
		dispatcher->scheduleJob(job);		
	}



	ConCommandExecuter::GetInstance().Execute("stdprint");


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

	
	ConCommandExecuter::GetInstance().Execute("quit");




	//core::Helper helper;
	//bool b = false;
	//assert(!b);

	//for (size_t i = 0; i < 10; i++)
	//{
	//	helper.enq(runJob);
	//}
	//
	//std::this_thread::sleep_for(std::chrono::milliseconds(10)); // sleep_for not enabled on some gcc

	//Sleep(100 * 1000);

	//getchar();
	return 0;
}

