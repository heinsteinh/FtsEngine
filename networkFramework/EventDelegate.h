

#include "Buffer.h"
#include "event_delegate.h"

namespace network
{
	class Socket;
	class Operation;


	
	typedef P9927::Delegate<void(Socket* /*_socket*/, Buffer* /*_buffer*/, int /*_errorCode*/)> ReadHandler;
	typedef P9927::Delegate<void(Socket* /*_socket*/, Buffer* /*_buffer*/, int /*_errorCode*/)> WriteHandler;
	typedef P9927::Delegate<void(Socket* /*_socket*/, Buffer* /*_buffer*/, int /*_errorCode*/)> AcceptHandler;

	typedef P9927::Delegate<void(Operation* /*_operation*/, int /*_errorCode*/)> DestoryHandler;
	typedef P9927::Delegate<void(Socket* /*_socket*/)> BreakenHandler;



	//typedef Delegate<void(Socket* /*_socket*/, Buffer* /*_buffer*/, int /*_errorCode*/)> ReadHandler;
	//typedef Delegate<void(Socket* /*_socket*/, Buffer* /*_buffer*/, int /*_errorCode*/)> WriteHandler;
	//typedef Delegate<void(Socket* /*_socket*/, Buffer* /*_buffer*/, int /*_errorCode*/)> AcceptHandler;

	//typedef Delegate<void(Operation* /*_operation*/, int /*_errorCode*/)> DestoryHandler;
	//typedef Delegate<void(Socket* /*_socket*/)> BreakenHandler;
}