#pragma once
#include <exception>
#include <string>

namespace Framework
{
	class SocketException : public std::exception
	{
	public:
		SocketException(const std::string& msg);
		SocketException(const std::string& msg, int errorCode);
		inline virtual const char* what() const override { return msg.c_str(); }
		const int errorCode = 0;
	private:
		std::string msg;
		inline SocketException& operator=(const SocketException&);
	};
	class NetworkProtocolException : public SocketException
	{
	public:
		NetworkProtocolException(const std::string& msg);
		NetworkProtocolException(const std::string& msg, int errorCode);
	};
}
