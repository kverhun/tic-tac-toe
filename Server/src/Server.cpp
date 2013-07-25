#ifndef SERVER_H
#include "Server.h"
#endif

#ifndef PORTS_H
#include "Ports.h"
#endif

#ifndef EXCEPTIONS_H
#include "Exceptions.h"
#endif

#ifndef COMMAND_H
#include "Command.h"
#endif

#ifndef MATH_H
#include "math.h"
#endif

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>


#ifndef IOSTREAM
#include <iostream>
#endif


using namespace std;

Server::~Server()
{

}

ServerTP::ServerTP()
{
	this -> _game = new Game(15, 15, TwoPlayers);
	this -> _listener = -1;
	this -> _sockdesc1 = -1;
	this -> _sockdesc2 = -1;
}

ServerTP::~ServerTP()
{
	PortsPool::GetInstance() -> RetPort(this -> _port);
	close(this -> _sockdesc1);
	close(this -> _sockdesc2);
}

int ServerTP::Run()
{
	cout << "\nCreating server for two players...\n";
	sockaddr_in addr;
	char buf[MAX_MSG_LENGTH];
	int bytes_read;
	bool connected = false;
	addr.sin_family = AF_INET;
	inet_aton("127.0.0.1", &addr.sin_addr);
	PortsPool* ports = PortsPool::GetInstance(2);
	int CheckedPorts[1000];
	int i = 0;
	while (!connected)
	{
		_port = htons(ports -> GetPort());
		if (_port < 0)
		{
			for (int j = 0; j < i; ++j)
				ports -> RetPort(CheckedPorts[j]);
			throw new ENoPortsAvailable();
		}

		_listener = socket(AF_INET, SOCK_STREAM, 0);
		if (_listener < 0)
		{
			for (int j = 0; j < i; ++j)
				ports -> RetPort(CheckedPorts[j]);
			throw new EConnectionFailed();
		}
		addr.sin_family = AF_INET;
		addr.sin_port = _port;
		inet_aton("127.0.0.1", &addr.sin_addr);
		if (bind(_listener, (sockaddr*)&addr, sizeof(addr)) < 0)
		{
			CheckedPorts[i++] = _port;
			close (_listener);
		}
		else
		{
			connected = true;
		}
	}
	for (int j = 0; j < i; ++j)
		ports -> RetPort(CheckedPorts[j]);

	cout << "Connection port: " << this -> _port << '\n';


	listen(_listener, 2);

	cout << "Waiting for clients...\n";
	_sockdesc1 = accept(_listener, NULL, NULL);
	if (_sockdesc1 < 0)
	{
		cout << "Error first connection";
		throw new EConnectionFailedFirst();
	}
	ServerCommand scmd1 = ServerCommand();
	scmd1.SetCommand(SConnectPermissionFirst);
	char* scmdb1 = scmd1.ToString();
	send (_sockdesc1,scmdb1, MAX_MSG_LENGTH, 0);
	delete[] scmdb1;
	cout << "First connected. Waiting for second...\n";

	_sockdesc2 = accept(_listener, NULL, NULL);
	if (_sockdesc2 < 0)
	{
		cout << "Error second connection.\n";
		throw new EConnectionFailedSecond();
	}
	ServerCommand scmd2 = ServerCommand();
	scmd2.SetCommand(SConnectPermissionSecond);
	char* scmdb2 = scmd2.ToString();
	send (_sockdesc2,scmdb2, MAX_MSG_LENGTH, 0);
	delete[] scmdb2;
	cout << "Two clients are ready\n";


	int maxSock = (_sockdesc1 > _sockdesc2 ? _sockdesc1 : _sockdesc2);
	fcntl(_listener, F_SETFL, O_NONBLOCK);
	ServerCommand scmd3 = ServerCommand();
	scmd3.SetCommand(SGameBegin);
	char* scmdb3 = scmd3.ToString();
	send (_sockdesc1,scmdb3, MAX_MSG_LENGTH, 0);
	send (_sockdesc2,scmdb3, MAX_MSG_LENGTH, 0);
	delete[] scmdb3;
	_game -> SwitchState();
	while(true)
	{
		fd_set readset;
		FD_ZERO(&readset);
		FD_SET(_listener, &readset);
		FD_SET(_sockdesc1, &readset);
		FD_SET(_sockdesc2, &readset);
		timeval timeout;
		timeout.tv_sec = 10;
		timeout.tv_usec = 0;
		if (select(maxSock+1, &readset, NULL, NULL, &timeout ) <= 0)
		{
			continue;
		}
		if ( FD_ISSET(_sockdesc1, &readset))
		{
			bytes_read = recv(_sockdesc1, buf, MAX_MSG_LENGTH, 0);
			if (bytes_read <= 0)
			{
				cout << "Receiving from 1 error\n";
				throw new EConnectionFailedFirst();
			}
			cout << "Received from first: " << bytes_read << " bytes\n";
			ClientCommand ccmd = ClientCommand(buf);
			ServerCommand scmd = _game -> GetAnswer(ccmd);
			char* scmdbytes = scmd.ToString();
			switch (scmd.GetAddr())
			{
			case F:
				send(_sockdesc1, scmdbytes, MAX_MSG_LENGTH, 0);
				break;
			case S:
				send(_sockdesc2, scmdbytes, MAX_MSG_LENGTH, 0);
				break;
			case B:
				send(_sockdesc1, scmdbytes, MAX_MSG_LENGTH, 0);
				send(_sockdesc2, scmdbytes, MAX_MSG_LENGTH, 0);
				break;
			default:
				;
			}
			if (scmd.GetWinner()!=0)
			{
				cout << "Winner: " << scmd.GetWinner() << '\n';
				scmd.SetCommand(SGameEnd);
				scmdbytes = scmd.ToString();
				send(_sockdesc1, scmdbytes, MAX_MSG_LENGTH, 0);
				send(_sockdesc2, scmdbytes, MAX_MSG_LENGTH, 0);
				close (_listener);
				close (_sockdesc1);
				close (_sockdesc2);
				ports -> RetPort(this -> _port);
				break;
			}
			delete[] scmdbytes;
		}
		if (FD_ISSET(_sockdesc2, &readset))
		{
			bytes_read = recv(_sockdesc2, buf, MAX_MSG_LENGTH, 0);
			if (bytes_read <= 0)
			{
				cout << "Receiving from 2 error\n";
				throw new EConnectionFailedSecond();
			}
			cout << "Received from second: " << bytes_read << " bytes\n";
			ClientCommand ccmd = ClientCommand(buf);
			ServerCommand scmd = _game -> GetAnswer(ccmd);
			char* scmdbytes = scmd.ToString();
			switch (scmd.GetAddr())
			{
			case F:
				send(_sockdesc1, scmdbytes, MAX_MSG_LENGTH, 0);
				break;
			case S:
				send(_sockdesc2, scmdbytes, MAX_MSG_LENGTH, 0);
				break;
			case B:
				send(_sockdesc1, scmdbytes, MAX_MSG_LENGTH, 0);
				send(_sockdesc2, scmdbytes, MAX_MSG_LENGTH, 0);
				break;
			default:
				;
			}
			if (scmd.GetWinner()!=0)
			{
				cout << "Winner: " << scmd.GetWinner() << '\n';
				scmd.SetCommand(SGameEnd);
				scmdbytes = scmd.ToString();
				send(_sockdesc1, scmdbytes, MAX_MSG_LENGTH, 0);
				send(_sockdesc2, scmdbytes, MAX_MSG_LENGTH, 0);
				close (_listener);
				close (_sockdesc1);
				close (_sockdesc2);
				ports -> RetPort(this -> _port);
				break;
			}

			delete[] scmdbytes;
		}
	}
}








