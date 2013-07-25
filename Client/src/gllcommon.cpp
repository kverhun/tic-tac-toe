#ifndef GLLCOMMON_H
#include "gllcommon.h"
#endif

#ifndef FREEGLUT_H
#include <GL/freeglut.h>
#endif




Size::Size(int w, int h)
{
	this -> _height = h;
	this -> _width = w;
}

int Size::GetHeight() const
{
	return this->_height;
}

int Size::GetWidth() const
{
	return this->_width;
}

void Size::Set(int w, int h)
{
	this->_height = h;
	this->_width = w;
}

void Size::Change(double scale_h, double scale_w)
{
	this -> _height = (1 + scale_h) * this->_height;
	this -> _width = (1 + scale_w) * this -> _width;
}

void Size::Change(int h, int w)
{
	this -> _height += h;
	this -> _width += w;
	if (this -> _height < 0) this -> _height = 0;
	if (this -> _width < 0) this -> _width = 0;
}

void Size::ChangeH(double scale_h)
{
	this -> Change(scale_h, 1.0);
}

void Size::ChangeH(int h)
{
	this -> Change(h, 0);
}

void Size::ChangeW(double scale_w)
{
	this -> Change(1.0, scale_w);
}

void Size::ChangeW(int w)
{
	this -> Change(0, w);
}

Position::Position(int x, int y)
{
	this -> x = x;
	this -> y = y;
}

int Position::GetX() const
{
	return this -> x;
}

int Position::GetY() const
{
	return this -> y;
}

void Position::Set(int x, int y)
{
	this -> x = x;
	this -> y = y;
}

Color::Color(double red, double green, double blue)
{
	_red = red;
	_green = green;
	_blue = blue;
}

double Color::GetRed() const
{
	return this -> _red;
}
double Color::GetGreen() const
{
	return this -> _green;
}
double Color::GetBlue() const
{
	return this -> _blue;
}

Color Color::Modify()
{
	double newRed = this->_red > 0.9 ? this -> _red - 0.1 : this -> _red + 0.1;
	double newGreen = this->_green > 0.9 ? this -> _green - 0.1 : this -> _green + 0.1;
	double newBlue = this->_blue > 0.9 ? this -> _blue - 0.1 : this -> _blue + 0.1;
	return Color (newRed, newGreen, newBlue);
}



int openGlInit (int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	return 0;
}

void glColor (Color cl)
{
	glColor3f(cl.GetRed(), cl.GetGreen(), cl.GetBlue());
}
