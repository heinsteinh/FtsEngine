// EventSystem1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "EventSystem.h"
#include "Callbacks.h"


#include <memory>
#include <iostream>
#include <vector>
#include <utility>
#include <limits>
#include <cstdio>
#include <cstdlib>

#include <cassert>

#ifdef _MSC_VER
# define EXPECT_FUNC __FUNCTION__
#else
# define EXPECT_FUNC __func__
#endif


// originally these tests used gtest.
// this is a minimal imitation of its api, just enough to make
// the body of the tests work after a copy/paste.


#include <iostream>
using namespace std;
using namespace sample;





class EventArgs
{

public:
	EventArgs(int iValue)
	{
		// the type of a closure cannot be named, but can be inferred with auto
		auto func1 = [iValue ](int i)  -> void
		{
			i = iValue + 4;
			std::cout << "EventArgs Print x:" << i << std::endl;
		};
	}
};

class WindowdResizeEvent : public EventArgs
{
	int m_iw;
	int m_ih;

public:

	WindowdResizeEvent(int iw, int ih):EventArgs(iw)
	{
		m_ih = ih;
		m_iw = iw;
	}
};


void handlerVoid(void) 
{
	std::cout << "handlerVoid function." << std::endl;
}

void handlerArg(EventArgs const&) 
{
	std::cout << "handlerArg function." << std::endl;
}

struct EventHandler {
	void operator()(EventArgs const&)
	{
		std::cout << "EventHandler::operator()." << std::endl;
	}
};


void BoundHandler(int i, EventArgs const&) {
	std::cout << "Bound Handler function " << i << "." << std::endl;
}


struct EventHandler_MemFun
{
	void MemberFunction(EventArgs const&) {
		std::cout << "EventHandler::MemberFunction." << std::endl;
	}
};



namespace PlayerEvent
{
	class Player
	{
	public:
		Player() {}

		typedef Event<int&> CastSpellEvent;
		typedef Event<> DieEvent;


		void CastSpell(int spell_id) 
		{
			evt_castspell_(spell_id);
		}

		void Die() {
			evt_die_();
		}

		CastSpellEvent& evt_castspell() {
			return evt_castspell_;
		}

		DieEvent& evt_die() {
			return evt_die_;
		}

	private:
		CastSpellEvent evt_castspell_;
		DieEvent evt_die_;
	};

	class Monster
	{
	public:
		void Attack(Player* target)
		{
			holder1_ = target->evt_castspell().add(bind(&Monster::OnPlayerCastSpell, this, placeholders::_1));
			holder2_ = target->evt_die().add(bind(&Monster::OnPlayerDie, this));
		}

	private:
		void OnPlayerCastSpell(int spell_id)
		{
			cout << "aha, I see you!" << endl;
		}

		void OnPlayerDie() 
		{
			cout << "you are dead!" << endl;
		}

		ListenerID holder1_;
		ListenerID holder2_;
	};
}


void event_test_basics()
{
	callbacks cb;



	Event<int> event;
	
	ListenerID iEventArgsId[3];

	typedef Event<EventArgs const&> OnResizeEvent;
	OnResizeEvent onResizeEvent_;

	iEventArgsId[0] = onResizeEvent_.add(handlerArg);
	iEventArgsId[1] = onResizeEvent_.add(EventHandler());
	iEventArgsId[2] = onResizeEvent_.add([](EventArgs const& arg) { std::cout << "Lambda function." << std::endl; });

	WindowdResizeEvent resizeArgs(2, 5);
	onResizeEvent_(resizeArgs);  // raise all the Event add this this listener;


	// std::bind and placeholders
	onResizeEvent_.add(std::bind(BoundHandler, 1, std::placeholders::_1));
	EventHandler_MemFun handler;
	onResizeEvent_.add(std::bind(&EventHandler_MemFun::MemberFunction, handler, std::placeholders::_1));
	onResizeEvent_(resizeArgs);

		
	// the type of a closure cannot be named, but can be inferred with auto
	auto func1 = [](int i)  -> void 
	{
		i = i + 4; 
		std::cout << "Print x:" << i << std::endl;
	};

			
	typedef Event<int> eventVoid;
	eventVoid  eventVoid_;
	eventVoid_.add(func1);

	eventVoid_(2);


	assert(event.size() == 0);

	static const size_t NumListeners = 10;

	int vals[NumListeners] = {};

	ListenerID ids[NumListeners];

	for (size_t i = 0; i < NumListeners; ++i) 
	{
		// capture vals by reference, but i by value.
		ids[i] = event.add([&vals, i](int x) { vals[i] = x; });
	}

	assert(event.size() == NumListeners);

	for (auto id : ids) {
		assert(event.has(id));
	}

	event(20);

	for (auto val : vals) {
		assert(val==20);
	}
}


using namespace PlayerEvent;

int _tmain(int argc, _TCHAR* argv[])
{
	
		
	callbacks cb;

	cb.add("lol", [](int a, float b) 
	{
		std::cout << "a: " << a << std::endl;
		std::cout << "b: " << b << std::endl;
	});

	cb.call("lol", 23, 5.4f);
	cb.call("lol", 23, 43.0f);



	Player* player = new Player;
	Monster* monster = new Monster;
	Monster* monster2 = new Monster;
	monster->Attack(player);
	monster2->Attack(player);
	player->CastSpell(1044);
	delete monster2;
	player->CastSpell(1044);
	player->Die();
	delete player;
	delete monster;


	event_test_basics();

	return 0;
}

