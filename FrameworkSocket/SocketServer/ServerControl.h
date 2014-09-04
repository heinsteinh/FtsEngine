#pragma once



#include <thread>
#include <vector>


#include "../FrameworkCommon/PacketUtils.h"


#include <condition_variable>
#include <csignal>
#include <cstdio>
#include <chrono>
#include <cstring>
#include <ctime>
#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <vector>
#include <sstream>
#include <queue>




namespace Framework
{
	class BlockSocket;
};


//
///**
//* Used by the kick command to check if given password exists in the list.
//*/
//class PasswordManager {
//public: 
//	PasswordManager(const char* file) : passwords_file{ file }	{	};
//	bool isValid(const char* checked)
//	{
//			passwords_file.seekg(0, std::ios::beg);
//			if (passwords_file.is_open()) {
//				std::string password;
//				while (std::getline(passwords_file, password)) {
//					if (!std::strcmp(password.c_str(), checked)) {
//						return true;
//					}
//				}
//			}
//			return false;
//		};
//	~PasswordManager()
//	{
//		passwords_file.close();
//	};
//private: // fields:
//	std::ifstream passwords_file;
//};


class TaskSocket;
class ServerControl 
{
public:
	ServerControl(std::string address, int port);
	virtual	~ServerControl();
	void	Start();
	

private:
	void	ServerThreadProc();
	std::thread	m_serverThread;
	

	int				m_iPort;
	std::string		m_address;
	std::vector<Framework::BlockSocket*> m_vClients;

	void PingPong();
	void SendToAllClient(const Framework::PacketData* msg);


private: /* fields: */
	//PasswordManager password_manager;

	TaskSocket*								  		m_pConnectionHandler;
	std::vector<TaskSocket*>				Channel;
	
	//EventsHandle<Event> events_handle;
	//ServerSocket server_socket;

	bool quit_flag;
	TimeStamp pinged;

};