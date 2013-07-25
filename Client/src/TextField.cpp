#ifndef TEXTFIELD_H
#include "TextField.h"
#endif

#ifndef CLIENT_H
#include "Client.h"
#endif

#ifndef FREEGLUT_H
#include <GL/freeglut.h>
#endif

TextField::TextField(int x1, int y1, int x2, int y2, std::string cpt, Color cl, Color scl, int swd, bool ang)
{
	this -> _x1 = x1;
	this -> _x2 = x2;
	this -> _y1 = y1;
	this -> _y2 = y2;
	this -> _color = cl;
	this -> _shapeColor = scl;
	this -> _caption = cpt;
	this -> _shapeWidth = swd;
	this -> _angles = ang;
	this -> _position = Position(_x1, _y1);
	this -> _size = Size (_x2 - _x1, _y2 - _y1);
	this -> _isActive = false;
	this -> _actColor = this -> _color;
}

void TextField::CommandHandle(ServerCommand cmd)
{
	Client* cl = Client::GetInstance();
	int winner = cmd.GetWinner();
	switch (winner)
	{
	case 1:
		if (cl -> GetPlayer() == First)
			this -> _caption = "You won!";
		else this -> _caption = "You lost :(";
		break;
	case 2:
		if (cl -> GetPlayer() == Second)
			this -> _caption = "You won!";
		else this -> _caption = "You lost :(";
		break;
	}
	switch (cmd.GetType())
	{
	case SGameBegin:
		break;
	case SGameEnd:
		switch (winner)
		{
		case 1:
			if (cl -> GetPlayer() == First)
				this -> _caption = "You won!";
			else this -> _caption = "You lost :(";
			break;
		case 2:
			if (cl -> GetPlayer() == Second)
				this -> _caption = "You won!";
			else this -> _caption = "You lost :(";
			break;
		}
		break;
	case SInvalideAction:
		this -> _caption = "Invalid move!";
		break;
	case SSetTextConnectionError:
		this -> _caption = "Connection failed";
		break;
	case SSetTextNoServerAvailable:
		this -> _caption = "No server available";
		break;
	case SSetTextWrong:
		this -> _caption = "Ooops. Something failed.";
		break;
	case SSetTextWaiting:
		this -> _caption = "Waiting...";
		break;
	case SSetTextGameBegin:
		this -> _caption = "Game began. Good luck!";
		break;
	default:
		this -> _caption = "";
	}
	this -> Draw();
	glutSwapBuffers();
}


void TextField::EventHandle(Event e, Info I)
{

}
