#include "stdafx.h"
#include "Input.h"




ANAS::Input::Input() :
pInputQueue(NULL), offset_x(0), offset_y(0)
{

	// Create Pipe
	//pipe(EventPipe);

}

ANAS::Input::~Input()
{
	if (isLive == true)
	{
		Term();
	}
}


void ANAS::Input::Init(MSG* _queue)
{

	pInputQueue = _queue;
	isLive = true;

	// Start Polling Thread
	PollThread = THREAD_PTR(new std::thread(std::bind(&ANAS::Input::Poll, this)));

}

void ANAS::Input::Poll()
{

	InputData temp;

	// for Signal
	Notification();


	while (true)
	{

		// Lock
		//boost::mutex::scoped_lock Lock(Mutex);

		MSG *msg = pInputQueue;
		int ident;
		int event;
		int data;

		while (PeekMessage(msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(msg);
			DispatchMessage(msg);
		}



		if (msg->message == WM_QUIT )
		{
			isLive = false;
		}
			
		// break
		if (isLive == false)
		{
			break;
		}


		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

}


void ANAS::Input::Term(){

	{
		std::unique_lock<std::mutex>  Lock(Mutex);
		isLive = false;
	}


	if (PollThread != NULL)
	{
		PollThread->join();
	}

	pInputQueue = NULL;
}

ANAS::InputData ANAS::Input::PopState(){

	// Lock
	std::unique_lock<std::mutex>  Lock(Mutex);


	InputData _temp = { -1, -1 };

	// Pop
	if (EventStack.size() > 0){
		_temp = EventStack.front();
		EventStack.pop_front();
	}

	return _temp;
}

void ANAS::Input::SetScreenOffset(int _x, int _y){

	// Lock
	std::unique_lock<std::mutex>  Lock(Mutex);

	offset_x = _x;
	offset_y = _y;
}