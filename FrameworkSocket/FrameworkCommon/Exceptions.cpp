
#include "Exceptions.h"
#include "CommonSocket.h"
#include "Log.h"

namespace Framework
{
	SocketException::SocketException(const std::string& msg) : SocketException(msg,  Net::GetSocketLastError()) { }
	SocketException::SocketException(const std::string& msg, int errorCode) : errorCode(errorCode)
	{
		this->msg = msg;

		this->msg += Net::GetLastErrorStr(errorCode);
	
		CLog::GetInstance().LogDebug("SocketException", " %s ", msg.c_str());		
	}

	NetworkProtocolException::NetworkProtocolException(const std::string& msg) : SocketException(msg) { }
	NetworkProtocolException::NetworkProtocolException(const std::string& msg, int errorCode) : SocketException(msg, errorCode) { }
}