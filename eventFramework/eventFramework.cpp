// eventFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "eventchannel.h"
#include <iostream>
#include <cassert>
#include <string>


#include "StateMachineTest.h"
#include "StateTransition.h"
#include "StateMachine.h"

#include "EventAllInOne.h"

#include "Log.h"
#include "ThreadBase.h"
#include "RenderThread.h"
#include "taskmanager.h"
#include "Boid.h"



namespace test_framework
{

	using namespace core;

	struct Dummy {};
	struct IntTransport { int i; };
	struct StringTransport { std::string message; };

	struct DummyHandler {
		void handle(const Dummy& d) {
			std::cout << "Dummy!" << std::endl;
		}
	};

	struct DoubleHandler {
		void handle(const IntTransport& i) {
			std::cout << "Int: " << i.i << std::endl;
		}

		void handle(const StringTransport& s) {
			std::cout << "Message: " << s.message.c_str() << std::endl;
		}
	};

	struct PtrHandler
	{
		void handle(const StringTransport* ps) {
			std::cout << "(Ptr) Message: " << ps->message.c_str() << std::endl;
		}
	};


	//test_framework::EventChannel chan;
	//test_framework::Dummy dummy;
	//test_framework::IntTransport inty;
	//test_framework::StringTransport str;
	//test_framework::StringTransport* strptr;

	//void broadcast(const std::string& message)
	//{
	//	std::cout << message.c_str() << std::endl;
	//	chan.broadcast(dummy);
	//	chan.broadcast(inty);
	//	chan.broadcast(str);
	//	chan.broadcast(strptr);
	//	std::cout << "Done" << std::endl << std::endl;
	//}

}


struct Explosion
{
	explicit Explosion(int damage) : damage(damage) {}
	int damage;
};



struct ExplosionHandlerOp : public h4d::EventHandler<Explosion>
{
	
	void operator()(const Explosion& d)
	{
		std::cout << "Explosion : !" << d.damage << std::endl;
	}
};


struct ExplosionHandler
{
	void handle(const Explosion& d)
	{
		std::cout << "Explosion : !" << d.damage << std::endl;
	}
};


struct ExplosionSystemnHandler
{

	int damage_received = 0;

	void handle(const Explosion& d)
	{
		damage_received = d.damage;
		std::cout << "Explosion : !" << d.damage << std::endl;
	}
};



class AEvent : core::EventHandler<AEvent>
{
public:
	void handle(const AEvent& evt)
	{
		std::cout << "Int Event AEvent" << std::endl;
	}
};


class BState;
class AState : public core::TBaseStateEvent<AState, double>
{
public:
	typedef TVector<StateTransition<AEvent, BState>> Reactions;	

	AState()
	{}
	AState(tStateEnterExitFn pfnStateEnter, tStateEnterExitFn pfnStateExit, tStateUpdateFn pfnStateUpdate){}
	


};


class StateMachineA : public core::cStateMachine<StateMachineA, double>
{
public:
	StateMachineA() :
		tStateMachine(&m_initialState),
		m_initialState(&StateMachineA::onEnter, &StateMachineA::onExit, &StateMachineA::onUpdate),
		m_errorState(&StateMachineA::OnEnterErrorState, NULL, NULL),
		m_stagedInitState(NULL, NULL, &StateMachineA::OnRunInitStages),
		m_finishedState(&StateMachineA::OnEnterFinishedState, NULL, NULL)
	{}

	~StateMachineA()
	{}

	bool onEnter()
	{
		std::cout << "onEnter" << std::endl;
		return true;
	}

	bool onExit()
	{
		std::cout << "onExit" << std::endl;
		return false;
	}

	void onUpdate(double)
	{		
		std::cout << "onUpdate" << std::endl;
		GotoState(&m_stagedInitState);
	}

	void OnInitialStateUpdate(double)
	{
		std::cout << "OnEnterErrorState" << std::endl;
		GotoState(&m_stagedInitState);
	}

	bool OnEnterErrorState()
	{
		std::cout << "OnEnterErrorState" << std::endl;
		return false;
	}
	void OnRunInitStages(double)
	{
		std::cout << "OnRunInitStages" << std::endl;
		GotoState(&m_finishedState);
	}

	bool OnEnterFinishedState()
	{
		std::cout << "OnEnterFinishedState" << std::endl;
		GotoState(&m_finishedState);
		return false;
	}


private:
	tState m_initialState;
	tState m_errorState;
	tState m_stagedInitState;
	tState m_finishedState;
};


class MyRunner : public BubbleBattleBoids::Runnable
{
public:
	MyRunner();
	~MyRunner();

	void run();

private:

};

MyRunner::MyRunner()
{
}

MyRunner::~MyRunner()
{
}

void MyRunner::run()
{
	LOG_INFO("Une info MyRunner");
}



class EndTask : public core::Task {
public:
	EndTask(core::TaskManager* tm) : core::Task(SINGLETHREADED), tm_(tm) {}
	~EndTask() {}

	void run() final { tm_->stop(); }

	core::TaskManager* tm_;
};


int _tmain(int argc, _TCHAR* argv[])
{

	h4d::EventChannel chan_safe;

	core::EventChannel chan;
	ExplosionHandler explosion_handler;
	ExplosionHandlerOp explosion_handler_op;
	
	Explosion _explosion(4);
	
	chan.add<Explosion>(explosion_handler);


	chan_safe.add<Explosion>(explosion_handler_op);	
	chan_safe.broadcast(_explosion);


	chan.broadcast(_explosion);

	ExplosionSystemnHandler explosion_system;
	chan.add<Explosion>(explosion_system);
	Explosion explosion(0);;
	chan.broadcast(explosion);

	assert(0 == explosion_system.damage_received);
	chan.broadcast(Explosion(10));
	assert(10 == explosion_system.damage_received);

	/*BubbleBattleBoids::RenderThread renderThread;


	MyRunner runner;
	BubbleBattleBoids::Thread inputThread(&runner);*/
	
	/*for (int i = 20 - 1; i >= 0; i--)
	{
		BubbleBattleBoids::Boid* obj = new BubbleBattleBoids::Boid(Vec2(i, 0));
	}*/

	


	//core::TaskManager tm;

	//// try queue with no multithreaded tasks
	////tm.add(core::TaskManager::TaskPtr(new EndTask(&tm)));
	//tm.start();

	return 0;
}

