#pragma once

#include "StateMachine.h"
#include "eventchannel.h"
#include "StateTransition.h"

#include <iostream>

class BtnUpEvent;
class EventTansitionState : public core::cStateMachine<EventTansitionState, double>, core::EventHandler<EventTansitionState>
{
public:
	core::EventChannel mEventMgr;

public:
	EventTansitionState();
	~EventTansitionState();
	
	
	bool OnEnterOk();
	bool OnExitOk();
	void OnUpdateOk(double);



	
public:
	/*
	class BtnUpEvent :public   core::EventHandler<EventTansitionState>
	{

	public:
	};


	struct ExitingState : core::cState<ExitingState, double>
	{
		typedef TVector<void> Reactions;
	};

	struct RunningState : core::cState<RunningState, double>
	{
		typedef TVector<StateTransition<BtnUpEvent, ExitingState>> Reactions;
	};
	*/


	struct AEvent : core::EventHandler<AEvent>
	{
		void handle(const AEvent& evt)
		{
			std::cout << "Int Event AEvent" << std::endl;
		}

	};

		
	struct BState;
	struct AState : core::TBaseStateEvent<AState>
	{
		typedef TVector<StateTransition<AEvent, BState>> Reactions;
		

	/*	bool OnEnter(EventTansitionState *evtTState)
		{
			evtTState->GetParent();
			std::cout << "Enter A" << std::endl;
		}

		bool OnExit(EventTansitionState *evtTState)
		{
			evtTState->GetParent();
			std::cout << "Exit A" << std::endl;
		}*/
	};

	

	

	void handle(const BtnUpEvent& evt);

private:
	//tState m_initialState;
	//tState m_charOkState;
	//tState m_errorState;

	typedef core::cStateMachine<AState, double>  AStateMachine;
	//AEvent mAEvent;
	//AStateMachine* mStateMachineA;

	//AState mAState;

	tState m_initialState;
	tState m_charOkState;
	tState m_errorState;

};