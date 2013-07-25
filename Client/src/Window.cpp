/*
 * Window.cpp
 *
 *  Created on: Apr 24, 2013
 *      Author: kostya
 */

#ifndef WINDOW_H
#include "Window.h"
#endif

#ifndef FREEGLUT
#include <GL/freeglut.h>
#endif

#ifndef STRING
#include <string>
#endif

#ifndef CLIENT_H
#include "Client.h"
#endif

#ifndef EXCEPTIONS_H
#include "Exceptions.h"
#endif

#include <ctime>

bool Window::exists;
Window* Window::wInstance;

Window* Window::GetInstance()
{
	if (!Window::exists)
	{
		Window::wInstance = new Window();
		Window::exists = true;
	}
	return Window::wInstance;
}

Window::Window()
{

}

Window* Window::Create(Position ps, Size sz, string title, Color bckg)
{
	if (Window::exists) return Window::GetInstance();
	Window::wInstance = new Window();
	Window::wInstance -> _background = bckg;
	Window::wInstance -> _position = ps;
	Window::wInstance -> _size = sz;
	Window::wInstance -> _title = title;
	Window::wInstance -> _componentCount = 0;
	Window::exists = true;
	Window::wInstance -> _currentActive = -1;
	openGlInit(NULL, NULL);
	return wInstance;
}

Window* Window::Create(int x, int y, int w, int h, string title, Color bckg)
{
	return Window::Create(Position(x,y), Size(w,h), title, bckg);
}

void Window::Initialize()
{
	Window* instance = Window::GetInstance();
	glutInitWindowSize(instance->_size.GetWidth(), instance->_size.GetHeight());
	glutInitWindowPosition(instance->_position.GetX(), instance->_position.GetY());
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutCreateWindow(instance -> _title.c_str());
	glOrtho(0.0,instance->_size.GetWidth(), instance->_size.GetHeight(), 0.0, 5.0, -5.0);
	glClearColor(instance->_background.GetRed(), instance -> _background.GetGreen(),instance ->_background.GetBlue(), 1.0);

	// registering functions-handlers
	glutDisplayFunc(Window::Redraw);
	glutMotionFunc(Window::MousePressedMoveHandle);
	glutPassiveMotionFunc(Window::MouseMoveHandle);
	glutMouseFunc(Window::MousePressedHandle);
	glutTimerFunc(200, Window::TimerHandler, 0);
	// this have to be in extern function
	// in its own thread

	glutMainLoop();


}

bool Window::AddComponent(IComponent* cmp)
{
	if (this->_componentCount >= 100) return false;
	else
		this -> _components[_componentCount++] = cmp;
	return true;
}

void Window::Redraw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	Window* wPtr = Window::GetInstance();
	int c = wPtr -> _componentCount;
	for (int i = 0; i < c; ++i)
		wPtr->_components[i]->Draw();
	glutSwapBuffers();
}

void Window::MouseMoveHandle(int ax, int ay)
{
	Window* wInst = Window::GetInstance();
	int cur = wInst->_currentActive;
	int newCur = wInst->CurrentActive(ax, ay);
	if (newCur == cur)
		return;
	else
	{
		Info I = Info(ax, ay);
		if (cur >= 0)
			wInst->_components[cur]->EventHandle(MouseOut, I);
		cur = wInst->_currentActive = newCur;
		if (cur >= 0)
			wInst->_components[cur]->EventHandle(MouseOn, I);
		glutSwapBuffers();
	}
}

void Window::MousePressedHandle(int button, int state, int x, int y)
{
	Window* wInst = Window::GetInstance();
	int cur = wInst->CurrentActive(x, y);
	if (cur < 0) return;
	else
	{
		Info I = Info(x,y,button, state, 0);
		wInst -> _components[cur] -> EventHandle(MouseClick, I);
		glutSwapBuffers();
	}
}

void Window::MousePressedMoveHandle(int ax, int ay)
{

}

void Window::TimerHandler(int value)
{
	Client* client = Client::GetInstance();
	Window* window = Window::GetInstance();
	if (!client -> isConnected())
	{
		glutTimerFunc(100, Window::TimerHandler, 0);
	}
	else
	{
		ServerCommand scmd = client -> ListenOnce();
		if (scmd.GetType() != SNothing)
			window -> CommandHandle( scmd);

		if (scmd.GetType() == SGameBegin)
			client -> MakeConnected();
		if (scmd.GetType()!=SGameEnd)
			glutTimerFunc(100, Window::TimerHandler, 0);

	}

}


int Window::CurrentActive(int ax, int ay)
{
	int result = 0;
	while (result < this->_componentCount)
	{

		if (_components[result]->IsPointInside(ax, ay))
			return result;
		++result;
	}
	return -1;
}



void Window::SetFieldIndex(unsigned int index)
{
	this -> _fieldIndex = index;
}


void Window::CommandHandle(ServerCommand cmd)
{
	/*
	if (cmd.GetType() == SPutCircle || cmd.GetType() == SPutCross)
	{
		this -> _components[_fieldIndex] -> CommandHandle(cmd);
	}
	*/
	for (int i = 0; i < this -> _componentCount; ++i)
		this -> _components[i] -> CommandHandle(cmd);
	glutSwapBuffers();
}

void Window::SetTextField(string str)
{

}
