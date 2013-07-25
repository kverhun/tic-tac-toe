#ifndef COMPONENTS_H
#include "Components.h"
#endif

#ifndef FREEGLUT_H
#include <GL/freeglut.h>
#endif

Info::Info()
{
	this -> MouseX = 0;
	this -> MouseY = 0;
	this -> KeyPressed = 0;
	this -> MouseButton = 0;
}
Info::Info(int mx, int my)
{
	this -> MouseX = mx;
	this -> MouseY = my;
	this -> KeyPressed = 0;
	this -> MouseButton = 0;
}

Info::Info(int mx, int my, int mb, int ms, int key)
{
	this -> MouseX = mx;
	this -> MouseY = my;
	this -> KeyPressed = key;
	this -> MouseButton = mb;
	this -> MouseState = ms;
}


Rectangle::Rectangle(int x1, int y1, int x2, int y2, Color cl)
{
	_x1 = x1;
	_x2 = x2;
	_y1 = y1;
	_y2 = y2;
	_position = Position(_x1, _y1);
	_size = Size (_x2 - _x1, _y2 - _y1 );
	_color = cl;
	_actColor = RED;
	_active  = false;
}

Rectangle::Rectangle(Position ps, Size sz, Color cl)
{
	_position = ps;
	_size = sz;
	_x1 = ps.GetX();
	_y1 = ps.GetY();
	_x2 = _x1 + sz.GetWidth();
	_y2 = _y1 +sz.GetHeight();
	_color = cl;
	_actColor = RED;
	_active  = false;
}

void Rectangle::Draw()
{
	if (this->_active)
		glColor(this->_actColor);
	else
		glColor(this->_color);
	glRecti(this -> _x1, this -> _y1, this -> _x2, this -> _y2);
}

void Rectangle::EventHandle(Event e)
{
	switch (e)
	{
	case MouseOn:
		this -> _active = true;
		break;
	case MouseOut:
		this -> _active = false;
		break;
	default:
		break;
	}
	this -> Draw();
}

bool Rectangle::IsPointInside(int ax, int ay)
{
	if ( (ax>=this->_x1)&&(ax<=this->_x2) && (ay >= this ->_y1) && (ay<=this -> _y2) )
		return true;
	else
		return false;
}
