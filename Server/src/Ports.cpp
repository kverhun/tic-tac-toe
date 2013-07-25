#include "Ports.h"

#ifndef IOSTREAM
#include <iostream>
#endif

#include <netinet/in.h>

bool PortsPool::_exists1;
bool PortsPool::_exists2;
PortsPool* PortsPool::_instance1 ;
PortsPool* PortsPool::_instance2;

PortsPool::PortsPool()
{
	PortsPool::_exists1 = true;
}

PortsPool* PortsPool::GetInstance(int num)
{
	switch (num)
	{
	case 1:
		return _instance1;
	case 2:
		return _instance2;
	default:
		return NULL;
	}
}


void PortsPool::Create(int minport, int maxport, int num)
{
	PortsPool* pool;
	switch (num)
	{
	case 1:
		PortsPool::_instance1 = new PortsPool();
		pool = PortsPool::GetInstance(1);
		break;
	case 2:
		PortsPool::_instance2 = new PortsPool();
		pool = PortsPool::GetInstance(2);
		break;
	default:
		;
	}

	pool -> _portsCount = maxport - minport + 1;
	pool -> _ports = new int [pool -> _portsCount];
	pool -> _available = new bool[pool -> _portsCount];
	for (int i = minport; i <= maxport; ++i)
	{
		pool -> _ports[i-minport] = i;
		pool -> _available[i-minport] = true;
	}
}

int PortsPool::GetPort()
{
	int i = 0;
	while (i < _portsCount && !_available[i]) ++i;
	if (i == _portsCount)
		return -1;
	else
	{
		_available[i] = false;
		return _ports[i];
	}
}

void PortsPool::RetPort(int port)
{
	int i = 0;
	int p = ntohs(port);
	while (i <= _portsCount && _ports[i]!=p) ++i;
	_available[i] = true;
}
