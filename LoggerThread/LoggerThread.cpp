// LoggerThread.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

// iostream
using ::std::cout;
using ::std::endl;

#include "LogThread.h"
#include "UserThread.h"
#include "RenderThread.h"

//https://github.com/GodwinneLorayne/Bus/blob/e240c4507a7fc721b61b7dea94d436d589e74f21/fluffykitten/main.cpp


int _tmain(int argc, _TCHAR* argv[])
{

	cout << "Welcome to the test harness!" << endl;

	fk::LogThread log;
	log.NotifyStart();

	log.set_log_level(fk::LogLevel::Verbose);
	{
		fk::RenderThread render;
		render.NotifyStart();

		fk::UserThread user;
		user.StartOnThisThread();
		// Because we can only get to the end of this block
		// once u has stopped, we don't need to wait for it.

		render.NotifyStop();
		render.WaitForStop();
	}

	log.NotifyStop();
	log.WaitForStop();

	return 0;
}

