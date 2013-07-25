/*
 * Components.h
 *
 *  Created on: Apr 14, 2013
 *      Author: kostya
 */

#ifndef COMPONENTS_H_
#define COMPONENTS_H_

#ifndef GLLCOMMON_H
#include "gllcommon.h"
#endif

#ifndef EVENTS_H
#include "Events.h"
#endif

#ifndef COMMAND_H
#include "Command.h"
#endif


class Info
{
public:
	int MouseX;
	int MouseY;
	int MouseState;
	int MouseButton;
	int KeyPressed;
	Info();
	Info(int mx, int my);
	Info(int mx, int my, int mb, int ms, int key);
};

class IComponent
{
public:
	virtual void Draw() = 0;
	virtual void EventHandle(Event e, Info I) = 0;
	virtual bool IsPointInside (int ax, int ay) = 0;

	virtual void CommandHandle(ServerCommand cmd) = 0;
	virtual ~IComponent(){}
};




class Rectangle : public IComponent
{
public:
	void Draw();
	void EventHandle(Event e);
	bool IsPointInside (int ax, int ay);
	Rectangle() {}
	Rectangle (int x1, int y1, int x2, int y2, Color cl = BLACK);
	Rectangle (Position ps, Size sz, Color cl = BLACK);
	virtual ~Rectangle(){}
private:
	Position _position;
	Size _size;
	int _x1, _y1, _x2, _y2;
	Color _color;
	Color _actColor;
	bool _active;
};






#endif /* COMPONENTS_H_ */
