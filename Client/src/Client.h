/*
 * Client.h
 *
 *  Created on: Apr 24, 2013
 *      Author: kostya
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#ifndef COMMAND_H
#include "Command.h"
#endif

enum GameType
{
	SinglePlayer,
	TwoPlayers
};

class Client
{
public:
	static void Create(int minp1 = 3200, int maxp1 = 3299, int minp2 = 3300, int maxp2 = 3399);
	static Client* GetInstance();
	Player GetPlayer();
	bool isConnected();
	ServerCommand ListenOnce();
	void Send(ClientCommand ccmd);
	void Connect (GameType gt = TwoPlayers);
	void MakeConnected();
	void Disconnect();
	int GetSockDesc();

private:
	Client();
	static Client* _instance;
	static bool _exists;
	Player _player;

	int* _ports1;
	int _ports1count;
	int* _ports2;
	int _ports2count;
	int _port;
	int _sockdesc;
	char _buffer[MAX_MSG_LENGTH];

	bool _connected;
};


#endif /* CLIENT_H_ */
