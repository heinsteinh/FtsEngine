#include "stdafx.h"
#include "InputActivity.h"

#include <chrono>


namespace ANAS
{

	InputActivity::InputActivity()
	{
		//key_map_[InputData::Key::eUp] = InputData::Action::kMoveUp;
		//key_map_[InputData::Key::eDown] = InputData::Action::kMoveDown;
		//key_map_[InputData::Key::eLeft] = InputData::Action::kMoveLeft;
		//key_map_[InputData::Key::eRight] = InputData::Action::kMoveRight;
	}


	InputActivity::~InputActivity()
	{
		if (isLive == true){
			Term();
		}
	}

	void InputActivity::Init(AInputQueue *pInput)
	{
		//pInputQueue = _queue;
		isLive = true;

		// Start Polling Thread
		PollThread = THREAD_PTR(new std::thread(std::bind(&ANAS::InputActivity::Poll, this)));
	}


	void InputActivity::Poll()
	{
	
		//ANAS::Log::i("Input", "entry poll function");

		//InputKeyData _keytemp;
		//InputMotionData _motiontemp;
		InputData::InputData temp;

		// for Signal
		Notification();

		// loop
		while (1)
		{

			
			// break
			if (isLive == false)
			{
				break;
			}

			std::chrono::milliseconds dura(2000);
			std::this_thread::sleep_for(dura);
			
			//usleep(100);
		}
	}

	

	void InputActivity::Term()
	{
		{
			std::lock_guard<std::mutex> Lock(Mutex);
			isLive = false;
		}

		if (PollThread != NULL){
			PollThread->join();
		}

		//pInputQueue = NULL;
	}



	void InputActivity::SendEvent(InputData::InputData& evtData)	
	{		
		// Lock
		std::lock_guard<std::mutex> Lock(Mutex);
		
		EventStack.push_back(evtData);
	}


	InputData::InputData InputActivity::PopState()
	{

		// Lock
		std::lock_guard<std::mutex> Lock(Mutex);
		
		InputData::InputData _temp = { -1, -1 };

		// Pop
		if (EventStack.size() > 0)
		{
			_temp = EventStack.front();
			EventStack.pop_front();
		}


		return _temp;
	}


	void InputActivity::SetScreenOffset(int _x, int _y)
	{

		// Lock
		std::lock_guard<std::mutex> Lock(Mutex);

		offset_x = _x;
		offset_y = _y;
	}

	


	//bool InputActivity::SendEventTask(const InputData::TaskKey::Holder& event)
	//{		
	//	return true;			 
	//}


	
	//void InputActivity::SendEvent(InputData::Key ekey, bool pressed)
	//{
	//	if (key_map_.find(ekey) != key_map_.end())
	//	{
	//		InputData::Action action = key_map_.find(ekey)->second;
	//		InputData::Event event = { action, pressed };

	//		InputData::TaskKey::Holder evfunc(event);
	//		SendEvent(evfunc);
	//	}
	//}



	//bool InputActivity::SendEvent(const InputData::Event& evt)
	//{
	//	InputData::TaskKey::Holder evfunc(evt);
	//	SendEvent(evfunc);
	//}

	//bool InputActivity::SendEvent(const InputData::TaskKey::Holder& evt)
	//{
	//	submit(new InputData::TaskKey(InputData::TaskKey::Holder(std::bind(&ANAS::InputActivity::SendEventTask, this, evt))));
	//	return true;
	//}

	//bool SendEvent(const InputData::TaskKey::Holder& evt);

	//void InputActivity::MapKeyToAction(InputData::Key& ekey, InputData::Action& act)
	//{
	//	key_map_[ekey] = act;
	//}

}