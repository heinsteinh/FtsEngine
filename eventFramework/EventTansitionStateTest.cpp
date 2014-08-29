#include "stdafx.h"
#include "EventTansitionStateTest.h"


EventTansitionState::EventTansitionState()
: tStateMachine(&m_initialState)
, m_charOkState(&EventTansitionState::OnEnterOk, &EventTansitionState::OnExitOk, &EventTansitionState::OnUpdateOk)
{
	mEventMgr.add<BtnUpEvent>(*this);
}

EventTansitionState::~EventTansitionState()
{
}

////////////////////////////////////////

bool EventTansitionState::OnEnterOk()
{
	std::cout << "Enter EventTansitionState" << std::endl;
	return true;
}

////////////////////////////////////////

bool EventTansitionState::OnExitOk()
{
	auto self = dynamic_cast<EventTansitionState *>(this);
	std::cout << "Exiting EventTansitionState" << std::endl;
	
	return true;
}

////////////////////////////////////////

void EventTansitionState::OnUpdateOk(double)
{

}

void EventTansitionState::handle(const BtnUpEvent& evt)
{
	
}