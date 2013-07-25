#ifndef FIELD_H
#include "Field.h"
#endif

#ifndef FREEGLUT_H
#include <GL/freeglut.h>
#endif

#ifndef MATH_H
#include <math.h>
#endif

#ifndef WINDOW_H
#include "Window.h"
#endif

#ifndef CLIENT_H
#include "Client.h"
#endif


void Field::Draw()
{
	//
	glColor(this -> _color);
	glRecti(this -> _x1, this -> _y1, this -> _x2, this -> _y2);

	glColor(this -> _gridColor);
	glLineWidth(2);
	glBegin(GL_LINES);
	for (unsigned int i = 0; i <= this -> _ncol; ++i)
	{
		glVertex2i(this -> _x1 + i*(this->_elementSize+1), this -> _y1);
		glVertex2i(this -> _x1 + i*(this->_elementSize+1), this -> _y2);
	}
	for (unsigned int i = 0; i <= this -> _nrow; ++i)
	{
		glVertex2i(this -> _x1, this -> _y1  + i*(this->_elementSize+1));
		glVertex2i(this -> _x2, this -> _y1  + i*(this->_elementSize+1));
	}
	glEnd();

	for (unsigned int i = 0; i < this -> _nrow; ++i)
		for (unsigned int j = 0; j < this -> _ncol; ++j)
		{
			if (this -> _matrix[i][j] != Empty)
			{
				if (this -> _matrix[i][j] == Cross) this -> DrawCross(i, j);
				else this -> DrawCircle(i, j);
			}
		}
}

void Field::EventHandle(Event e, Info I)
{
	Client* client = Client::GetInstance();
	if (client -> isConnected() == false) return;
	switch (e)
	{
	case MouseClick:

		if (I.MouseState == 0) return;
		int i = this -> GetI(I.MouseY);
		int j = this -> GetJ(I.MouseX);
		ClientCommand cmd = ClientCommand();
		cmd.SetPlayer(client -> GetPlayer());
		cmd.SetCommandType(CPut);
		cmd.SetRow(i);
		cmd.SetCol(j);

		client -> Send(cmd);
		//client -> Send(cmd);
		//this -> _matrix[i][j] = Circle;
		//this -> DrawCircle(i, j);
		break;
	}
}

bool Field::IsPointInside(int ax, int ay)
{
	if ( (ax>=this->_x1)&&(ax<=this->_x2) && (ay >= this ->_y1) && (ay<=this -> _y2) )
		return true;
	else
		return false;
}


void Field::CommandHandle(ServerCommand cmd)
{
	 //
	ServerCommandType cmdType = cmd.GetType();
	unsigned int i = cmd.GetRow();
	unsigned int j = cmd.GetCol();
	if (i >= this -> _nrow || j >= this -> _ncol) return;
	switch (cmdType)
	{
	case SPutCross:
		this -> DrawCross(cmd.GetRow(), cmd.GetCol());
		this -> _matrix[cmd.GetRow()][cmd.GetCol()] = Cross;
		break;
	case SPutCircle:
		this -> DrawCircle(cmd.GetRow(), cmd.GetCol());
		this -> _matrix[cmd.GetRow()][cmd.GetCol()] = Circle;
		break;
	default:
		break;
	}
}


Field::Field(unsigned int nrow, unsigned int ncol)
{
	Field(nrow, ncol, 15, 15);
}

void Field::MakeAvailable()
{
	this -> _available = true;
}

Field::Field(unsigned int nrow, unsigned int ncol, int x1, int y1)
{
	this -> _ncol = ncol;
	this -> _nrow = nrow;
	this -> _elementSize = 30;
	this -> _crossColor = RED;
	this -> _circleColor = BLUE;
	this -> _gridColor = BLACK;
	this -> _color = WHITE;
	this -> _x1 = x1;
	this -> _y1 = y1;
	this -> _x2 = this -> _x1 + this -> _ncol * this -> _elementSize + this -> _ncol + 1;
	this -> _y2 = this -> _y1 + this -> _nrow * this -> _elementSize + this -> _nrow + 1;

	this -> _matrix = new State* [this -> _nrow];
	for (unsigned int i = 0; i < this -> _nrow; ++i)
		this -> _matrix[i] = new State[this -> _ncol];
	for (unsigned int i = 0; i < this -> _nrow; ++i)
		for (unsigned int j = 0; j < this -> _ncol; ++j)
			this -> _matrix[i][j] = Empty;
	/*
	this -> _matrix[2][2] = Cross;
	this -> _matrix[6][6] = Cross;
	this -> _matrix[0][3] = Cross;
	*/
}

void Field::DrawCross(unsigned int i, unsigned int j)
{
	glColor(this -> _crossColor);
	glLineWidth(4);
	glBegin(GL_LINES);

	glVertex2i(this -> _x1 + j*(this -> _elementSize+1) + 3, this -> _y1 + (i+1)*(this -> _elementSize+1) -3 );
	glVertex2i(this -> _x1 + (j+1)*(this -> _elementSize+1) - 3, this -> _y1 + i*(this -> _elementSize+1) +2 );

	glVertex2i(this -> _x1 + j*(this -> _elementSize+1) + 3, this -> _y1 + i*(this -> _elementSize+1) +3 );
	glVertex2i(this -> _x1 + (j+1)*(this -> _elementSize+1) - 3, this -> _y1 + (i+1)*(this -> _elementSize+1) - 2 );

	glEnd();
	glutSwapBuffers();
}

void Field::DrawCircle(unsigned int i, unsigned int j)
{
//


	int x0 = this -> _x1 + (this -> _elementSize+1)*j + this -> _elementSize/2;
	int y0 = this -> _y1 + (this -> _elementSize+1)*i + this -> _elementSize/2;
 	int r = this -> _elementSize/2 - 3;
 	glBegin(GL_POINTS);
 	glColor(this -> _circleColor);
 	for(float i = 0; i < 360; i+=0.1)
	{
		glVertex2f(x0+r*cos(i*M_PI/180), y0+r*sin(i*M_PI/180));
		glVertex2f(x0+(r-1)*cos(i*M_PI/180), y0+(r-1)*sin(i*M_PI/180));
	}
	glEnd();
	glutSwapBuffers();
}

void Field::DrawClear(unsigned i, unsigned j)
{
	// TODO
}

int Field::GetI(int yCoord)
{
	int res = 0;
	int ty = this -> _y1 + 1;
	while (ty <= yCoord)
	{
		ty += (this -> _elementSize+1);
		++res;
	}
	--res;
	if (res < this-> _nrow) return res;
	else return this -> _nrow-1;
}

int Field::GetJ(int xCoord)
{
	unsigned res = 0;
	int tx = this -> _x1 + 1;
	while (tx <= xCoord)
	{
		tx += (this -> _elementSize);
		++res;
	}
	--res;
	if (res < this-> _ncol) return res;
		else return this -> _ncol-1;
}

