/*
 * Window.h
 *
 *  Created on: Apr 14, 2013
 *      Author: kostya
 */

#ifndef WINDOW_H_
#define WINDOW_H_

#ifndef GLLCOMMON_H
#include "gllcommon.h"
#endif

#ifndef COMPONENTS_H
#include "Components.h"
#endif

#ifndef COMMAND_H
#include "Command.h"
#endif

#ifndef STRING
#include <string>
#endif

using namespace std;


enum GameState
{
	Active,
	Passive,
	NoConnection
};


// Singleton-based class
// Implements the only one window, created by app
// Has static functions to be given as a parameter to opengl functions
class Window
{
public:
	// returns reference to window-object
	static Window* GetInstance();
	void Create();
	static Window* Create (Position ps, Size sz, string title, Color bckg = BCKG);
	static Window* Create (int x, int y, int w, int h, string title, Color bckg = BCKG);

	void Show();
	void Destroy();

	int CurrentActive(int ax, int ay);

	bool AddComponent(IComponent* cmp);
	void SetFieldIndex(unsigned int index);
	/**
	 GUI-listening function
	 */
	static void Redraw();
	static void MouseMoveHandle(int ax, int ay);
	static void MousePressedHandle (int button, int state, int x, int y);
	static void MousePressedMoveHandle (int ax, int ay);
	static void TimerHandler(int);
	static void Initialize();

	/**
	 Server-commands handlers
	 */
	void CommandHandle(ServerCommand cmd);
	void SetTextField (std::string str);
private:
	Window();
	~Window();
	static Window* wInstance;
	static bool exists;
	IComponent* _components[100];
	int _componentCount;
	Position _position;
	Size _size;
	string _title;
	Color _background;
	int _currentActive;


	// data to be read and influenced by server commands

	GameState _state;

	// used to access to game-field directly
	unsigned int _fieldIndex;
};




#endif /* WINDOW_H_ */
