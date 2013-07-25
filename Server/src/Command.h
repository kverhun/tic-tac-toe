/*
 * Command.h
 *
 *  Created on: Apr 24, 2013
 *      Author: kostya
 */

#ifndef COMMAND_H_
#define COMMAND_H_

enum CommandAddress
{
  F,
  S,
  B,
  U
};

enum Player
{
  Error,
  First,
  Second
};

enum ServerCommandType
{
  SNothing,
  SConnectPermission,
  SConnectPermissionFirst,
  SConnectPermissionSecond,
  SConnectForbid,
  SGameBegin,
  SStateChange,
  SPutCross,
  SPutCircle,
  SInvalideAction,
  SGameEnd,
  SGameEndWinnerFirst,
  SGameEndWinnerSecond
};

enum ClientCommandType
{
	CNothing,
	CConnectionQuery,
	CReady,
	CPut,
	CGameEnd
};


const int MAX_MSG_LENGTH = 5;


// command sent by client
class ClientCommand
{
public:
	ClientCommand();
	ClientCommand(char* cmd);
	unsigned int GetRow();
	unsigned int GetCol();
	Player GetPlayer();
	ClientCommandType GetCommand();
private:
	ClientCommandType _type;
	unsigned int _nrow;
	unsigned int _ncol;
	Player _sentBy;
};



// command sent by server
class ServerCommand
{
public:
	ServerCommand();
	void SetAddress(CommandAddress addr);
	void SetRow(unsigned int i);
	void SetCol(unsigned int j);
	void SetCommand(ServerCommandType cmd);
	void SetWinner(int winner);
	unsigned int GetRow();
	unsigned int GetCol();
	CommandAddress GetAddr();
	ServerCommandType GetCmd();
	int GetWinner();
	char* ToString();
private:
	CommandAddress _addr;
	ServerCommandType _type;
	unsigned int _rowCoord;
	unsigned int _colCoord;
	int _winner;
};



class ServerCommandToSend
{
public:
	ServerCommandToSend (ServerCommand cmd);
	char* GetBytes();
private:
	unsigned int nbytes;
	char* bytes;
};





#endif /* COMMAND_H_ */
