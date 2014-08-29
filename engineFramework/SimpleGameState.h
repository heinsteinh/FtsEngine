#pragma once


#include "StateMachine.h"




namespace SimpleGameState
{

	//http://www.cplusplus.com/forum/general/91043/
	class game;
	class SimpleGameState : public core::cState<SimpleGameState, double>
	{
	public:
		virtual ~SimpleGameState();

		// handle key down event, return state after event
		virtual SimpleGameState* on_key_down(char key, game& g) = 0;
		virtual const char* name() const =0;	
	};
	
	

	class state_zero : public SimpleGameState
	{
	public:
		virtual const char* name() const override { return "#0"; }
		virtual SimpleGameState* on_key_down(char key, game& g) override;
		/* ... */
	};

	class state_one : public SimpleGameState
	{
	public:
		virtual const char* name() const override { return "#1"; }
		virtual SimpleGameState* on_key_down(char key, game& g) override;
		/* ... */
	};

	class state_two : public SimpleGameState
	{

	public:
		virtual const char* name() const override { return "#2"; }
		virtual SimpleGameState* on_key_down(char key, game& g) override;
		/* ... */
	};


	struct StateChangeEvent;
	class game : public core::cStateMachine<game, double>
	{
	public:

		struct StateExecuteEvent
		{
			explicit StateExecuteEvent(SimpleGameState* st){ mState = st; }
			SimpleGameState* mState;
		};

		struct onEnterEvent
		{		
			explicit onEnterEvent( SimpleGameState* st){ mState = st; }
			SimpleGameState* mState;
		};

		struct onExitEvent
		{
			explicit onExitEvent(SimpleGameState* st){ mState = st; }
			SimpleGameState* mState;
		};

		struct Explosion
		{
			explicit Explosion(int damage) : damage(damage) {}
			int damage;
		};


		struct ExplosionHandler
		{
			void handle(const Explosion& d)
			{
				std::cout << "Explosion : !" << d.damage << std::endl;
			}
		};


	public:
		game() :tStateMachine(&m_CurrentState), m_CurrentState(&game::onEnter, &game::onExit, &game::onExecute)
		{						
			mEvent.add<StateExecuteEvent>(*this);
			mEvent.add<onExitEvent>(*this);
			mEvent.add<onEnterEvent>(*this);
		}

		~game()
		{
			mEvent.remove<StateExecuteEvent>(*this);
			mEvent.remove<onExitEvent>(*this);
			mEvent.remove<onEnterEvent>(*this);
		}

		int score() const { return current_score; }
		int add_to_score(int v) { 
		
			GotoState(&m_CurrentState);
			return current_score += v; 
		}


		void on_key_down(char key)
		{			
			current_state = current_state->on_key_down(key, *this);
			std::cout << "    on key: " << key << "   state: " << current_state->name() << '\n';
			
			StateExecuteEvent st(0);
			ExplosionHandler explosion_handler;
			Explosion _explosion(4);
			
			mEvent.add<Explosion>(explosion_handler);			
			mEvent.broadcast(_explosion);
			mEvent.remove<Explosion>(explosion_handler);

			GotoState(&m_InitState);
		}

		 
		bool onEnter()	
		{
			mEvent.broadcast(onEnterEvent(current_state));
			std::cout << " on state enter: " << current_state->name() << '\n'; 
			return true;
		};

		bool onExit()
		{
			mEvent.broadcast(onExitEvent(current_state));
			std::cout << " on state exit: " << current_state->name() << '\n';
			return true; 
		}

		void onExecute(double f) 
		{
			mEvent.broadcast(StateExecuteEvent(current_state));
			std::cout << " on state execute" << current_state->name() << '\n';
		}


		// accessors elided for brevity
		static std::vector< SimpleGameState* > states;


		void handle(const onEnterEvent& stEvt);
		void handle(const onExitEvent& stEvt);
		void handle(const StateExecuteEvent& stEvt);



	private:
		int current_score;
		SimpleGameState* current_state = states[0];

		tState m_InitState;
		tState m_CurrentState;
		core::EventChannel mEvent;
	};

}

//SimpleGameState::game g;
//char c = 'o';
//while (c != 'q')
//{
//	std::cin >> c;
//	g.on_key_down(c);
//}

