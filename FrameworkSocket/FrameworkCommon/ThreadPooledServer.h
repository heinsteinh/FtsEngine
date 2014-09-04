
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


		TaskQueue*		m_pPool;

	public:
		ThreadPooledServer(const std::string& address, const int port);
		~ThreadPooledServer();
		
		
		bool IsStopped();


	protected:
		bool OpenServerSocket();

	};

}
