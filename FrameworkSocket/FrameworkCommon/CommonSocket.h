#ifndef __COMMON_SOCKET__
#define __COMMON_SOCKET__

#include "Compack.h"

namespace Net
{

	enum ConnectionType
	{
		TYPE_TCP,
		TYPE_UDP
	};

	bool	SetSocketReuseable(SOCKET hSocket);
	bool	SetSocketUnblock(SOCKET hSocket);
	bool	SetSocketBlock(SOCKET hSocket);
	bool	SetSocketNoDelay(SOCKET hSocket);
	bool	SetSocketKeepAlive(SOCKET hSocket, int keepInterval, int keepCount, int keepIdle);

	bool	InitNetwork();
	bool	UninitNetwork();


	SOCKET Connect(std::string address, unsigned short port, ConnectionType connectionType, int domain = AF_INET);
	SOCKET Listen(unsigned int port, ConnectionType connectionType, int domain = AF_INET);
	SOCKET Accept(SOCKET sock, sockaddr& addr);

	int Send(SOCKET sock, const char *data, size_t length, int iFlag=0);
	int Recv(SOCKET sock, char *data, size_t length, int iFlag = 0);
	
	
	int32_t	GetSocketLastError();
	bool	IsSocketValid(SOCKET hSocket);

	void	ShutDownSend(SOCKET hSocket);
	void	ShutDownRecv(SOCKET hSocket);

	void	CloseSocket(SOCKET hSocket);
	std::string GetLastErrorStr(INT32 nError);
	uint32_t	IpAddrStrToInt(CHAR *pszIpAddr);
	std::string IpAddrIntToStr(UINT32 dwIpAddr);

#ifdef WIN32
	bool	ConnectSocketEx(SOCKET hSocket, const char *pAddr, short sPort, LPOVERLAPPED lpOverlapped);
#endif

}
#endif /* __COMMON_SOCKET__*/