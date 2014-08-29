// 04_Promises_easy.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <string>
//#include <boost/thread.hpp>
#include <thread>
#include <future>


class BackgroundTask
{
	std::promise<std::string> promise_;

public:
	void operator()()
	{
		//std::this_thread::sleep(boost::posix_time::seconds(3));
		promise_.set_value("Eureka");
	}

	std::future<std::string> get_future()
	{
		return promise_.get_future();
	}
};


void waiter(std::future<std::string> f)
{
	std::cout << f.get() << std::endl;


}

template< class T, class F>
std::future<T> add_future_task(F f)
{
	auto task = std::make_shared<std::packaged_task<T>>(f);
	std::future<T> res = task->get_future();
	queue.push([task]() { (*task)(); });

	return res;
}


int _tmain(int argc, _TCHAR* argv[])
{


	BackgroundTask bt{};
	//std::future<std::string> future = bt.get_future();
	//std::thread thd1(waiter, std::move(future));
	
	//std::thread thd1(waiter, bt.get_future());
	std::thread thd2(std::ref(bt));
	

	
	//thd1.join();
	thd2.join();
	return 0;
}

