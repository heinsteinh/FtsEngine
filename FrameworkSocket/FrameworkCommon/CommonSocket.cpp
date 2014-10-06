
#include "CommonSocket.h"
#include "Log.h"


bool Net::SetSocketReuseable(SOCKET hSocket)
{
	char nReuse = 1;
	if (0 != setsockopt(hSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&nReuse, sizeof(int)))
	{
		return false;
	}
	return true;
}


bool Net::SetSocketUnblock(SOCKET hSocket)
{
#ifdef WIN32
	u_long iMode = 1;
	ioctlsocket(hSocket, FIONBIO, &iMode);
#else
	int flags = fcntl(hSocket, F_GETFL, 0);
	fcntl(hSocket, F_SETFL, flags | O_NONBLOCK);
#endif
	return true;
}


bool Net::SetSocketBlock(SOCKET hSocket)
{
#ifdef WIN32
	u_long iMode = 0;
	ioctlsocket(hSocket, FIONBIO, &iMode);
#else
	int flags = fcntl(hSocket, F_GETFL, 0);
	fcntl(hSocket, F_SETFL, flags & (~O_NONBLOCK));
#endif
	return true;
}

bool Net::SetSocketNoDelay(SOCKET hSocket)
{
	int bOn = 1;
	if (0 != setsockopt(hSocket, IPPROTO_TCP, TCP_NODELAY, (char*)&bOn, sizeof(bOn)))
	{
		return false;
	}
	return true;
}


bool Net::InitNetwork()
{
#if WIN32
	WSADATA wsaData;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		return false;
	}
#endif
	return true;
}

bool Net::UninitNetwork()
{
#if WIN32
	return (0 == WSACleanup());
#endif
	return true;
}


void Net::CloseSocket(SOCKET hSocket)
{
#ifdef WIN32
	closesocket(hSocket);
#else
	close(hSocket);
#endif
}

void Net::ShutDownSend(SOCKET hSocket)
{
	shutdown(hSocket, 0);
}

void Net::ShutDownRecv(SOCKET hSocket)
{
	shutdown(hSocket, 1);
}




uint32_t Net::IpAddrStrToInt(CHAR *pszIpAddr)
{
	sockaddr_in SvrAddr;
	inet_pton(AF_INET, pszIpAddr, &SvrAddr.sin_addr);
	return SvrAddr.sin_addr.s_addr;
}



std::string Net::IpAddrIntToStr(UINT32 dwIpAddr)
{
	in_addr Addr;
	Addr.s_addr = dwIpAddr;
	CHAR szIpBuffer[20] = { 0 };
	inet_ntop(AF_INET, &Addr, szIpBuffer, 20);
	return std::string(szIpBuffer);
}


int32_t Net::GetSocketLastError()
{
#ifdef WIN32
	return WSAGetLastError();
#else
	return errno;
#endif
}


std::string Net::GetLastErrorStr(uint32_t nError)
{
	std::string msg;
	msg += (" with error " + std::to_string(nError) + ": ");

#ifdef WIN32

	LPSTR lpMsgBuf = NULL;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, nError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);

	FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, nError, 0, (LPSTR)&lpMsgBuf, 0, NULL);
	msg += lpMsgBuf;

	LocalFree(lpMsgBuf);
#else
	msg = strerror(nError);
#endif


//	std::wstring strErrorText;
//#ifdef WIN32
//	LPVOID lpMsgBuf;
//	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, nError,
//		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
//	strErrorText = (LPTSTR)lpMsgBuf;
//	LocalFree(lpMsgBuf);
//#else
//	strErrorText = strerror(nError);
//#endif
//		std::string str((const char*)&strErrorText[0], sizeof(wchar_t) / sizeof(char)*strErrorText.size());		
//		//std::string str_v(strErrorText.begin(), strErrorText.end());

		return msg;
}



