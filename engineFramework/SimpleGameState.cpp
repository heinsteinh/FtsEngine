#include "stdafx.h"
#include "SimpleGameState.h"


namespace SimpleGameState
{
	SimpleGameState::~SimpleGameState() {}


	std::vector<SimpleGameState*> game::states{ new state_zero, new state_one, new state_two };


	SimpleGameState* state_zero::on_key_down(char key, game& g)
	{
		std::cout << "state_zero::on_key_down\n";

		if (key == '0') // no state transition
		{
			g.add_to_score(10); return this;
		}
		else return g.states[1]; // transit to state 1
	}

	SimpleGameState* state_one::on_key_down(char key, game& g)
	{
		std::cout << "state_one::on_key_down\n";

		if (key == '1') // no state transition
		{
			g.add_to_score(20); return this;
		}
		else return g.states[2]; // transit to state 2
	}

	SimpleGameState* state_two::on_key_down(char key, game& g)
	{
		std::cout << "state_two::on_key_down\n";

		if (key == '2') // no state transition
		{
			g.add_to_score(30); return this;
		}
		else return g.states[0]; // transit to state 0
	}


	//game::StateChangeEvent::StateChangeEvent(tState st){ mState = st; }

	void game::handle(const onEnterEvent& stEvt)
	{
	}

	void game::handle(const onExitEvent& stEvt)
	{}

	void game::handle(const StateExecuteEvent& stEvt)
	{
		int i = 0;
		/*if (!IsCurrentState(stEvt.mState))
		{
		GotoState(&stEvt.mState);
		}*/
	}
}
