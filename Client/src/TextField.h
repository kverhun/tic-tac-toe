/*
 * TextField.h
 *
 *  Created on: Apr 28, 2013
 *      Author: kostya
 */

#ifndef TEXTFIELD_H_
#define TEXTFIELD_H_

#ifndef BUTTON_H
#include "Button.h"
#endif

#ifndef STRING
#include <string>
#endif

class TextField : public Button
{
public:
	void EventHandle (Event e, Info I = Info());
	void CommandHandle (ServerCommand cmd);
	TextField(int x1, int y1, int x2, int y2, std::string cpt, Color cl = BCKG, Color scl = BLACK, int swd=1, bool ang=false);
private:

};



#endif /* TEXTFIELD_H_ */
