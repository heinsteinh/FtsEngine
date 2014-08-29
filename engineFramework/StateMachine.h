#pragma once
#include "System.h"


//https://github.com/jswigart/omnibot/blob/96b7db730ffed31edc51e0cfbd8e14aa659b50d7/Omnibot/Common/IGame.h
//https://github.com/dpalma/sge/blob/98357c91eb77d6effe50dd11e926fb637f68a295/api/tech/statemachine.h

namespace core
{

	class UpdateDelay
	{
	public:

		double GetDelay() const { return m_UpdateDelay; }
		int GetDelayMsec() const { return (int)(m_UpdateDelay); }
		double GetRate() const { return m_UpdateDelay / 1000.f; }


		UpdateDelay(double _delay = 0) : m_UpdateDelay(_delay) {}
	private:
		double m_UpdateDelay;
	};


	class Telegram;
	template <class T, typename UPDATEARG>
	class cState : public core::EventHandler<cState<T, UpdateDelay>>
	{
	public:
		friend class StateSimultaneous;

	public:

		cState(const cState &);
		const cState & operator =(const cState &);
		
		typedef bool (T::*tStateEnterExitFn)();
		typedef void (T::*tStateUpdateFn)(UPDATEARG);

	public:
		cState();
		cState(tStateEnterExitFn pfnStateEnter, tStateEnterExitFn pfnStateExit, tStateUpdateFn pfnStateUpdate);
		virtual ~cState();
		

		virtual bool ExecuteStateEnter(T * pT) const;
		virtual bool ExecuteStateExit(T * pT) const;
		virtual void ExecuteStateUpdate(T * pT, UPDATEARG arg) const;


		void handle(const cState<T, UpdateDelay>&)
		{
		}

		virtual void HandleMessage(T*, const Telegram&) {};


	private:
		tStateEnterExitFn	m_pfnStateEnter;
		tStateEnterExitFn	m_pfnStateExit;
		tStateUpdateFn		m_pfnStateUpdate;
	};



	//////////////////////////////////////////////////////////////////////////

	// class: StateChild
	// Pick a random child state to run, but never repeat the same one twice.
	class StateChild : public cState<StateChild, UpdateDelay>
	{
	public:
		StateChild();
		StateChild(tStateEnterExitFn pfnStateEnter, tStateEnterExitFn pfnStateExit, tStateUpdateFn pfnStateUpdate);

	protected:
	private:

	};


	///////////////////////////////////////////////////////////////////////////////
	//
	// CLASS: cStateMachine
	//

	template <class T, typename UPDATEARG, class STATE = cState<T, UPDATEARG> >
	class cStateMachine
	{
	public:
		typedef cStateMachine<T, UPDATEARG, STATE> tStateMachine;
		typedef STATE tState;

		cStateMachine(const tState * pInitialState);
		~cStateMachine();

		void Update(UPDATEARG arg);


		tState *GetParent()		const { return m_Parent; }
		tState *GetRootState()	const { return m_Root; }
		tState *GetFirstChild() const { return m_FirstChild; }
		tState *GetSibling()	const { return m_Sibling; }

		const tState *GetActiveState() const { return m_pCurrentState; }
		
		struct StateTransition
		{
			StateTransition(cState<T, UPDATEARG>  NewState) :mState(NewState){	}
			cState<T, UPDATEARG>  mState;
		};

		void handle(const StateTransition& newState);

	protected:
		bool IsCurrentState(const tState * pState) const;
		void GotoState(const tState * pNewState);


		

	private:
		const tState * m_pCurrentState;
		
		tState	*m_Sibling;
		tState	*m_Parent;
		tState	*m_FirstChild;
		tState	*m_Root;
	};



	
	///////////////////////////////////////////////////////////////////////////////
	//
	// CLASS: cStateManager
	//	
	class cStateManager :public System
	{
		typedef cStateMachine<cStateManager, UpdateDelay> tStateMachine;	
		
		typedef std::shared_ptr<tStateMachine>  StateMachinePtr;
		typedef std::map<std::string, StateMachinePtr> StateMachineMap;
		
		typedef std::shared_ptr<StateChild>  StatePtr_;
		typedef std::map<std::string, StatePtr_> StateMap_;
		

	public:
		cStateManager();
		~cStateManager();
		
		bool init();
		void update();
		void shutdown();
		
	
		/* StateMachinePtr specific */
		void addStateMachine(StateMachinePtr stateMachine, const std::string &s);
		const StateMachinePtr& getStateMachine(const std::string &s);
		void removeStateMachine(const std::string &s, bool destroy = true);