bool Net::SetSocketKeepAlive(SOCKET hSocket, int keepInterval, int keepCount, int keepIdle)
{
	bool bKeepAlive = true;

#ifdef WIN32
	setsockopt(hSocket, SOL_SOCKET, SO_KEEPALIVE, (char*)&bKeepAlive, sizeof(bKeepAlive));
#else

//	setsockopt(hSocket, SOL_TCP, TCP_KEEPIDLE, (void *)&keepIdle, sizeof(keepIdle));
//	setsockopt(hSocket, SOL_TCP, TCP_KEEPINTVL, (void *)&keepInterval, sizeof(keepInterval));
//	setsockopt(hSocket, SOL_TCP, TCP_KEEPCNT, (void *)&keepCount, sizeof(keepCount));
#endif

	return true;
}



namespace Net
{
	SOCKET Connect(std::string address, unsigned short port, ConnectionType connectionType, int domain)
	{
		// Prepare type
		int type;
		if (connectionType == TYPE_TCP)
		{
			type = SOCK_STREAM;
		}
		else if (connectionType == TYPE_UDP)
		{
			type = SOCK_DGRAM;
		}
		else
		{
			return -1;
		}
		// Prepare address struct
		if (domain != AF_INET)
		{
			// Other domains are not supported yet
			return -1;
		}
		sockaddr_in addr;
		memset(&addr, 0, sizeof(addr));
		// Resolve address
		unsigned long ip_addr;
		if ((ip_addr = inet_addr(address.c_str())) != INADDR_NONE)
		{
			memcpy((char*)&addr.sin_addr, &ip_addr, sizeof(ip_addr));
		}
		else
		{
			// For localhost etc.
			hostent *host_info = gethostbyname(address.c_str());
			if (host_info == NULL)
			{
				Framework::CLog::GetInstance().LogError("Net::GetLastErrorStr", "Unknown host: %s ", address.c_str());				
				return -1;
			}
			memcpy(&addr.sin_addr, host_info->h_addr, host_info->h_length);
		}
		addr.sin_family = domain;
		addr.sin_port = htons(port);
		// Create socket
		int sock = socket(domain, type, 0);
		if (sock < 0)
		{
			return -1;
		}
		// Connect
		if (::connect(sock, (sockaddr*)&addr, sizeof(addr)) < 0)
		{
			CloseSocket(sock);
			return -1;
		}
		else
		{
			return sock;
		}
	}

	int Send(SOCKET sock, const char *data, size_t length, int iFlag)
	{
		return ::send(sock, data, length, iFlag);
	}
	
	int Recv(SOCKET sock, char *data, size_t length, int iFlag )
	{
		return ::recv(sock, data, length, iFlag);
	}

	SOCKET Listen(unsigned int port, ConnectionType connectionType, int domain)
	{
		// Prepare type
		int type;
		if (connectionType == TYPE_TCP)
		{
			type = SOCK_STREAM;
		}
		else if (connectionType == TYPE_UDP)
		{
			type = SOCK_DGRAM;
		}
		else
		{
			return -1;
		}
		// Prepare address struct
		if (domain != AF_INET)
		{
			// Other domains are not supported yet
			return -1;
		}
		sockaddr_in addr;
		memset(&addr, 0, sizeof(addr));
		addr.sin_family = domain;
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
		addr.sin_port = htons(port);
		// Create socket
		int sock = socket(domain, type, 0);
		if (sock < 0)
		{
			return -1;
		}
		// Bind
		if (bind(sock, (sockaddr*)&addr, sizeof(addr)) < 0)
		{
			CloseSocket(sock);
			return -1;
		}
		// Listen
		if (::listen(sock, 5) < 0)
		{
			CloseSocket(sock);
			return -1;
		}
		return sock;
	}


	SOCKET accept(SOCKET sock, sockaddr& addr)
	{
		socklen_t len = sizeof(addr);
		return ::accept(sock, &addr, &len);
	}
};
