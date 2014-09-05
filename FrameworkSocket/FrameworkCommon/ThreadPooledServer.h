
#pragma once

#include "Compack.h"
#include "ThreadBase.h"
#include "TaskQueue.h"

#include <string>


namespace Framework
{
	class ThreadPooledServer : public Runnable
	{

	protected:
		int						m_iServerPort = 8080;
		SOCKET				m_ServerSocket ;
		bool					m_bIsStopped ;
		//Thread*				m_pRunningThread;
		int						m_iThreadCount;

		TaskQueue*		m_pPool;

	public:
		ThreadPooledServer(const std::string& address, const int port, int iThreadCount = 3);
		~ThreadPooledServer();
		
		
		bool IsStopped();


	protected:
		bool OpenServerSocket();

	};

}
