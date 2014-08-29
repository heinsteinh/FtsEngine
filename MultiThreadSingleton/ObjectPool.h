#pragma once

#include "MemAlloc.h"

namespace XServer
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
	class ObjectPool : public core::CSingleton<ObjectPool<T> >
	{
		friend class core::CSingleton<ObjectPool<T> >;

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
	private:
		ObjectPoolImpl<T>* m_pImpl;
	};

	template<class T>
	class ObjectPoolWithLock
	{
	public:
		ObjectPoolWithLock()
			: m_pImpl(new ObjectPoolImpl<T>())
		{}

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

		void Push(T* p)
		{
			AutoLock lock(m_Mutex);
			m_pImpl->Push(p);
		}
	private:		
		typedef std::mutex Mutex;
		typedef std::unique_lock<std::mutex> ScopeLock;
	
		ObjectPoolImpl<T>* m_pImpl;
		Mutex m_Mutex;
	};
}