ServerSP::ServerSP()
{
	this -> _game = new Game(15, 15, TwoPlayers);
	this -> _listener = -1;
	this -> _sockdesc1 = -1;
}

ServerSP::~ServerSP()
{
	PortsPool::GetInstance() -> RetPort(this -> _port);
	close(this -> _sockdesc1);
}













int ServerSP::Run()
{
	cout << "\nCreating server for single player...\n";
	sockaddr_in addr;
	char buf[MAX_MSG_LENGTH];
	int bytes_read;
	bool connected = false;
	addr.sin_family = AF_INET;
	inet_aton("127.0.0.1", &addr.sin_addr);
	PortsPool* ports = PortsPool::GetInstance(1);
	int CheckedPorts[1000];
	int i = 0;
	while (!connected)
	{
		_port = htons(ports -> GetPort());
		if (_port < 0)
		{
			for (int j = 0; j < i; ++j)
				ports -> RetPort(CheckedPorts[j]);
			throw new ENoPortsAvailable();
		}

		_listener = socket(AF_INET, SOCK_STREAM, 0);
		if (_listener < 0)
		{
			for (int j = 0; j < i; ++j)
				ports -> RetPort(CheckedPorts[j]);
			throw new EConnectionFailed();
		}
		addr.sin_family = AF_INET;
		addr.sin_port = _port;
		inet_aton("127.0.0.1", &addr.sin_addr);
		if (bind(_listener, (sockaddr*)&addr, sizeof(addr)) < 0)
		{
			CheckedPorts[i++] = _port;
			close (_listener);
		}
		else
		{
			connected = true;
		}
	}
	for (int j = 0; j < i; ++j)
		ports -> RetPort(CheckedPorts[j]);

	cout << "Connection port: " << this -> _port << '\n';


	listen(_listener, 1);

	cout << "Waiting for client...\n";
	_sockdesc1 = accept(_listener, NULL, NULL);
	if (_sockdesc1 < 0)
	{
		cout << "Error first connection";
		throw new EConnectionFailedFirst();
	}
	ServerCommand scmd1 = ServerCommand();
	scmd1.SetCommand(SConnectPermissionFirst);
	char* scmdb1 = scmd1.ToString();
	send (_sockdesc1,scmdb1, MAX_MSG_LENGTH, 0);
	delete[] scmdb1;
	cout << "Connected.\n";

	ServerCommand scmd3 = ServerCommand();
	scmd3.SetCommand(SGameBegin);
	char* scmdb3 = scmd3.ToString();
	send (_sockdesc1,scmdb3, MAX_MSG_LENGTH, 0);
	delete[] scmdb3;


	fcntl(_listener, F_SETFL, O_NONBLOCK);
	_game -> SwitchState();
	while(true)
	{
		fd_set readset;
		FD_ZERO(&readset);
		FD_SET(_listener, &readset);
		FD_SET(_sockdesc1, &readset);
		timeval timeout;
		timeout.tv_sec = 10;
		timeout.tv_usec = 0;
		if (select(this -> _sockdesc1+1, &readset, NULL, NULL, &timeout ) <= 0)
		{
			continue;
		}
		if ( FD_ISSET(_sockdesc1, &readset))
		{
			bytes_read = recv(_sockdesc1, buf, MAX_MSG_LENGTH, 0);
			if (bytes_read <= 0)
			{
				cout << "Receiving from 1 error\n";
				throw new EConnectionFailedFirst();
			}
			cout << "Received from client: " << bytes_read << " bytes\n";
			ClientCommand ccmd = ClientCommand(buf);
			ServerCommand scmd = _game -> GetAnswer(ccmd);
			char* scmdbytes = scmd.ToString();
			send(_sockdesc1, scmdbytes, MAX_MSG_LENGTH, 0);
			if (scmd.GetWinner()!=0)
			{
				cout << "Winner: " << scmd.GetWinner() << '\n';
				scmd.SetCommand(SGameEnd);
				scmdbytes = scmd.ToString();
				send(_sockdesc1, scmdbytes, MAX_MSG_LENGTH, 0);
				close (_listener);
				close (_sockdesc1);
				ports -> RetPort(this -> _port);
				break;
			}
			if (scmd.GetCmd() ==  SInvalideAction) continue;
			sleep(1);
			ServerCommand scmd2;
			switch (ccmd.GetPlayer())
			{
			case First:
				scmd2 = this -> _game -> GetAnswerMove(Second);
				break;
			case Second:
				scmd2 = this -> _game -> GetAnswerMove(First);
				break;
			}
			scmdbytes = scmd2.ToString();
			send(_sockdesc1, scmdbytes, MAX_MSG_LENGTH, 0);
			if (scmd.GetWinner()!=0)
			{
				cout << "Winner: " << scmd.GetWinner() << '\n';
				scmd.SetCommand(SGameEnd);
				scmdbytes = scmd.ToString();
				send(_sockdesc1, scmdbytes, MAX_MSG_LENGTH, 0);
				close (_sockdesc1);
				close (_listener);
				ports -> RetPort(this -> _port);
				break;
			}
			delete[] scmdbytes;
		}

	}
}







