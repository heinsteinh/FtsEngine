#pragma once

#include "Delegate.h"
#include "Mutex.h"


#include <string>
#include <list>

template<typename T>
class ThreadPool
{
	struct Td
	{
		HANDLE Handle;
		DWORD ThreadId;
		int Index;
		bool Waiting;
		std::string Name;
		ThreadPool<T>* Owner;
	};

	std::list<delegate<T>*> m_works;
	
	Td* m_threads;
	int m_threadSize;
	mutex m_mutex;
	static DWORD WINAPI threadProc(LPVOID data);
	static void suspend(Td* thread);
	void wakeThread();
public:
	ThreadPool(int num);
	~ThreadPool();
	void add(delegate<T>* work);
	void start();
};




template<typename T>
DWORD ThreadPool<T>::threadProc(LPVOID data)
{
	Td* t = static_cast<Td*>(data);
	std::list<delegate<T>*>& works = t->Owner->m_works;
	mutex& mt = t->Owner->m_mutex;
	HANDLE handle = t->Handle;
	std::string& name = t->Name;

	delegate<T>* work;
	while (true)
	{
		mt.wait();
		if (works.empty())
			work = NULL;
		else
		{
			work = works.front();
			works.pop_front();
		}
		mt.notify();

		if (work)
			work->invoke();
		else
		{
			TRACE("%s wait\r\n", name.c_str());
			suspend(t);
		}
	}
	return 0;
}


template<typename T>
ThreadPool<T>::ThreadPool(int num):m_threads(NULL), m_threadSize(num)
{
	DWORD dwCreationFlags = CREATE_SUSPENDED;
	m_threads = new Td[num];
	for (int i = 0; i < num; ++i)
	{
		char buffer[1024];
		sprintf_s(buffer, 1024, "Thread_%08X_%d", this, i);
		m_threads[i].Name.append(buffer);
		m_threads[i].Index = i;
		m_threads[i].Owner = this;
		m_threads[i].Waiting = true;

		m_threads[i].Handle = ::CreateThread(NULL, 0, threadProc, &m_threads[i], dwCreationFlags, &m_threads[i].ThreadId);	
		if (m_threads[i].Handle == NULL)
			TRACE("CreateThread[i] failed,for error:%d!", i, GetLastError());
	}
}
template<typename T>
ThreadPool<T>::~ThreadPool()
{
	if (m_threads)
	{
		delete[] m_threads;
		m_threads = NULL;
	}
}


template<typename T>
void ThreadPool<T>::start()
{
	for (int i = 0; i < m_threadSize; ++i)
	{
		if (::ResumeThread(m_threads[i].Handle) == -1)
		{
			TRACE("ResumeThread[%d] failed,for error:%d!\r\n", i, GetLastError());
			return;
		}
		TRACE("ResumeThread[%s] success!\r\n", m_threads[i].Name.c_str());
		m_threads[i].Waiting = false;
	}
}

template<typename T>
void ThreadPool<T>::suspend(Td* thread)
{
	thread->Waiting = true;
	TRACE("SuspendThread[%s] success!\r\n", thread->Name.c_str());
	if (::SuspendThread(thread->Handle) == -1)
	{
		thread->Waiting = false;
		TRACE("SuspendThread[%s] failed,for error:%d!\r\n", thread->Name.c_str(), GetLastError());
		return;
	}

}
template<typename T>
void ThreadPool<T>::add(delegate<T>* work)
{
	m_mutex.wait();
	m_works.push_back(work);

	TRACE("add work:%08X\r\n", work);

	m_mutex.notify();
	wakeThread();
}


template<typename T>
void ThreadPool<T>::wakeThread()
{
	for (int i = 0; i < m_threadSize; ++i)
	{
		if (m_threads[i].Waiting)
		{
			if (::ResumeThread(m_threads[i].Handle) == -1)
			{
				TRACE("ResumeThread[%s] failed,for error:%d!\r\n", m_threads[i].Name.c_str(), GetLastError());
				continue;
			}
			TRACE("ResumeThread[%s] success!\r\n", m_threads[i].Name.c_str());
			m_threads[i].Waiting = false;
		}
	}
}