// ThreadPoolWorkStealing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <list>
#include <iostream>
#include <algorithm>
#include <array>
#include <random>
#include <chrono>
#include <iostream>
#include <random>
#include <fstream>

//#include "thread_pool.h"


void func_int(int x)
{
	printf("int func: %d!!", x);
}

void func_void()
{
	printf("int func: %d!!");
}


void task(size_t seed, size_t number)
{
	std::mt19937 rng(seed);
	std::normal_distribution<> dist(0.0, 1.0);
	double sum = 0.0;
	for (size_t i = 0; i<number; ++i)
		sum += dist(rng);
	sum /= double(number);
	std::cerr << sum << std::endl;
}

struct task2
{
	size_t m_seed;
	size_t m_number;

	task2(size_t seed, size_t number) : m_seed(seed), m_number(number) { }

	double operator()(void) const
	{
		std::mt19937 rng(m_seed);
		std::normal_distribution<> dist(0.0, 1.0);
		double sum = 0.0;
		for (size_t i = 0; i<m_number; ++i)
			sum += dist(rng);
		sum /= double(m_number);
		return sum;
	}
};


struct S {
	static __declspec(thread) int a;
	static int b; // expected-note {{here}}
	static __declspec(thread) int c; // expected-error {{'thread_local' is only allowed on variable declarations}}
	static __declspec(thread) int d; // expected-note {{here}}
};



int _tmain(int argc, _TCHAR* argv[])
{
	//thread_pool pool;


	
	//std::future< double > res = pool.submit(task2(0, 2000));
	//std::cout << res.get() << std::endl;


	S s;


	return 0;
}

