// testFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <cstdlib>
#include <queue>
#include <future>
#include <math.h>
#include <string>
#include "queue.h"
#include "safe_queue.h"
#include "thread_pool.h"
#include <Windows.h> //sleep


void func_string(const std::string &x) {}

void func_int(int x)
{
	printf("int func: %d!!", x);
}

void func_void(void) 
{
	printf("void func!!");
}



void standard_queue()
{
	std::queue<int> m_queue;

	for (int i = 0; i<100; i++)
		m_queue.push(i);

	while (!m_queue.empty()){
		std::cout << m_queue.front() << std::endl;
		m_queue.pop();
	}
}

void custom_queue()
{
	alm::queue<int> m_queue;
	for (int i = 0; i<100; i++)
		m_queue.push(i);

	while (!m_queue.empty())
		std::cout << m_queue.pop() << std::endl;
}


class Test
{
public:
	Test(alm::thread_pool &pool)
		: m_pool(pool), m_data("Test")
	{
		char ii;
		std::cin >> ii;
		while (ii != 'q')
		{
			std::future<void> result = pool.submit([&]{print(); });
			std::cout << " check1" << std::endl;
			result.wait();
			std::cout << " check2" << std::endl;

			std::cin >> ii;
		}

		std::cout << "Finish" << std::endl;
	}

	~Test() { }

	void print()
	{
		Sleep(3);
		std::cout << m_data << std::this_thread::get_id() << std::endl;
	}

private:
	alm::thread_pool& m_pool;
	std::string m_data;
};

void thread_pool()
{
	alm::thread_pool pool(2);

	Test test(pool);
}

int _tmain(int argc, _TCHAR* argv[])
{

	try
	{
		thread_pool();
	}
	catch (std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
	}

	/*alm::thread_pool pool;
		
	std::future<void> res1 = pool.submit(func_void);
	std::future<void> res2 = pool.submit(std::bind(func_int, 1));
	
	res1.get();
	res2.get();*/

	return 0;
}

