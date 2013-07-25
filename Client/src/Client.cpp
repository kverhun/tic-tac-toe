#ifndef CLIENT_H
#include "Client.h"
#endif

#ifndef IOSTREAM
#include <iostream>
#endif

#ifndef EXCEPTIONS_H
#include "Exceptions.h"
#endif

#ifndef WINDOW_H
#include "Window.h"
#endif

#ifndef FREEGLUT_H
#include <GL/freeglut.h>
#endif

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>


Client* Client::_instance;
bool Client::_exists;

Client::Client()
{
	this -> _exists = true;
	this -> _connected = false;
}

void Client::Create(int minp1, int maxp1, int minp2, int maxp2)
{
	Client::_instance = new Client();
	Client* client = Client::GetInstance();
	client -> _ports1count = maxp1 - minp1 + 1;
	client -> _ports2count = maxp2 - minp2 + 1;
	client -> _ports1 = new int [client -> _ports1count];
	client -> _ports2 = new int [client -> _ports2count];
	for (int i = minp1; i <= maxp1; ++i)
		client -> _ports1[i-minp1] = i;
	for (int i = minp2; i <= maxp2; ++i)
		client -> _ports2[i-minp2] = i;

	return;
}

Client* Client::GetInstance()
{
	if (!Client::_exists)
		return NULL;
	return Client::_instance;
}

void Client::Connect(GameType gt)
{
	sockaddr_in addr;
	int bytes_read;
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
		throw new EConnectionFailed();

	addr.sin_family = AF_INET;
	inet_aton("127.0.0.1", &addr.sin_addr);
	volatile int i = 0;
	this -> _connected = false;

	switch (gt)
	{
	case SinglePlayer:
		while (!_connected)
		{
			if (i >= this -> _ports1count)
				throw new ENoServerAvailable();
			addr.sin_port = htons(_ports1[i]);
			int flags = fcntl(_sockdesc, F_GETFL);
			int result = fcntl(_sockdesc, F_SETFL, flags & ~O_NONBLOCK);
			int res = connect(sock, (sockaddr*)&addr, sizeof(addr));
			if (res < 0)
			{

			}
			else
			{
				this -> _sockdesc = sock;
				fcntl(sock, F_SETFL, O_NONBLOCK);
				ServerCommand scmd = this -> ListenOnce();
				switch (scmd.GetType())
				{
				case SConnectPermission:
					this -> _port = _ports1[i];
					this -> _sockdesc = sock;
					this -> _connected = true;
					this -> _player = First;
					break;
				case SConnectPermissionFirst:
					this -> _port = _ports1[i];
					this -> _sockdesc = sock;
					this -> _connected = true;
					this -> _player = First;
					break;
				case SConnectPermissionSecond:
					this -> _port = _ports1[i];
					this -> _sockdesc = sock;
					this -> _connected = true;
					this -> _player = Second;
					break;
				default:
					;
				}
			}
			++i;
		}
		break;
	case TwoPlayers:
		while (!_connected)
		{
			if (i >= this -> _ports2count)
			{
				throw new ENoServerAvailable();
			}
			addr.sin_port =htons(_ports2[i]);
			int flags = fcntl(_sockdesc, F_GETFL);
			int result = fcntl(_sockdesc, F_SETFL, flags & ~O_NONBLOCK);
			int res = connect(sock, (sockaddr*)&addr, sizeof(addr));
			if (res < 0)
			{
				;
			}
			else
			{
				this -> _sockdesc = sock;
				fcntl(sock, F_SETFL, O_NONBLOCK);
				ServerCommand scmd = this -> ListenOnce();
				switch (scmd.GetType())
				{
				case SConnectPermission:
					this -> _port = _ports2[i];
					this -> _sockdesc = sock;
					this -> _connected = true;
					this -> _player = First;
					break;
				case SConnectPermissionFirst:
					this -> _port = _ports2[i];
					this -> _sockdesc = sock;
					this -> _connected = true;
					this -> _player = First;
					break;
				case SConnectPermissionSecond:
					this -> _port = _ports2[i];
					this -> _sockdesc = sock;
					this -> _connected = true;
					this -> _player = Second;
					break;
				default:
					;
				}
			}
			++i;
		}
		break;
	}
	int flags = fcntl(_sockdesc, F_GETFL);
	int result = fcntl(_sockdesc, F_SETFL, flags & ~O_NONBLOCK);
	Window* window = Window::GetInstance();
	ServerCommand cmd1 = ServerCommand();
	window -> Redraw();
	glFinish();
	cmd1.SetType(SSetTextWaiting);
	window -> CommandHandle(cmd1);
	ServerCommand ccmd = this -> ListenOnce();
	while (ccmd.GetType() != SGameBegin)
	{
		ccmd = this -> ListenOnce();
		glFlush();
		if (ccmd.GetType() == SGameEnd)
			throw new EConnectionFailed;
	}

	ServerCommand cmd2 = ServerCommand();
	cmd2.SetType(SSetTextGameBegin);
	window -> CommandHandle(cmd2);
	fcntl(sock, F_SETFL, O_NONBLOCK);
}

void Client::MakeConnected()
{
	this -> _connected = true;
}

ServerCommand Client::ListenOnce()
{
	ServerCommand scmd;
	fd_set readset;
	FD_ZERO(&readset);
	FD_SET(this -> _sockdesc, &readset);
	timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 10000;
	if (select(_sockdesc+1, &readset, NULL, NULL, &timeout ) <= 0)
	{
		scmd.SetType(SNothing);
		return scmd;
	}

	if (FD_ISSET(_sockdesc, &readset))
	{
		char* buf = new char[MAX_MSG_LENGTH];
		int iRead = recv(_sockdesc, buf, MAX_MSG_LENGTH, 0);
		if (iRead < 0)
		{
			scmd.SetType(SNothing);
			return scmd;
		}
		ServerCommand sreccmd = ServerCommand(buf);
		delete[] buf;
		return sreccmd;
	}
	return scmd;
}

void Client::Send(ClientCommand ccmd)
{
	char* buf = ccmd.ToString();
	send (this -> _sockdesc, buf, MAX_MSG_LENGTH, 0);
	delete[] buf;
}

void Client::Disconnect()
{
	this -> _connected = false;
}

int Client::GetSockDesc()
{
	return this -> _sockdesc;
}

Player Client::GetPlayer()
{
	return this -> _player;
}


bool Client::isConnected()
{
	return (this -> _connected);
}
