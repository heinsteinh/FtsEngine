#include "stdafx.h"
#include "MutexHelper.h"



using namespace std;
using namespace Framework;

std::mutex MutexHelper::m_iListMutex;
bool MutexHelper::inited = false;
map<std::mutex*, MutexState> MutexHelper::m_mList;

void MutexHelper::Init()
{
	//pthread_mutex_init(&m_iListMutex, NULL);
	inited = true;
}

MutexHelper::MutexHelper(std::mutex *p_piMutex)
{
	if (!inited)
	{
		Init();
	}
	
	m_iListMutex.lock();
	
	m_piMutex = p_piMutex;
	if (m_mList.find(m_piMutex) != m_mList.end() && (std::this_thread::get_id() == m_mList[m_piMutex].m_iThread))		
	{
		// Our lock, just increase counter
		m_mList[m_piMutex].m_iLocks++;
	}
	else
	{
		// Not our lock or not locked yet, lock and set
		m_piMutex->lock();
		m_mList[m_piMutex].m_iThread = std::this_thread::get_id(); // pthread_self();
		m_mList[m_piMutex].m_iLocks = 1;
	}

	m_iListMutex.unlock();
	
}


MutexHelper::~MutexHelper()
{


	m_iListMutex.lock();
		
	m_mList[m_piMutex].m_iLocks--;
	if (m_mList[m_piMutex].m_iLocks == 0)
	{
		m_piMutex->unlock();		
		m_mList.erase(m_piMutex);
	}
	m_iListMutex.unlock();
	
}