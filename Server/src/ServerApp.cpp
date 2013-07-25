

#ifndef SERVERAPP_H
#include "ServerApp.h"
#endif

#ifndef PORTS_H
#include "Ports.h"
#endif

#ifndef EXCEPTIONS_H
#include "Exceptions.h"
#endif

#ifndef IOSTREAM
#include <iostream>
#endif

#ifndef SERVER_H
#include "Server.h"
#endif


using namespace std;

bool ServerApp::_exists;
ServerApp* ServerApp::_instance;

ServerApp::ServerApp()
{
	_exists = true;
}

ServerApp* ServerApp::GetInstance()
{
	return _instance;
}

void ServerApp::Create()
{
	std::cout << "Server startup...\n";
	_instance = new ServerApp();
	PortsPool::Create(3200, 3299,1);
	PortsPool::Create(3300, 3399,2);
	std::cout << "Server created\n";
}


void ServerApp::Run()
{
	std::cout << "Server started...\n";
	char a = 'y';
	while (a == 'y')
	{
		std::cout << " -- For single player type 1;\n -- For two players type 2:\n";
		int n;
		std::cin >> n;
		Server* server;
		switch (n)
		{
		case 1:
			server = new ServerSP;
			break;
		case 2:
			server = new ServerTP;
			break;
		}
		try
		{
			server -> Run();
		}
		catch (ENoPortsAvailable* e)
		{
			std::cout << "No ports available";
		}
		catch (EConnectionFailed* e)
		{
			std::cout << "Connection failed";
		}
		std::cout << "Server was shutdown.\n -- Type \'y\' to create new game...\n";
		delete server;
		std::cin >> a;
	}
	std::cout << "Server is shutdown\nGood-bye!\n";
}



