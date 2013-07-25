/*
 * Button.h
 *
 *  Created on: Apr 14, 2013
 *      Author: kostya
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#ifndef COMPONENTS_H
#include "Components.h"
#endif

#ifndef STRING
#include <string>
#endif



class Button : public IComponent
{
public:
	virtual void Draw();
	virtual void EventHandle (Event e, Info I = Info());
	virtual bool IsPointInside(int ax, int ay);
	virtual void CommandHandle (ServerCommand cmd);
	~Button() {}
	Button() {}
	Button (int x1, int y1, int x2, int y2, std::string cpt, Color cl = RED, Color scl = BLACK, int swd = 1, bool ang = false );
	Button (Position ps, Size sz, std::string cpt, Color cl = RED, Color scl = BLACK, int swd = 1, bool ang = false );
protected:
	Position _position;
	Size _size;
	int _x1, _x2, _y1, _y2;
	std::string _caption;
	Color _color;
	Color _actColor;
	Color _shapeColor;
	int _shapeWidth;
	bool _angles;
	bool _isActive;
};



class ConnectAsFirstBtn : public Button
{
public:
	ConnectAsFirstBtn (int x1, int y1, int x2, int y2, std::string cpt, Color cl = RED, Color scl = BLACK, int swd = 1, bool ang = false );
	void EventHandle (Event e, Info I = Info());
};

class ConnectAsSecondBtn : public Button
{
public:
	ConnectAsSecondBtn (int x1, int y1, int x2, int y2, std::string cpt, Color cl = RED, Color scl = BLACK, int swd = 1, bool ang = false );
	void EventHandle (Event e, Info I = Info());
};

#endif /* BUTTON_H_ */
