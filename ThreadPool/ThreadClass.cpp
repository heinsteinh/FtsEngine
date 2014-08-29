#include "stdafx.h"
#include "ThreadClass.h"
#include "Mutex.h"




DWORD Thread::threadProc(LPVOID data)
{
	Thread* thread = static_cast<Thread*>(data);
	thread->m_pRunnable->run();
	return 0;
}


Thread::Thread(IRunnable* r) :m_handle(NULL), m_threadId(-1), m_pRunnable(r)
{
	DWORD dwCreationFlags = CREATE_SUSPENDED;
	m_handle = ::CreateThread(NULL, 0, threadProc, this, dwCreationFlags, &m_threadId);
	if (m_handle == NULL)
		TRACE("CreateThread failed,for error:%d!", GetLastError());
}

void Thread::start()
{
	if (::ResumeThread(m_handle) == -1)
		TRACE("ResumeThread failed,for error:%d!", GetLastError());
}

void Thread::suspend()
{
	if (::SuspendThread(m_handle) == -1)
		TRACE("SuspendThread failed,for error:%d!", GetLastError());
}