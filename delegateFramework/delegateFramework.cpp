// delegateFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <iostream>
using namespace std;


#include <thread>
#include <list>
#include <cassert>
#include <set>



//http://blog.coldflake.com/posts/2014-01-12-C++-delegates-on-steroids.html
//https://github.com/yngccc/P9927/blob/5a0919ce44747ba72c40f4c2d58eaf9011f443b5/src/lib/event_delegate.h

//https://github.com/xaxaxa/workspace/blob/e50a35a0bbd230db80110007e34f04619069dc20/cplib/headers/cplib.hpp

namespace event_ftr
{
	template <typename FuncSignature>
	class Delegate;

	template <typename FuncSignature>
	class Event;

	template <typename R, typename... Args>
	class Delegate<R(Args...)>
	{
		using FuncType = R(*)(const void*, Args...);

		FuncType func_ = nullptr;
		const void* obj_ = nullptr;

		Delegate(FuncType func, const void* obj) : func_(func), obj_(obj)
		{
		}

		template <typename FR, typename... FArgs>
		friend class FreeDelegateFactory;
		template <typename FR, class FT, typename... FArgs>
		friend class MemberDelegateFactory;
		template <typename FR, class FT, typename... FArgs>
		friend class ConstMemberDelegateFactory;

	public:
		Delegate() = default;

		R operator()(Args... args) const {
			return (*func_)(obj_, args...);
		}

		bool operator==(const Delegate& other) const{
			return (obj_ == other.obj_) && (func_ == other.func_);
		}

	};

	template <typename R, typename... Args>
	class FreeDelegateFactory {
		template <R(*Func)(Args...)>
		static R Wrapper(const void*, Args... args) {
			return (*Func)(args...);
		}

	public:
		template <R(*Func)(Args...)>
		static Delegate<R(Args...)> bind() {
			return Delegate<R(Args...)>(&FreeDelegateFactory::Wrapper<Func>, nullptr);
		}
	};

	template <typename R, typename... Args>
	FreeDelegateFactory<R, Args...> GetDelegateFactory(R(*)(Args...)) {
		return FreeDelegateFactory<R, Args...>();
	}

	template <typename R, class T, typename... Args>
	class MemberDelegateFactory {
		template <R(T::*Func)(Args...)>
		static R Wrapper(const void* o, Args... args) {
			T* obj = const_cast<T*>(static_cast<const T*>(o));
			return (obj->*Func)(args...);
		}

	public:
		template <R(T::*Func)(Args...)>
		static Delegate<R(Args...)> bind(T* o) {
			return Delegate<R(Args...)>(&MemberDelegateFactory::Wrapper<Func>,
				static_cast<const void*>(o));
		}
	};

	template <typename R, class T, typename... Args>
	MemberDelegateFactory<R, T, Args...> GetDelegateFactory(R(T::*)(Args...)) {
		return MemberDelegateFactory<R, T, Args...>();
	}

	template <typename R, class T, typename... Args>
	class ConstMemberDelegateFactory {
		template <R(T::*Func)(Args...) const>
		static R Wrapper(const void* o, Args... args) {
			const T* obj = static_cast<const T*>(o);
			return (obj->*Func)(args...);
		}

	public:
		template <R(T::*Func)(Args...) const>
		static Delegate<R(Args...)> bind(const T* o) {
			return Delegate<R(Args...)>(&ConstMemberDelegateFactory::Wrapper<Func>,
				static_cast<const void*>(o));
		}
	};

	template <typename R, class T, typename... Args>
	ConstMemberDelegateFactory<R, T, Args...> GetDelegateFactory(R(T::*)(Args...) const) {
		return ConstMemberDelegateFactory<R, T, Args...>();
	}


	template <typename R, typename... Args>
	class Event<R(Args...)> {

		std::list<Delegate<R(Args...)>> delegate_list_;

		friend class Delegate<R(Args...)>;

	public:
		/** linear time complexity */
		int num_delegates() const {
			return delegate_list_.size();
		}

		void operator()(Args... args) const {
			for (auto& delegate : delegate_list_)
				delegate(args...);
		}

		void operator+=(Delegate<R(Args...)>& delegate_)
		{
			for (std::list<Delegate<R(Args...)>>::iterator iter = delegate_list_.begin(); iter != delegate_list_.end(); ++iter)
			{
				if ((*iter) == (delegate_))
					return;
			}

			delegate_list_.push_back(delegate_);
		}

