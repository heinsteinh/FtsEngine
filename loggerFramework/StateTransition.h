#pragma once
#include <typeinfo>
#include<cstddef>

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
struct Transition
{
	typedef E Event;
	typedef T State;
};