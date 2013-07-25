#ifndef CLIENTAPP_H
#include "ClientApp.h"
#endif

#ifndef CLIENT_H
#include "Client.h"
#endif

#ifndef WINDOW_H
#include "Window.h"
#endif

#ifndef BUTTON_H
#include "Button.h"
#endif

#ifndef FIELD_H
#include "Field.h"
#endif

#ifndef EXCEPTIONS_H
#include "Exceptions.h"
#endif

#ifndef TEXTFIELD_H
#include "TextField.h"
#endif


ClientApp::ClientApp()
{
	Client::Create();
	Window* mw = Window::Create(50, 50, 480, 600, "Xs & Os",BCKG);
	IComponent* fld = new Field(15, 15, 8, 10);
	mw -> AddComponent(fld);
	mw -> AddComponent(new TextField(200,520,460,550, "Please connect to server", BCKG));
	mw -> AddComponent(new ConnectAsFirstBtn(20, 500, 145, 530, "Single player", BTNCLR));
	mw -> AddComponent(new ConnectAsSecondBtn(20, 550, 145, 580, "Two players", BTNCLR));
}

void ClientApp::Run()
{
	Window* mw = Window::GetInstance();
	try
	{
		mw -> Initialize();
	}
	catch (...)
	{
		ServerCommand cmd = ServerCommand();
		cmd.SetType(SSetTextWrong);
		mw -> CommandHandle(cmd);
	}
}
