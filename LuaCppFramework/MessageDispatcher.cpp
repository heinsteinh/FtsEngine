#include "stdafx.h"
#include "MessageDispatcher.h"


std::unique_ptr<MessageDispatcher> MessageDispatcher::singleton(nullptr);


void MessageDispatcher::Discharge(AIObject* pReceiver, const Telegram& msg)
{
	//if (!pReceiver->HandleMessage(msg))
	//{
	//	std::cerr << "Message not handled." << std::endl;
	//}
}

void MessageDispatcher::DispatchMessage(double delay, int sender, int receiver, int msg /*, luabind::object extraInfo*/)
{
	AIObject* pReceiver = NULL; /// (*AIObjectManager::GetInstance())->GetObjectFromID(receiver);

	if (pReceiver == NULL)
	{
		std::cerr << "No receiver found with an ID of " << receiver << " found." << std::endl;
		return;
	}

	Telegram message(0.0, sender, receiver, msg);

	if (delay <= 0.0)
	{
		Discharge(pReceiver, message);
	}
	else
	{
		//double currentTime = timer.GetTime();
		message.dispatchTime = delay;// + currentTime;
		PriorityQueue.insert(message);
	}
}

void MessageDispatcher::DispatchDelayedMessages()
{
	//double currentTime = timer.GetTime();

	//while(!PriorityQueue.empty() && (PriorityQueue.begin()->dispatchTime < currentTime) &&
	//(PriorityQueue.begin()->dispatchTime > 0))
	//{
	//const Telegram& message = *PriorityQueue.begin();

	//AIObject* pReceiver = (*AIObjectManager::GetInstance())->GetObjectFromID(message.receiver);

	//Discharge(pReceiver, message);

	//PriorityQueue.erase(PriorityQueue.begin());
	//}
}

std::unique_ptr<MessageDispatcher>* MessageDispatcher::GetInstance()
{
	if (singleton.get() == NULL)
	{
		singleton.reset(new MessageDispatcher);
	}
	return &singleton;
}