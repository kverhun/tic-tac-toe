#ifndef BUTTON_H
#include "Button.h"
#endif

#ifndef FREEGLUT_H
#include <GL/freeglut.h>
#endif

#ifndef EXCEPTIONS_H
#include "Exceptions.h"
#endif

#ifndef STRING_H
#include <string.h>
#endif

#ifndef CLIENT_H
#include "Client.h"
#endif

Button::Button (int x1, int y1, int x2, int y2, std::string cpt, Color cl, Color scl, int swd, bool ang)
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
	this -> _actColor =
				Color
					(this -> _color.GetRed() - 0.05,
					this -> _color.GetGreen() - 0.05,
					this -> _color.GetBlue() - 0.05);
}

Button::Button (Position ps, Size sz, std::string cpt, Color cl, Color scl, int swd, bool ang)
{
	this -> _position = ps;
	this -> _size = sz;
	this -> _x1 = this -> _position.GetX();
	this -> _y1 = this -> _position.GetY();
	this -> _x2 = this -> _x1 + this -> _size.GetWidth();
	this -> _y2 = this -> _y1 + this -> _size.GetHeight();
	this -> _color = cl;
	this -> _shapeColor = scl;
	this -> _caption = cpt;
	this -> _shapeWidth = swd;
	this -> _angles = ang;
	this -> _isActive = false;
	this -> _actColor =
				Color
					(this -> _color.GetRed() - 0.05,
					this -> _color.GetGreen() - 0.05,
					this -> _color.GetBlue() - 0.05);

}

void Button::Draw()
{

	if (this -> _isActive)
	{
		//glColor(this->_color.Modify());
		Color newColor = this -> _color.Modify();

		glColor(newColor);
	}
	else
	{
		glColor(this -> _color);
	}

	glRecti(this -> _x1+this -> _shapeWidth, this -> _y1, this -> _x2 , this -> _y2-this -> _shapeWidth);


	glBegin(GL_POINTS);
	glColor(this-> _shapeColor);

	for (int i = this -> _x1 + 2; i < this -> _x2 - 1; ++i)
	{
		glVertex2i(i,this->_y1);
		glVertex2i(i,this->_y2);
	}
	for (int j = this -> _y1 + 2; j < this -> _y2 - 1; ++j)
	{
		glVertex2i(this -> _x1, j);
		glVertex2i(this -> _x2, j);
	}
	glEnd();

	glColor(LIGHTGRAY);
	glRasterPos2i(this -> _x1 + 5, this -> _y1 + 20);
	int len = strlen(this -> _caption.c_str());
	for (int i = 0; i < len; ++i)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, this -> _caption[i]);
	}
	glColor(this -> _shapeColor);
	glBegin(GL_POINTS);
	glVertex2i(this->_x1+1, this -> _y1 + 1);
	glVertex2i(this->_x2-1, this -> _y1 + 1);
	glVertex2i(this->_x1+1, this -> _y2 - 1);
	glVertex2i(this->_x2-1, this -> _y2 - 1);
	glEnd();
	glutSwapBuffers();
}

bool Button::IsPointInside(int ax, int ay)
{
	if ( (ax>=this->_x1)&&(ax<=this->_x2) && (ay >= this ->_y1) && (ay<=this -> _y2) )
		return true;
	else
		return false;
}

void Button::EventHandle(Event e, Info I)
{
	switch (e)
	{
	case MouseOn:
		this -> _isActive = true;
		this -> Draw();
		break;
	case MouseOut:
		this -> _isActive = false;
		this -> Draw();
		break;
	}

}

void Button::CommandHandle(ServerCommand cmd)
{

}

#ifndef CLIENT_H
#include "Client.h"
#endif

#ifndef WINDOW_H
#include "Window.h"
#endif

void ConnectAsFirstBtn::EventHandle (Event e, Info I)
{
	Client* client = Client::GetInstance();
	switch (e)
	{
	case MouseClick:

		if (client -> isConnected()) return;
		if (!client -> isConnected())
		{
			try
			{
				client -> Connect(SinglePlayer);
			}
			catch (ENoServerAvailable* e)
			{
				Window* window = Window::GetInstance();
				ServerCommand cmd = ServerCommand();
				cmd.SetType(SSetTextNoServerAvailable);
				window -> CommandHandle(cmd);
			}
			catch (EConnectionFailed* e)
			{
				Window* window = Window::GetInstance();
				ServerCommand cmd = ServerCommand();
				cmd.SetType(SSetTextConnectionError);
				window -> CommandHandle(cmd);
			}
			catch(IException* e)
			{
				Window* window = Window::GetInstance();
				ServerCommand cmd = ServerCommand();
				cmd.SetType(SSetTextWrong);
				window -> CommandHandle(cmd);
			}
		}
		break;
	case MouseOn:
		this -> _isActive = true;
		this -> Draw();
		break;
	case MouseOut:
		this -> _isActive = false;
		this -> Draw();
		break;
	}
}

ConnectAsFirstBtn::ConnectAsFirstBtn(int x1, int y1, int x2, int y2, std::string cpt, Color cl, Color scl, int swd, bool ang)
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
	this -> _actColor =
			Color
				(this -> _color.GetRed() - 0.05,
				this -> _color.GetGreen() - 0.05,
				this -> _color.GetBlue() - 0.05);

}


void ConnectAsSecondBtn::EventHandle(Event e, Info I)
{
	Client* client = Client::GetInstance();
	switch (e)
	{
	case MouseClick:

		if (client -> isConnected()) return;
		try
		{
			client -> Connect(TwoPlayers);
		}
		catch (ENoServerAvailable* e)
		{
			Window* window = Window::GetInstance();
			ServerCommand cmd = ServerCommand();
			cmd.SetType(SSetTextNoServerAvailable);
			window -> CommandHandle(cmd);
		}
		catch (EConnectionFailed* e)
		{
			Window* window = Window::GetInstance();
			ServerCommand cmd = ServerCommand();
			cmd.SetType(SSetTextConnectionError);
			window -> CommandHandle(cmd);
		}
		catch(IException* e)
		{
		Window* window = Window::GetInstance();
			ServerCommand cmd = ServerCommand();
			cmd.SetType(SSetTextWrong);
			window -> CommandHandle(cmd);
		}
		break;
	case MouseOn:
		this -> _isActive = true;
		this -> Draw();
		break;
	case MouseOut:
		this -> _isActive = false;
		this -> Draw();
		break;
	}
}

ConnectAsSecondBtn::ConnectAsSecondBtn(int x1, int y1, int x2, int y2, std::string cpt, Color cl, Color scl, int swd, bool ang)
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
	this -> _actColor =
				Color
				(this -> _color.GetRed() - 0.05,
				this -> _color.GetGreen() - 0.05,
				this -> _color.GetBlue() - 0.05);

}
