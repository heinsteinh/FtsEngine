// SharePtrSingleton.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <memory>
#include <iostream>


using namespace std;


namespace phony {

	template<class T>
	class singleton_manager 
	{
	public:
		singleton_manager(void)
		{
		}

		virtual ~singleton_manager(void)
		{
			this->clear();
		}

		virtual void clear() 
		{
		}

		static std::shared_ptr<T> instance(void) 
		{
			if (singleton_manager<T>::_instance == nullptr) 
			{
				singleton_manager<T>::_instance = std::make_shared<T>();
			}

			return _instance;
		}

	private:
		static std::shared_ptr<T> _instance;

	};

	template<class T>
	std::shared_ptr<T> singleton_manager<T>::_instance = nullptr;
}



template <class T>
class Singleton
{
public:
	static inline T* instance()
	{
		if (0 == _instance.get())
		{
			_instance.reset(new T);
		}
		return _instance.get();
	};
private:
	Singleton(void){};
	~Singleton(void){};
	Singleton(const Singleton&){};
	Singleton & operator= (const Singleton &){};
	
	static auto_ptr<T> _instance;
};


#define DECLARE_SINGLETON_CLASS(type) \
	friend class auto_ptr<type>; \
	friend class Singleton<type>;

#define IMPLEMENT_SINGLETON_CLASS(type)\
	auto_ptr<type> Singleton<type>::_instance;


class TestSingleton
{
public:
	void Run()
	{
		//do some thing
	}
private:
	TestSingleton(void){}
	virtual ~TestSingleton(void)
	{
		cout << "dtr \n" <<endl;
	}

	DECLARE_SINGLETON_CLASS(TestSingleton);
};


IMPLEMENT_SINGLETON_CLASS(TestSingleton);




class TestSingleton_  : public phony::singleton_manager<TestSingleton_>
{
		
public:
	void Run()
	{
		//do some thing
	}
	

	TestSingleton_()
	{
		cout << "ctr \n" << endl;
	}
	~TestSingleton_(void)
	{
		cout << "dtr \n" << endl;
	}

};



int _tmain(int argc, _TCHAR* argv[])
{
	

	TestSingleton_::instance()->Run();

	//Singleton<TestSingleton>::instance()->Run();

	return 0;
}

