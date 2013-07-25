//============================================================================
// Name        : Server.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#ifndef SERVERAPP_H
#include "ServerApp.h"
#endif

using namespace std;


int main() {
	ServerApp::Create();
	ServerApp::GetInstance() -> Run();
	return 0;
}