	private:
		StateMachineMap mStateMachineMap;
		StateMachineMap mRemovedStateMachineMap;

	};



	///////////////////////////////////////////////////////////////////////////////
	//
	// TEMPLATE: cState
	//

	////////////////////////////////////////

	template <class T, typename UPDATEARG>
	cState<T, UPDATEARG>::cState()
		: m_pfnStateEnter(NULL)
		, m_pfnStateExit(NULL)
		, m_pfnStateUpdate(NULL)
	{
	}

	////////////////////////////////////////

	template <class T, typename UPDATEARG>
	cState<T, UPDATEARG>::cState(tStateEnterExitFn pfnStateEnter,
		tStateEnterExitFn pfnStateExit,
		tStateUpdateFn pfnStateUpdate)
		: m_pfnStateEnter(pfnStateEnter)
		, m_pfnStateExit(pfnStateExit)
		, m_pfnStateUpdate(pfnStateUpdate)
	{
	}

	////////////////////////////////////////

	template <class T, typename UPDATEARG>
	cState<T, UPDATEARG>::~cState()
	{
	}

	////////////////////////////////////////

	template <class T, typename UPDATEARG>
	bool cState<T, UPDATEARG>::ExecuteStateEnter(T * pT) const
	{
		if ((pT != NULL) && (m_pfnStateEnter != NULL))
		{
			return (pT->*m_pfnStateEnter)();
		}
		return  false;
	}

	////////////////////////////////////////

	template <class T, typename UPDATEARG>
	bool cState<T, UPDATEARG>::ExecuteStateExit(T * pT) const
	{
		if ((pT != NULL) && (m_pfnStateExit != NULL))
		{
			return (pT->*m_pfnStateExit)();
		}
		return  false;
	}

	////////////////////////////////////////

	template <class T, typename UPDATEARG>
	void cState<T, UPDATEARG>::ExecuteStateUpdate(T * pT, UPDATEARG arg) const
	{
		if ((pT != NULL) && (m_pfnStateUpdate != NULL))
		{
			(pT->*m_pfnStateUpdate)(arg);
		}
	}

	



	///////////////////////////////////////////////////////////////////////////////
	//
	// TEMPLATE: cStateMachine
	//

	////////////////////////////////////////

	template <class T, typename UPDATEARG, class STATE>
	cStateMachine<T, UPDATEARG, STATE>::cStateMachine(const tState * pInitialState)
		: m_pCurrentState(pInitialState)
	{

		core::EventChannel echan;
		echan.add<StateTransition>(*this);
	}

	////////////////////////////////////////

	template <class T, typename UPDATEARG, class STATE>
	cStateMachine<T, UPDATEARG, STATE>::~cStateMachine()
	{
		core::EventChannel echan;
		echan.remove<StateTransition>(*this);
	}

	////////////////////////////////////////

	template <class T, typename UPDATEARG, class STATE>
	void cStateMachine<T, UPDATEARG, STATE>::Update(UPDATEARG arg)
	{
		if (m_pCurrentState != NULL)
		{
			T * pT = static_cast<T*>(this);
			m_pCurrentState->ExecuteStateUpdate(pT, arg);
		}
	}

	////////////////////////////////////////

	template <class T, typename UPDATEARG, class STATE>
	bool cStateMachine<T, UPDATEARG, STATE>::IsCurrentState(const tState * pState) const
	{
		return (m_pCurrentState == pState);
	}

	////////////////////////////////////////

	template <class T, typename UPDATEARG, class STATE>
	void cStateMachine<T, UPDATEARG, STATE>::GotoState(const tState * pNewState)
	{
		T * pT = static_cast<T*>(this);
		if ((pNewState != NULL) && (pNewState != m_pCurrentState))
		{
			m_pCurrentState->ExecuteStateExit(pT);
			m_pCurrentState = pNewState;
			m_pCurrentState->ExecuteStateEnter(pT);
		}
	}


	////////////////////////////////////////

	template <class T, typename UPDATEARG, class STATE>
	void cStateMachine<T, UPDATEARG, STATE>::handle(const StateTransition& newState)
	{				
		
		//if (!IsCurrentState(newState.mState))
			int i = 0;
		//GotoState(newState.mState);*/
	}
	////////////////////////////////////////////////////////////////////////////////
}

