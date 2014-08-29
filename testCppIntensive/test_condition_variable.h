#include <iostream>
#include <functional>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>


//https://github.com/bmal/trash/blob/04a98aa612d13fba04f712e23d2334a1c938984d/test_condition_variable.cpp

struct S
{
	S() : is_(false) {}

	void put_object(int o)
	{
		object_ = o;
		is_ = true;
		is.notify_one();
	}

	int get_object()
	{
		is_ = false;
		return object_;
	}

	bool available()
	{
		return is_;
	}

	std::condition_variable is;


private:
	int object_;
	bool is_;
};

class A
{
private:
	std::mutex m;
	S& ref;
public:
	A(S& obj) : ref(obj) {}
	void set_value(int val)
	{
		std::lock_guard<std::mutex> lk(m);
		ref.put_object(val);
		std::cout << "Value Set: " << val << std::endl;
	}

	void get_value()
	{
		std::unique_lock<std::mutex> lk(m);
		ref.is.wait(lk, [this]()->bool{return ref.available(); });
		int i = ref.get_object();

		std::cout << "Received value: " << i << std::endl;
		lk.unlock();
		
	}
};

void thread_a(S& obj)
{
	A ob_a(obj);
	ob_a.get_value();
	ob_a.set_value(10);
	ob_a.set_value(12);
}

void thread_b(S& obj)
{
	A ob_a(obj);
	ob_a.set_value(3);
	ob_a.set_value(2);
	ob_a.get_value();
}