#pragma once



#include <thread>
#include <vector>


namespace Framework
{
	class BlockSocket;
};


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
};