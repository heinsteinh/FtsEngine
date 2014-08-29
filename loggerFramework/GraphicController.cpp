#include "stdafx.h"
#include "GraphicController.h"

namespace core
{


	GraphicController::GraphicController(std::shared_ptr<Dispatcher> dispatcher) : Controller(dispatcher), shouldStop_(false) 
	{	}

	GraphicController::~GraphicController() 
	{	}

	void GraphicController::start() 
	{		
		while (!shouldStop_)
		{
			// A bit of a hack, but it will do for now.
			for (int round = 0; round < 60 && !shouldStop_; ++round)
				std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}

	void GraphicController::stop() {
		shouldStop_ = true;
	}
	

}