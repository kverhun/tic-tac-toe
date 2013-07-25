/*
 * Ports.h
 *
 *  Created on: Apr 28, 2013
 *      Author: kostya
 */

#ifndef PORTS_H_
#define PORTS_H_

class PortsPool
{
public:
	static PortsPool* GetInstance(int num = 1);
	static void Create (int minport, int maxport, int num = 1);
	int GetPort();
	void RetPort (int port);
private:
	PortsPool();
	static PortsPool* _instance1;
	static PortsPool* _instance2;
	static bool _exists1;
	static bool _exists2;

	int* _ports;
	bool* _available;
	int _portsCount;

};

#endif /* PORTS_H_ */
