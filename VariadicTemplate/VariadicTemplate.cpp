// VariadicTemplate.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <tuple>
#include "functor.h"




/*
namespace Variadic
{

	template<typename ... Args>
	struct FunctorImpl;


	template<typename R, typename ... Args>
	struct FunctorImpl<R(Args ...)>
	{
		typedef R(*FT)(Args ...);

		FunctorImpl(FT fn) : m_fn(fn) { ; }

		R operator () (Args ... args)
		{
			return m_fn(args ...);
		}

		FT m_fn;
	};
	
	template<typename FT>
	struct Functor : public FunctorImpl<FT>
	{
		Functor() : FunctorImpl<FT>(NULL) { ; }
		Functor(FT fn) : FunctorImpl<FT>(fn) { ; }
	};


	int plus_fn(int a, int b) { return a + b; }
	int minus_fn(int a, int b) { return a - b; }
	int increment(int& a) { return a++; }

	template<typename ... Type>
	void printf(const char* format, Type ... args);
}*/

//https://github.com/doremi/guiframe/blob/288d8098cb26d151767f59c0b809b2f55c87d607/lib/functor.cpp


struct TestFunctor 
{
	void operator()(int i)
	{
		printf("%s: %d\n", __FUNCTION__, i);
	}
};

void myFunction(int i)
{
	printf("%s: %d\n", __FUNCTION__, i);
}

int three(bool visible, double a)
{
	if (visible)
		printf("visible: %lf\n", a);
	else
		printf("invisible: %lf\n", a);
	return 10;
}

class Button 
{
public:
	typedef std::tuple_element<0, std::tuple<void(void)> >::type CallbackType;
	Button(Functor<CallbackType> &func) : func(func) {}
	void clicked() { func(); }
	void setClicked(Functor<CallbackType> &func) {
		this->func = func;
	}
private:
	Functor<CallbackType> func;
};


void nofunc()
{
	printf("I'm in nofunc!\n");
}

template<typename T, typename U>
auto myFunc(T& t, U& u)-> decltype(t + u)
{
	return t + u;
};


template <typename Signature>
class NoCommand;

template <typename R, typename... Args>
class NoCommand<R(Args...)> {
public:
	R operator()(Args...)
	{
	}
};

void abc()
{
}


int _tmain(int argc, _TCHAR* argv[])
{

	TestFunctor f;
	Functor<void(int)> cmd1(myFunction);
	Functor<void(int)> cmd2(f);
	Functor<int(bool, double)> cmd3(three);
	Functor<void(void)> cmd4(nofunc);

	Button btn(cmd4);
	btn.clicked();

	cmd1(4);
	cmd2(5);

	printf("return: %d\n", cmd3(true, 123.45));

	auto cmd5 = cmd1;
	cmd5 = cmd2;
	cmd5(10);



	std::cin.get();
	return 0;
}

