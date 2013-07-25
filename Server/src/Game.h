/*
 * Game.h
 *
 *  Created on: Apr 24, 2013
 *      Author: kostya
 */

#ifndef GAME_H_
#define GAME_H_

#ifndef COMMAND_H
#include "Command.h"
#endif


enum GameMode {GameError, SinglePlayer, TwoPlayers};
enum GameState{GameWaiting, GameFirstMove, GameSecondMove, GameEnd};
enum CellState {Empty, Cross, Circle};

const int COUNT_TO_WIN = 5;
const int MAX_SIZE = 25;

class Game
{
public:
	Game (int nrow, int ncol, GameMode gm);
	ServerCommand GetAnswer (ClientCommand clCmd);
	ServerCommand GetAnswerMove (Player pl);
	void SetState(GameState st);
	void SwitchState();
	GameState GetState();
private:

	//* GetWinner() - to be used in GetAnswer
	// returns 0 if noone
	// 		   1 if First
	//		   2 if Second
	int GetWinner ();
	bool CheckCell(int i, int j, CellState St);
	// Puts Cr or Cir to cell
	// returns true if correct action
	// returns false if incorrect
	bool Put (int i, int j, CellState cs);

	GameMode _gameMode;
	GameState _gameState;

	int _ncol;
	int _nrow;
	CellState _cell[MAX_SIZE][MAX_SIZE];
};




#endif /* GAME_H_ */
