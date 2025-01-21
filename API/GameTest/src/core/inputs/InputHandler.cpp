// InputHandler.cpp

#include "stdafx.h"
#include "InputHandler.h"


InputHandler::InputHandler(std::shared_ptr<Command> keyW, std::shared_ptr<Command> keyA, std::shared_ptr<Command> keyS, std::shared_ptr<Command> keyD, std::shared_ptr<Command> mouseL)
	: keyW_(keyW)
	, keyA_(keyA)
	, keyS_(keyS)
	, keyD_(keyD)
	, mouseL_(mouseL)
{
}

void InputHandler::handleInput()
{
	// Have some sort of enum handling the states
	if (App::IsKeyPressed('W'))
	{
		keyW_->execute();
	}
	if (App::IsKeyPressed('A'))
	{
		keyA_->execute();
	}
	if (App::IsKeyPressed('S'))
	{
		keyS_->execute();
	}
	if (App::IsKeyPressed('D'))
	{
		keyD_->execute();
	}
	if (App::IsKeyPressed(App::IsKeyPressed(VK_LBUTTON)))
	{
		mouseL_->execute();
	}
}