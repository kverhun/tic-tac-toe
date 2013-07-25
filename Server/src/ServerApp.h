/*
 * ServerApp.h
 *
 *  Created on: Apr 29, 2013
 *      Author: kostya
 */

#ifndef SERVERAPP_H_
#define SERVERAPP_H_

#ifndef SERVER_H
#include "Server.h"
#endif

class ServerApp
{
public:
	static void Create();
	static ServerApp* GetInstance();
	void Run();
private:
	ServerApp();
	static ServerApp* _instance;
	static bool _exists;
};

#endif /* SERVERAPP_H_ */
