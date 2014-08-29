#pragma once


#include <typeinfo>
#include<cstddef>

//https://github.com/wanghengwei/Snake/blob/405a0956edf763e71469e5aedcea6d29bc70cb68/LogicEngine/Transition.h


template <class T, typename UPDATEARG= double>
class cState;


template<typename ... T>
struct TVector;

template< typename tState,  typename F, typename S, typename ... T>
struct TVector<tState, F, S, T ...>
{
	typedef cState<tState> TState;

	static TState * newStateByEvent(size_t hash)
	{
		if (typeid(typename F::Event).hash_code() == hash) {
			return new typename F::State;
		}
		else {
			return TVector<S, T ...>::newStateByEvent(hash);
		}
	}
};

template<typename tState, typename F>
struct TVector<tState, F>
{
	typedef cState<tState> TState;
	
	static TState * newStateByEvent(size_t hash)
	{
		if (typeid(typename F::Event).hash_code() == hash) {
			return new typename F::State;
		}
		else {
			return nullptr;
		}
	}
};


template<typename tState>
struct TVector<tState, void>
{

	typedef cState<tState> TState;
	static TState* newStateByEvent(size_t)
	{
		return nullptr;
	}
};



template<typename tState, typename Evt>
struct StateTransition
{
	typedef cState<tState, double> TState;

	typedef Evt Event;
	typedef TState State;
}; 





namespace protege_moi
{
	class BaseState;

	template<typename ... T>
	struct TVector;

	template<typename F, typename S, typename ... T>
	struct TVector<F, S, T ...>
	{
		static BaseState * newStateByEvent(size_t hash)
		{
			if (typeid(typename F::Event).hash_code() == hash) {
				return new typename F::State;
			}
			else {
				return TVector<S, T ...>::newStateByEvent(hash);
			}
		}
	};

	template<typename F>
	struct TVector<F>
	{
		static BaseState * newStateByEvent(size_t hash)
		{
			if (typeid(typename F::Event).hash_code() == hash) {
				return new typename F::State;
			}
			else {
				return nullptr;
			}
		}
	};


	template<>
	struct TVector<void>
	{
		static BaseState * newStateByEvent(size_t)
		{
			return nullptr;
		}
	};


	template<typename E, typename T>
	struct StateTransition
	{
		typedef E Event;
		typedef T State;
	};
}

