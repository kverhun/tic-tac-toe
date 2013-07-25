/*
 * ServerApp.h
 *
 *  Created on: Apr 28, 2013
 *      Author: kostya
 */

#ifndef SERVER_H_
#define SERVER_H_

#ifndef GAME_H
#include "Game.h"
#endif

// Abstract class
class Server
{
public:
	virtual int Run() = 0;
	virtual ~Server();
private:
};


// server for two-player game
class ServerTP : public Server
{
public:
	ServerTP();
	~ServerTP();
	int Run();
private:
	Game* _game;
	int _port;
	int _listener;
	int _sockdesc1;
	int _sockdesc2;
};

class ServerSP : public Server
{
public:
	ServerSP();
	~ServerSP();
	int Run();
private:
	Game* _game;
	int _port;
	int _listener;
	int _sockdesc1;
};


#endif /* SERVERAPP_H_ */
