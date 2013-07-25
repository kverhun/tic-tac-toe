/*
 * gllcommon.h
 *
 *  Created on: Apr 14, 2013
 *      Author: kostya
 */

#ifndef GLLCOMMON_H_
#define GLLCOMMON_H_

class Size
{
public:
	Size(){};
	Size (int, int);
	int GetHeight() const;
	int GetWidth() const;
	void Set (int, int);
	void Change (int, int);
	void Change (double, double);
	void ChangeW (int);
	void ChangeW (double);
	void ChangeH (int);
	void ChangeH (double);
private:
	int _height;
	int _width;
};

class Position
{
public:
	Position(){};
	Position(int, int);
	int GetX () const;
	int GetY () const;
	void Set (int, int);
	void SetX (int);
	void SetY (int);
	void Change (int, int);
	void Change (double, double);
	void ChangeX (int);
	void ChangeX (double);
	void ChangeY (int);
	void ChangeY (double);
private:
	int x;
	int y;
};

class Color
{
public:
	Color() {}
	Color(double red, double green, double blue);
	double GetRed() const ;
	double GetGreen() const;
	double GetBlue()const;
	Color Modify();
private:
	double _red;
	double _green;
	double _blue;
};

const Color RED = Color(1.0, 0.0, 0.0);
const Color GREEN = Color (0.0, 1.0, 0.0);
const Color BLUE = Color (0.0, 0.0, 1.0);
const Color WHITE = Color (1.0, 1.0, 1.0);
const Color BLACK = Color (0.0, 0.0, 0.0);
const Color LIGHTGRAY = Color (0.1,0.1,0.1);
const Color BTNCLR = Color (0.98,0.98,0.98);
const Color BCKG = Color (0.97,0.97,0.97);

int openGlInit (int argc, char** argv);
void glColor (Color cl);

#endif /* GLLCOMMON_H_ */
