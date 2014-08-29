#pragma once

#include "MemAlloc.h"
//https://github.com/codinghao/XServer/blob/f8e7a2a6e08537cfe7204068adf1f7e29f72e052/GameFrame/src/Common/MemAlloc.h

namespace tin
{

	template<class T>
	class ObjectPoolImpl
	{
	public:
		ObjectPoolImpl()
		{}

		virtual ~ObjectPoolImpl()
		{}

		T* Pop()
		{
			T* pObj = (T*)MemAllocT.Alloc(sizeof(T));
			pObj = new(pObj)T();
			return pObj;
		}

		template<class Arg1>
		T* Pop(Arg1 p1)
		{
			T* pObj = (T*)MemAllocT.Alloc(sizeof(T));
			pObj = new(pObj)T(p1);
			return pObj;
		}

		template<class Arg1, class Arg2>
		T* Pop(Arg1 p1, Arg2 p2)
		{
			T* pObj = (T*)MemAllocT.Alloc(sizeof(T));
			pObj = new(pObj)T(p1, p2);
			return pObj;
		}

		template<class Arg1, class Arg2, class Arg3>
		T* Pop(Arg1 p1, Arg2 p2, Arg3 p3)
		{
			T* pObj = (T*)MemAllocT.Alloc(sizeof(T));
			pObj = new(pObj)T(p1, p2, p3);
			return pObj;
		}

		template <class... Args> 
		T* Pop(Args&&... args)
		{
			T* pObj = (T*)MemAllocT.Alloc(sizeof(T));
			pObj = new(pObj)T(std::forward<Args>(args)...);
			return pObj;
		}		


		template< class... Args>
		std::shared_ptr<T>	PopShared(Args&&... args)
		{
			T* pObj = (T*)MemAllocT.Alloc(sizeof(T));
			pObj = new(pObj)T(std::forward<Args>(args)...);

			return std::shared_ptr<T>(pObj, std::bind(&ObjectPoolImpl::Push, this, std::placeholders::_1));
		}


		void Push(T* p)
		{
			if (p != NULL)
			{
				p->~T();
				MemAllocT.Dealloc((void*)p, sizeof(T));
			}
		}
	};

	template<class T>
	class ObjectPool : public CSingleton<ObjectPool<T> >
	{
		friend class CSingleton<ObjectPool<T> >;

	public:
		ObjectPool()
			: m_pImpl(new ObjectPoolImpl<T>())
		{}

		~ObjectPool()
		{
			if (m_pImpl != NULL)
				delete m_pImpl;
			m_pImpl = NULL;
		}

		T* Pop() { return m_pImpl->Pop(); }
		void Push(T* p) { m_pImpl->Push(p); }

		template <class... Args>
		T* Pop(Args&&... args) { return m_pImpl->Pop(std::forward<Args>(args)...); }

		template<class... Args>
		std::shared_ptr<T>	PopShared(Args&&... args){ return m_pImpl->PopShared(std::forward<Args>(args)...); }

	private:
		ObjectPoolImpl<T>* m_pImpl;
	};



	template<class T>
	class ObjectPoolWithLock : public CSingleton<ObjectPoolWithLock<T> >
	{
		friend class CSingleton<ObjectPoolWithLock<T> >;

	public:
		ObjectPoolWithLock() : m_pImpl(new ObjectPoolImpl<T>()){}

		~ObjectPoolWithLock()
		{
			if (m_pImpl != NULL)
				delete m_pImpl;
			m_pImpl = NULL;
		}

		T* Pop()
		{
			ScopeLock lock(m_Mutex);
			return m_pImpl->Pop();
		}

		template<class Arg1>
		T* Pop(Arg1 p1)
		{
			ScopeLock lock(m_Mutex);
			return m_pImpl->Pop(p1);
		}

		template<class Arg1, class Arg2, class Arg3>
		T* Pop(Arg1 p1, Arg2 p2, Arg3 p3)
		{
			ScopeLock lock(m_Mutex);
			return m_pImpl->Pop(p1, p2, p3);
		}

		template<class Arg1, class Arg2>
		T* Pop(Arg1 p1, Arg2 p2)
		{
			ScopeLock lock(m_Mutex);
			return m_pImpl->Pop(p1, p2);
		}


		template <class... Args>
		T* Pop(Args&&... args){
			ScopeLock lock(m_Mutex);
			return m_pImpl->Pop(std::forward<Args>(args)...);
		}


		template<class... Args>
		std::shared_ptr<T>	PopShared(Args&&... args){
			ScopeLock lock(m_Mutex);
			return m_pImpl->PopShared(std::forward<Args>(args)...);
		}


		void Push(T* p)
		{
			ScopeLock lock(m_Mutex);
			m_pImpl->Push(p);
		}
	private:
		typedef std::mutex Mutex;
		typedef std::unique_lock<std::mutex> ScopeLock;

		ObjectPoolImpl<T>* m_pImpl;
		Mutex m_Mutex;
	};
}