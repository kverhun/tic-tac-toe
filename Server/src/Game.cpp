#ifndef IOSTREAM
#include <iostream>
#endif

#ifndef GAME_H
#include "Game.h"
#endif

#ifndef EXCEPTIONS_H
#include "Exceptions.h"
#endif

#ifndef STDLIB_H
#include <stdlib.h>
#endif


Game::Game(int nrow, int ncol, GameMode gm)
{
	this -> _ncol = ncol;
	this -> _nrow = nrow;
	this -> _gameMode = gm;
	this -> _gameState = GameWaiting;

	for (int i = 0; i < this -> _nrow; ++i)
		for (int j = 0; j < this -> _ncol; ++j)
			this -> _cell[i][j] = Empty;

}


bool Game::CheckCell(int I, int J, CellState St)
{
	if (this -> _cell[I][J] != St) return false;
	// find columns
	int i = 0;
	for (i = 1; i < COUNT_TO_WIN; ++i)
	{
		if (this -> _cell[I+i][J] != St || I+i >= this -> _ncol) break;
	}
	if (i == COUNT_TO_WIN) return true;

	// find rows
	int j = 0;
	for (j = 1; j < COUNT_TO_WIN; ++j)
	{
		if (this -> _cell[I][J+j] != St || J+j >= this -> _nrow) break;
	}
	if (j == COUNT_TO_WIN) return true;


	// find diag rightdown
	int k = 0;
	for (k = 0; k < COUNT_TO_WIN; ++k)
	{
		if (this -> _cell[I+k][J+k] != St || I+i >= this -> _ncol || J+j >= this -> _nrow) break;
	}
	if (k == COUNT_TO_WIN) return true;

	// find diag leftdown
	int p = 0;
	for (p = 0; p < COUNT_TO_WIN; ++p)
	{
		if (this -> _cell[I+p][J-p] != St || I+i >= this -> _ncol || J+j >= this -> _nrow) break;
	}
	if (p == COUNT_TO_WIN) return true;

	return false;
}

int Game::GetWinner()
{
	for (int i = 0; i < this -> _ncol; ++i)
		for (int j = 0; j < this -> _nrow; ++j)
		{
			if (this -> CheckCell(i,j, Cross)) return 1;
			if (this -> CheckCell(i, j, Circle)) return 2;
		}
	return 0;
}

bool Game::Put(int i, int j, CellState cs)
{
	if (this -> _cell[i][j] == cs) return false;
	else
	{
		this -> _cell[i][j] = cs;
		return true;
	}
}

void Game::SetState(GameState st)
{
	this -> _gameState = st;
}

void Game::SwitchState()
{
	switch (this -> _gameState)
	{
	case GameFirstMove:
		this -> SetState(GameSecondMove);
		break;
	case GameSecondMove:
		this -> SetState(GameFirstMove);
		break;
	case GameWaiting:
		this -> SetState(GameFirstMove);
		break;
	default:
		throw (new ELogicException());
	}
}

ServerCommand Game::GetAnswer(ClientCommand clCmd)
{

	ServerCommand ResCmd = ServerCommand();
	ResCmd.SetCommand(SNothing);
	ClientCommandType cmd = clCmd.GetCommand();
	Player sentby = clCmd.GetPlayer();
	int i = clCmd.GetRow();
	int j = clCmd.GetCol();
	switch(cmd)
	{
	case CNothing:
		break;
	case CReady:

		break;
	case CConnectionQuery:
		break;
	case CPut:
		switch(sentby)
		{
		case First:
			if (this -> GetState() != GameFirstMove) return ResCmd;
			if (this -> _cell[i][j] == Empty)
			{
				this -> Put(clCmd.GetRow(), clCmd.GetCol(), Cross);
				ResCmd.SetCommand(SPutCross);
				ResCmd.SetRow(i);
				ResCmd.SetCol(j);
				ResCmd.SetAddress(B);
				this -> SwitchState();
			}
			else
			{
				ResCmd.SetCommand(SInvalideAction);
				ResCmd.SetAddress(F);
			}
			break;
		case Second:
			if (this -> GetState() != GameSecondMove) return ResCmd;
			if (this -> _cell[i][j] == Empty)
			{
				this -> Put(clCmd.GetRow(), clCmd.GetCol(), Circle);
				ResCmd.SetCommand(SPutCircle);
				ResCmd.SetRow(i);
				ResCmd.SetCol(j);
				ResCmd.SetAddress(B);
				this -> SwitchState();
			}
			else
			{
				ResCmd.SetCommand(SInvalideAction);
				ResCmd.SetAddress(S);
			}
			break;
		}
		break;
	case CGameEnd:

		break;
	}
	ResCmd.SetWinner(this -> GetWinner());
	return ResCmd;
}


ServerCommand Game::GetAnswerMove(Player pl)
{
	ServerCommand scmd = ServerCommand();

	int i = rand()%this -> _nrow;
	int j = rand()%this -> _ncol;
	while (this -> _cell[i][j]!=Empty)
	{
		i = rand()%this -> _nrow;
		j = rand()%this -> _ncol;
	}
	scmd.SetRow(i);
	scmd.SetCol(j);
	switch (pl)
	{
	case First:
		this -> Put(i,j, Cross);
		scmd.SetCommand(SPutCross);
		break;
	case Second:
		this -> Put(i,j, Circle);
		scmd.SetCommand(SPutCircle);
		break;
	}
	this -> SwitchState();
	scmd.SetWinner(this -> GetWinner());
	return scmd;
}


GameState Game::GetState()
{
	return this -> _gameState;
}
