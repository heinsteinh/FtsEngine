#pragma once


#include "eventhandler.h"
#include "StateTransition.h"
#include <typeinfo>

namespace core
{
	template <class tEvent>
	class EventHandler;
}


//https://github.com/jswigart/omnibot/blob/96b7db730ffed31edc51e0cfbd8e14aa659b50d7/Omnibot/Common/IGame.h
//https://github.com/dpalma/sge/blob/98357c91eb77d6effe50dd11e926fb637f68a295/api/tech/statemachine.h

namespace core
{

	class UpdateDelay
	{
	public:

		double GetDelay()	const { return m_UpdateDelay; }
		int GetDelayMsec()	const { return (int)(m_UpdateDelay); }
		double GetRate()	const { return m_UpdateDelay / 1000.f; }


		UpdateDelay(double _delay = 0) : m_UpdateDelay(_delay) {}
	private:
		double m_UpdateDelay;
	};


	template <class T, typename UPDATEARG>
	class cState
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
		
		virtual cState<T, UPDATEARG>* processEvent(const cState<T, UPDATEARG > &);
		

	private:
		tStateEnterExitFn	m_pfnStateEnter;
		tStateEnterExitFn	m_pfnStateExit;
		tStateUpdateFn		m_pfnStateUpdate;
	};


	template <class MD, typename UPDATEARG = double>
	class TBaseStateEvent : public cState<TBaseStateEvent<MD>, UPDATEARG> //, public core::EventHandler<TBaseStateEvent>
	{
	public:
		TBaseStateEvent(){}
		TBaseStateEvent(tStateEnterExitFn pfnStateEnter, tStateEnterExitFn pfnStateExit, tStateUpdateFn pfnStateUpdate){}

		
		cState<TBaseStateEvent<MD>, UPDATEARG>* processEvent(const cState<TBaseStateEvent<MD>, UPDATEARG> &event)
		{			
			//MD::Reactions::newStateByEvent(typeid(event).hash_code());
			return NULL; // MD::Reactions::newStateByEvent(typeid(event).hash_code());
		}		
	};



	//////////////////////////////////////////////////////////////////////////
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
	cState<T, UPDATEARG>* cState<T, UPDATEARG>::processEvent(const cState<T, UPDATEARG > &)
	{
		return this;
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
	cStateMachine<T, UPDATEARG, STATE>::cStateMachine(const tState * pInitialState): m_pCurrentState(pInitialState)
	{
	}

	////////////////////////////////////////

	template <class T, typename UPDATEARG, class STATE>
	cStateMachine<T, UPDATEARG, STATE>::~cStateMachine()
	{
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


	////////////////////////////////////////////////////////////////////////////////
}



