#include "stdafx.h"
#include "ThreadPooledServer.h"
#include "CommonSocket.h"
#include "Log.h"



using namespace Framework;

#define LOG_NAME "ThreadPooledServer"


ThreadPooledServer::ThreadPooledServer(const std::string& address, const int port) :m_iServerPort(port)
{
	Net::InitNetwork();
	
	m_pPool = new TaskQueue;
	m_pPool->Start();



	m_bIsStopped = false;
}


ThreadPooledServer::~ThreadPooledServer()
{
	m_pPool->Stop();

	if (m_pPool != NULL)
	{
		delete m_pPool;
		m_pPool = NULL;
	}

	Net::UninitNetwork();
	Net::CloseSocket(m_ServerSocket);
}





bool ThreadPooledServer::IsStopped()
{
	return m_bIsStopped;
}



bool ThreadPooledServer::OpenServerSocket()
{
	
	m_ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	Net::SetSocketNoDelay(m_ServerSocket);
	Net::SetSocketReuseable(m_ServerSocket);
	Net::SetSocketBlock(m_ServerSocket);


	sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr("127.0.0.1");
	service.sin_port = htons(m_iServerPort);

	if (bind(m_ServerSocket, reinterpret_cast<sockaddr*>(&service), sizeof(sockaddr_in)) == INVALID_SOCKET)
	{
		CLog::GetInstance().LogError(LOG_NAME, "Failed to bind socket with error %s", Net::GetLastErrorStr(Net::GetSocketLastError()).c_str());
		return false;
	}


	if (listen(m_ServerSocket, SOMAXCONN) == INVALID_SOCKET)
	{
		CLog::GetInstance().LogError(LOG_NAME, "Failed to listen on socket  with error %s", Net::GetLastErrorStr(Net::GetSocketLastError()).c_str());
		return false;
	}

	return (m_ServerSocket != INVALID_SOCKET);
}