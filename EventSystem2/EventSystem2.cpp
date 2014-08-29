// EventSystem2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



#include <iostream>
#include <functional>
#include <set>

template<class ReturnType, class... Args>
class EventProvider
{
private:
	typedef std::function<ReturnType(Args...)> Function;
	typedef ReturnType(*F)(Args...);

	struct FunctionByPointer
	{
		bool operator()(const Function &_f1, const Function &_f2) const
		{
			return (int)*_f1.target<F>() < (int)*_f2.target<F>();
		}
	};

	typedef std::set<Function, FunctionByPointer> Registered;

private:
	Registered regs;

public:
	void reg(Function f)
	{
		regs.insert(f);
	}

	void call(Args&&... args)
	{
		for (auto &f : regs)
		{
			f(std::forward<Args>(args)...);
		}
	}
};

void handle1(int arg, int arg2)
{
	std::cout << "Handling1 " << arg << " " << arg2 << "!\n";
}

void handle2(int arg, int arg2)
{
	std::cout << "Handling2 " << arg << "!\n";
}



int _tmain(int argc, _TCHAR* argv[])
{

	std::cout << "Hello, world!\n";


	EventProvider<void, int, int> events;

	events.reg(handle1);
	events.reg(handle2);

	events.call(3, 4);

	return 0;
}

