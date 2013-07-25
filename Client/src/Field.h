/*
 * Field.h
 *
 *  Created on: Apr 17, 2013
 *      Author: kostya
 */

#ifndef FIELD_H_
#define FIELD_H_

#ifndef COMPONENTS_H
#include "Components.h"
#endif

enum State {Empty, Cross, Circle};


class Field : public IComponent
{
public:

	void Draw();
	void EventHandle(Event e, Info I);
	bool IsPointInside (int ax, int ay);
	void CommandHandle(ServerCommand cmd);
	~Field() {}

	Field() {}
	Field(unsigned int nrow, unsigned int ncol);
	Field(unsigned int nrow, unsigned int ncol, int x1, int y1);

	void DrawCross(unsigned int i, unsigned int j);
	void DrawCircle(unsigned int i, unsigned int j);
	void DrawClear (unsigned int i, unsigned int j);

	int GetJ (int xCoord);
	int GetI (int yCoord);
	void MakeAvailable();
private:
	Size _size;
	Position _position;
	int _x1, _x2, _y1, _y2;
	unsigned int _ncol;
	unsigned int _nrow;
	unsigned int _elementSize;
	State** _matrix;
	Color _color;
	Color _gridColor;
	Color _crossColor;
	Color _circleColor;
	bool _available;


};



#endif /* FIELD_H_ */
