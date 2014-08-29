
#pragma once 

namespace core
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