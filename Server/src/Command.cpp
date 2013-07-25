#ifndef COMMAND_H
#include "Command.h"
#endif

/*
 * ========================
 * Client
 * ========================
 */
ClientCommand::ClientCommand()
{
	this -> _type = CNothing;
}


ClientCommand::ClientCommand(char* cmd)
{
	this -> _type = (ClientCommandType)cmd[0];
	this -> _sentBy = (Player)cmd[1];
	this -> _nrow = (unsigned int) cmd[2];
	this -> _ncol = (unsigned int) cmd[3];
}

Player ClientCommand::GetPlayer()
{
	return this -> _sentBy;
}

unsigned int ClientCommand::GetRow()
{
	return this -> _nrow;
}

unsigned int ClientCommand::GetCol()
{
	return this -> _ncol;
}

ClientCommandType ClientCommand::GetCommand()
{
	return this -> _type;
}



/*
 * ========================
 * Server
 * ========================
 */

ServerCommand::ServerCommand()
{
	this -> _type = SNothing;
	this -> _rowCoord = -1;
	this -> _colCoord = -1;
	this -> _winner = 0;
	this -> _addr = U;
}

void ServerCommand::SetAddress(CommandAddress addr)
{
	this -> _addr = addr;
}

void ServerCommand::SetRow(unsigned int i)
{
	this -> _rowCoord = i;
}

void ServerCommand::SetCol(unsigned int j)
{
	this -> _colCoord = j;
}

void ServerCommand::SetCommand(ServerCommandType cmd)
{
	this -> _type = cmd;
}

void ServerCommand::SetWinner(int winner)
{
	this -> _winner = winner;
}

char* ServerCommand::ToString()
{
	char* result = new char[5];
	result[0] = (char)this -> _type;
	result[1] = (char)this -> _winner;
	result[2] = (char)this -> _rowCoord;
	result[3] = (char)this -> _colCoord;
	result[4] = '\0';
	return result;
}

CommandAddress ServerCommand::GetAddr()
{
	return this -> _addr;
}

ServerCommandType ServerCommand::GetCmd()
{
	return this -> _type;
}

int ServerCommand::GetWinner()
{
	return this -> _winner;
}


