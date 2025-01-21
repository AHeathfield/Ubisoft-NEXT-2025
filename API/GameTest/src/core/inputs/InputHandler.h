// InputHandler.h

#pragma once

#include "stdafx.h"

// I think adding this to a GameState Manager of some sort is a good choice

class InputHandler
{
private:
	std::shared_ptr<Command> keyW_;
	std::shared_ptr<Command> keyA_;
	std::shared_ptr<Command> keyS_;
	std::shared_ptr<Command> keyD_;
	std::shared_ptr<Command> mouseL_;

public:
	InputHandler(std::shared_ptr<Command> keyW, std::shared_ptr<Command> keyA, std::shared_ptr<Command> keyS, std::shared_ptr<Command> keyD, std::shared_ptr<Command> mouseL);

	void handleInput();
};