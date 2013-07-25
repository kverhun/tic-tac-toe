/*
 * Command.h
 *
 *  Created on: Apr 24, 2013
 *      Author: kostya
 */

#ifndef COMMAND_H_
#define COMMAND_H_

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
  SGameEndWinnerSecond,
  SSetTextNoServerAvailable,
  SSetTextConnectionError,
  SSetTextWrong,
  SSetTextWaiting,
  SSetTextGameBegin
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


class ClientCommand
{
public:
	ClientCommand();
	void SetCommandType(ClientCommandType cmd);
	void SetRow (unsigned int i);
	void SetCol (unsigned int j);
	void SetPlayer (Player player);
	char* ToString();
private:
	ClientCommandType _type;
	unsigned int _nrow;
	unsigned int _ncol;
	Player _player;
};


class ServerCommand
{
public:
	ServerCommand();
	ServerCommand (char* cmd);
	unsigned int GetWinner();
	unsigned int GetRow();
	unsigned int GetCol();
	ServerCommandType GetType();
	void SetType(ServerCommandType type);
private:
	unsigned int _winner;
	unsigned int _nrow;
	unsigned int _ncol;
	ServerCommandType _type;
};


#endif /* COMMAND_H_ */
