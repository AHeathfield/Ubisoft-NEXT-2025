// Command.h
#pragma once

#include "stdafx.h"
#include "App\app.h"

/*	This is the command pattern.
 *	This will handle inputs mainly, see inputs directory.
 *	Idea is to give Player a move member and have the commands set that value
 */

class Command
{
public:
	virtual ~Command() = default;
	virtual void execute() = 0;
};