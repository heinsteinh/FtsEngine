// networkFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include "Lib.h"



#include <thread>


#include "event_delegate.h"



#include "PeerAddr.h"
#include "Socket.h"



int increment(int& itest)
{
	return itest;
}



int _tmain(int argc, _TCHAR* argv[])
{
	
	network::PeerAddr pPeerAddr("127.0.0.1", 8080); 
	network::Socket* pSocket = new network::Socket();
	
	pSocket->SetPeerAddr(pPeerAddr);





	system("pause");

	return 0;
}

