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

}

void ClientCommand::SetCol(unsigned int j)
{
	this -> _ncol = j;
}

void ClientCommand::SetRow(unsigned int i)
{
	this -> _nrow = i;
}

void ClientCommand::SetCommandType(ClientCommandType cmd)
{
	this -> _type = cmd;
}

void ClientCommand::SetPlayer(Player player)
{
	this -> _player = player;
}

char* ClientCommand::ToString()
{
	char* result = new char[5];
	result[0] = (char)this -> _type;
	result[1] = (char)this -> _player;
	result[2] = (char)this -> _nrow;
	result[3] = (char)this -> _ncol;
	result[4] = '\0';
	return result;
}

/*
 * ========================
 * Server
 * ========================
 */
ServerCommand::ServerCommand()
{
	this -> _type = SNothing;
	this -> _ncol = 0;
	this -> _nrow = 0;
	this -> _winner = 0;
}


ServerCommand::ServerCommand(char* cmd)
{
	this -> _type = (ServerCommandType)cmd[0];
	this -> _winner = (unsigned int) cmd[1];
	this -> _nrow = (unsigned int) cmd[2];
	this -> _ncol = (unsigned int) cmd[3];
}

unsigned int ServerCommand::GetRow()
{
	return this -> _nrow;
}

unsigned int ServerCommand::GetCol()
{
	return this -> _ncol;
}

unsigned int ServerCommand::GetWinner()
{
	return this -> _winner;
}

ServerCommandType ServerCommand::GetType()
{
	return this -> _type;
}

void ServerCommand::SetType(ServerCommandType type)
{
	this -> _type = type;
}