		void operator-=(Delegate<R(Args...)>& delegate_)
		{
			std::list<Delegate<R(Args...)>>::iterator whereToRemove;
			for (std::list<Delegate<R(Args...)>>::iterator iter = delegate_list_.begin(); iter != delegate_list_.end(); ++iter)
			{
				if ((*iter) == (delegate_))
				{
					whereToRemove = iter;
					break;
				}
			}
			delegate_list_.erase(whereToRemove);
		}


		void clear() {
			delegate_list_.clear();
		}


		~Event(){ clear(); }
	};

#ifdef BIND_FREE
#undef BIND_FREE
#endif

#ifdef BIND_METHOD_OBJ
#undef BIND_METHOD_OBJ
#endif

#ifdef BIND_METHOD
#undef BIND_METHOD
#endif

#define BIND_FREE(freeFuncPtr) \
	(core::GetDelegateFactory(freeFuncPtr).bind<freeFuncPtr>())

#define BIND_METHOD_OBJ(memFuncPtr, instancePtr) \
	(core::GetDelegateFactory(&memFuncPtr).bind<&memFuncPtr>(&instancePtr))

#define BIND_METHOD(memFuncPtr) \
	(core::GetDelegateFactory(&memFuncPtr).bind<&memFuncPtr>(this))



}









using namespace std;
namespace xaxaxa
{
	//typedef void* Function;

	typedef volatile int atomic_t;
#define atomic_read(v) v
#define atomic_set(v,i) v = i
#define atomic_add(i,v) v += i
#define atomic_sub(i,v) v -= i
#define atomic_sub_and_test(i,v) (v -= i) == 0
#define atomic_inc(v) v++
#define atomic_dec(v) v--
#define atomic_dec_and_test(v) --v == 0
#define atomic_inc_and_test(v) ++v == 0
#define atomic_add_negative(i,v) (v += i) < 0

	template<class SIGNATURE> struct Delegate;
	template<class RET, class ... ARGS> struct Delegate<RET(ARGS...)>
	{
		virtual RET operator()(ARGS...) = 0;
	};

		//for the following 3 function wrapper classes, if they are initialized
		//with the default constructor(without any parameters), calling the object
		//results in undefined behavior
		template<class SIGNATURE> struct StaticFunction;
		template<class RET, class ... ARGS> struct StaticFunction<RET(ARGS...)> : public Delegate<
			RET(ARGS...)>
		{
			RET(*func)(ARGS...);
			virtual RET operator()(ARGS&& ... a)
			{
				return func(std::forward<ARGS...>(a...));
			}
			StaticFunction(RET(*func)(ARGS...)) :
				func(func)
			{
			}
			StaticFunction()
			{
			}
		};

		template<class SIGNATURE> struct MemberFunction;
		template<class RET, class ... ARGS> struct MemberFunction<RET(ARGS...)> : public Delegate<RET(ARGS...)>
		{
			RET(*func)(void*, ARGS...);
			void* this_ptr;
			virtual RET operator()(ARGS&& ... a)
			{
				return func(this_ptr, std::forward<ARGS...>(a...));
			}
			template<class c> MemberFunction(RET(c::*func)(ARGS...), c* obj)
				//:func((RET (*)(void*, ARGS...))func), this_ptr(obj)
			{
				this->func = (RET(*)(void*, ARGS...))func; this->this_ptr = obj;
			}
			MemberFunction()
			{}
		};

		//uncomment to allow hybrid functions to distinguish between (a member
		//function pointer with a NULL thisptr) and (a static function).
		//this adds overhead.
		#define XAXAXA_FUNCTION_ALLOW_NULL_THISPTR

