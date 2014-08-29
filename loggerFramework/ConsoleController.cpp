#include "stdafx.h"
#include "ConsoleController.h"
#include "Dispatcher.h"

#include "GraphicController.h"

#include "ConCommand.h"


#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>

namespace core {

	ConsoleController::ConsoleController() :Controller(std::shared_ptr<Dispatcher>(new Dispatcher(DISPATCHER_POOL_SIZE))) 
	{
	}

	ConsoleController::ConsoleController(std::shared_ptr<Dispatcher> dispatcher) :
		Controller(dispatcher) {
	}

	void ConsoleController::start(const std::string& localBackupInfoLocation) {
		bool exitCommandUsed = false;


		
		//Json::Value configInfo;
		bool configSuccessful = false;// getTrackerInfo(configInfo);

		if (!configSuccessful) {
			std::cerr << "Error: no valid configuration file found." << std::endl
				<< "Please create a file called config.json next to "
				<< "this executable to use this program." << std::endl
				<< "See the documentation for this program for more "
				<< "information about what should go in the "
				<< "configuration file." << std::endl;
			return;
		}


		createControllers(!localBackupInfoLocation.empty());


		startAllAsync();

		while (!exitCommandUsed) 
		{
			std::cout << "> ";
			std::string userInput;
			std::getline(std::cin, userInput);
			std::vector<std::string> splitInput;
		}

		stopAllAsync();
	}


	void ConsoleController::start() {
		start(std::string());
	}


	void ConsoleController::createControllers(bool deferChecking) 
	{
		asyncControllers_.push_back(std::shared_ptr<Controller>(new GraphicController(dispatcher_)));
	}



	void ConsoleController::startAllAsync()
	{
		for (std::vector<std::shared_ptr<Controller>>::iterator it = asyncControllers_.begin();	it != asyncControllers_.end(); ++it)
			asyncControllerThreads_.push_back((*it)->startInBackground());
	}

	void ConsoleController::stopAllAsync() {
		for (std::vector<std::shared_ptr<Controller>>::iterator it =
			asyncControllers_.begin();
			it != asyncControllers_.end();
		++it)
			(*it)->stop();

		// Use a second loop so that the shutdown signal can be given to all threads
		// before trying to join any of them.
		for (std::vector<std::shared_ptr<std::thread>>::iterator it =
			asyncControllerThreads_.begin();
			it != asyncControllerThreads_.end();
		++it) {
			(*it)->join();
		}
	}


}