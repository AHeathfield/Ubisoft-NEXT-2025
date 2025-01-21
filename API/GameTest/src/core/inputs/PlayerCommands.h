// PlayerCommands.h
#pragma once

#include "stdafx.h"
#include "../Command.h"
#include "src/ecs/ECS.h"

// I think I will just define the basic movements in here
// Maybe in future I will add vel.

// ====== Move Up ======
class MoveUpCommand : public Command
{
private:
	//std::shared_ptr<Player> m_player; OLD REMOVE
	Entity& entity_;
public:
	//MoveUpCommand(const std::shared_ptr<Player>& player); OLD REMOVE
	MoveUpCommand(Entity& entity);
	void execute() override;
};


// ====== Move Down ======
class MoveDownCommand : public Command
{
private:
	Entity& entity_;
public:
	MoveDownCommand(Entity& entity);
	void execute() override;
};


// ====== Move Right ======
class MoveRightCommand : public Command
{
private:
	Entity& entity_;
public:
	MoveRightCommand(Entity& entity);
	void execute() override;
};


// ====== Move Left ======
class MoveLeftCommand : public Command
{
private:
	Entity& entity_;
public:
	MoveLeftCommand(Entity& entity);
	void execute() override;
};


// ====== LaunchBall ======
class LaunchBallCommand : public Command
{
private:
	Entity& entity_;
public:
	LaunchBallCommand(Entity& entity);
	void execute() override;
};