		template<class SIGNATURE> struct Function;
		template<class RET, class ... ARGS> struct Function<RET(ARGS...)> : public Delegate<RET(ARGS...)>
		{
			//RET (*func)(void*, ARGS...);
			void* func;
			void* this_ptr;
#ifdef XAXAXA_FUNCTION_ALLOW_NULL_THISPTR
			bool is_mem_func;
#endif
			virtual RET operator()(ARGS&& ... a)
			{
#ifdef XAXAXA_FUNCTION_ALLOW_NULL_THISPTR
				if (is_mem_func)
					return ((RET(*)(void*, ARGS...))func)(this_ptr, a...);
				else
					return ((RET(*)(ARGS...))func)(a...);
#endif
				if (this_ptr != NULL)
					return ((RET(*)(void*, ARGS...)) func)(this_ptr, std::forward<ARGS...>(a...));
				else
					return ((RET(*)(ARGS...)) func)(std::forward<ARGS...>(a...));
			}
			template<class c> Function(RET(c::*func)(ARGS...), c* obj) : func((void*)func), this_ptr(obj)
			{
#ifdef XAXAXA_FUNCTION_ALLOW_NULL_THISPTR
				this->is_mem_func = true;
#endif
			}
			Function(RET(*func)(ARGS...)) :func((void*)func)
			{
#ifdef XAXAXA_FUNCTION_ALLOW_NULL_THISPTR
				this->is_mem_func = false;
#else
				this->this_ptr = NULL;
#endif
			}
			Function()
			{
			}
		};
			template<class SIGNATURE> struct FunctionWrapper
				;
			template<class RET, class ... ARGS> struct FunctionWrapper<RET(ARGS...)>
			{
				function<RET(ARGS...)> func;
				typedef RET(*func_t)(void*, ARGS...);
				FunctionWrapper(const function<RET(ARGS...)>& f) :
					func(f)
				{
				}
				RET operator()(ARGS&& ... a)
				{
					return func(std::forward<ARGS...>(a...));
				}
				func_t Get()
				{
					return (func_t)&FunctionWrapper<RET(ARGS...)>::operator();
				}
			};




				/********************************************************************************/
				/*
				/********************************************************************************/
#define FUNCTION_DECLARE(NAME,RETVAL,...) \
				struct NAME; struct NAME{\
				std::function<RETVAL(void*, __VA_ARGS__)> f; \
				void* obj; int __id; \
				template<class FGSAFJGFJSA>inline NAME(RETVAL(FGSAFJGFJSA::*f)(__VA_ARGS__), void* obj)\
				{__id = rand(); this->f = reinterpret_cast<RETVAL(*)(void*, __VA_ARGS__)>((void*)f); \
				this->obj = obj; }\
				inline NAME(RETVAL(*f)(void*, __VA_ARGS__))\
				{__id = rand(); this->f = reinterpret_cast<RETVAL(*)(void*, __VA_ARGS__)>((void*)f); \
				this->obj = NULL; }\
				inline NAME(const std::function<RETVAL(void*, __VA_ARGS__)>& func)\
				{__id = rand(); f = func; \
				this->obj = NULL; }\
				inline NAME(const std::function<RETVAL(void*, __VA_ARGS__)>& func, void* obj)\
				{__id = rand(); f = func; \
				this->obj = obj; }\
				inline NAME(){}\
				static NAME null; \
				bool operator<(const NAME& X) const\
				{return __id>X.__id; }\
				}

#define FUNCTION_DECLWRAPPER(NAME,RETVAL,...) static inline RETVAL NAME(void* obj,__VA_ARGS__)
#define FUNCTION_CALL(FUNC,...) (FUNC).f((FUNC).obj,__VA_ARGS__)
#define DELEGATE(RETVAL,NAME,...) FUNCTION_DECLARE(NAME,RETVAL,__VA_ARGS__)
#define CALL FUNCTION_CALL



				class Object
				{
				public:

					atomic_t RefCount; //reference counter
					Object()
					{
						RefCount = 1;
#ifdef __debug_obj123
						objs++;
						cout << "construct<" << typeid(*this).name() << ">; " << objs << " objects total" << endl;
#endif
					}
					Object(const Object& other)
					{
						RefCount = 1;
					}
					virtual ~Object()
					{
#ifdef __debug_obj123
						objs--;
						cout << "destruct<" << typeid(*this).name() << ">; " << objs << " objects total" << endl;
#endif
					}
					inline void RefCount_inc()
					{
						atomic_inc(RefCount);
#ifdef __debug_obj123
						cout << "retain<" << typeid(this).name() << "> = " << RefCount << "; " << objs << " objects total" << endl;
#endif
					}
					inline void RefCount_dec()
					{
						atomic_dec(RefCount);
#ifdef __debug_obj123
						cout << "release<" << typeid(this).name() << "> = " << RefCount << "; " << objs << " objects total" << endl;
#endif
						//dbgprint("refcount=" << RefCount);
						if (RefCount <= 0) {
							delete this;
							//cout << o;
						}
					}
					inline void Release()
					{
						RefCount_dec();
					}
					virtual string ToStr() const
					{
						return string(typeid(*this).name());
					}
					Object& operator=(const Object& other)
					{
						//RefCount = 1;
						return *this;
					}
				};

				template<class T>
				class _Event : public Object
				{
				public:
					std::set<T> handlers;
					typedef typename set<T>::iterator iter;

					inline void addhandler(T delegate)
					{
						handlers.insert(delegate);
					}
					inline void removehandler(T delegate)
					{
						handlers.erase(delegate);
					}
					inline void operator+=(T delegate)
					{
						addhandler(delegate);
					}
					inline void operator-=(T delegate)
					{
						removehandler(delegate);
					}
				};


#define EVENT(DEL) _Event<DEL>

#define RAISEEVENT(NAME,...) \
				{\
				for (auto gjfdjdsghddjh = (NAME).handlers.begin(); gjfdjdsghddjh != (NAME).handlers.end(); gjfdjdsghddjh++)\
				{CALL((*gjfdjdsghddjh), __VA_ARGS__); }}

#define ADDHANDLER(NAME,DEL) (NAME).addhandler(DEL)
#define REMOVEHANDLER(NAME,DEL) (NAME).removehandler(DEL)

}

using namespace event_ftr;


class MyClass
{
public:
	MyClass()
	{
	}

	~MyClass()
	{
	}
	
	FUNCTION_DECLARE(OnChangeEvent, void, int, int);
	
	

private:

};


//these functions are in a separately compiled shared library to avoid inlining

const int iterations = 5000;

using namespace event_ftr;
void call100times(event_ftr::Delegate<void()> d) {
	for (int i = 0; i<100; i++)
		d();
}
void call100times_i(event_ftr::Delegate<void(int)> d) {
	for (int i = 0; i<100; i++)
		d(i);
}

void call100times(function<void()>& d) {
	for (int i = 0; i<100; i++)
		d();
}
void call100times_i(function<void(int)>& d) {
	for (int i = 0; i<100; i++)
		d(i);
}

void call100000times(event_ftr::Delegate<void()> d) {
	for (int i = 0; i<100000; i++)
		d();
}
void call100000times_i(event_ftr::Delegate<void(int)> d) {
	for (int i = 0; i<100000; i++)
		d(i);
}

void call100000times(function<void()>& d) {
	for (int i = 0; i<100000; i++)
		d();
}
void call100000times_i(function<void(int)>& d) {
	for (int i = 0; i<100000; i++)
		d(i);
}

void call100000times(void(*d)()) {
	for (int i = 0; i<100000; i++)
		d();
}
void call100000times_i(void(*d)(int)) {
	for (int i = 0; i<100000; i++)
		d(i);
}



//for C function ptrs
int X;
void Func(int i) {
	X += i;
}


using namespace std;
using namespace xaxaxa;
class a
{
public:
	DELEGATE(void, mydelegate, int, int);
	EVENT(mydelegate) event1;

	void raise(int x, int y)
	{
		RAISEEVENT(event1, x, y);
		RAISEEVENT(event1, y, x);
	}
};

class b
{
public:
	void handler1(int x, int y)
	{
		cout << "handler1 called x=" << x << "; y=" << y << endl;
	}
};

class c
{
public:
	int z;
	void handler2(int x, int y)
	{
		cout << "handler2 called x=" << x << "; y=" << y << "; z=" << z << endl;
	}
};

void handler3(void* user, int x, int y)
{
	cout << "handler3 called x=" << x << "; y=" << y << endl;
}

struct foo
{
	void bar(int v, int p) { std::cout << "foo::bar - " << v << p << '\n'; }
};

int _tmain(int argc, _TCHAR* argv[])
{

	foo my_foo;

	auto f1 = std::bind(&foo::bar, my_foo, 1, 2);
	auto f2 = std::bind(&foo::bar, &my_foo, 2, std::placeholders::_1);

	f1();
	f2(2);


	a a1;
	b b1;
	c c1;
	c1.z = 678;
	

	
	ADDHANDLER(a1.event1, a::mydelegate(std::bind(&b::handler1, &b1, std::placeholders::_2, std::placeholders::_3)));	
	ADDHANDLER(a1.event1, a::mydelegate(std::bind(&c::handler2, &c1, std::placeholders::_2, std::placeholders::_3)));
	ADDHANDLER(a1.event1, a::mydelegate(&handler3, NULL));



	
	a1.raise(12, 345);



	for (int i = 0; i<iterations * 1000; i++) 
	{
		int x = 0;
		std::function<void(int)> func = [&x](int i) 
		{
			x += i;
		};
		
		call100times_i(func);
	}
	printf("done.\n");

	//ADDHANDLER(a1.event1, a::mydelegate(&c::handler2, &c1));
	//ADDHANDLER(a1.event1, a::mydelegate(&handler3, NULL));
	//a1.raise(12, 345);
	
	

	getchar();
	return 0;
}

