// PlayerCommands.cpp

#include "stdafx.h"
#include "PlayerCommands.h"
#include "src/ecs/components/Components.h"


// ====== LaunchBallCommand ======
LaunchBallCommand::LaunchBallCommand(Entity& entity) : entity_(entity) {}

void LaunchBallCommand::execute()
{

	if (entity_.hasComponent<TransformComponent>() && entity_.hasComponent<SpriteComponent>())
	{
		auto& transform = entity_.getComponent<TransformComponent>();
		if (!transform.isMoving())
		{
			physics::Vector3 mousePos = physics::Vector3();
			App::GetMousePos(mousePos.x, mousePos.y);
			mousePos -= entity_.getComponent<SpriteComponent>().getPosition();;

			transform.velocity.x += 1.0f * (mousePos.x / 50);
			transform.velocity.y += 1.0f * (mousePos.y / 50);
		}
	}
}

// ====== MoveUpCommand ======
MoveUpCommand::MoveUpCommand(Entity& entity) : entity_(entity) {}

void MoveUpCommand::execute()
{
	if (entity_.hasComponent<TransformComponent>())
	{
		entity_.getComponent<TransformComponent>().velocity.y += 1.0f;
		//entity_.getComponent<TransformComponent>().position.y += 2.0f;
	}
}


// ====== MoveDownCommand ======
MoveDownCommand::MoveDownCommand(Entity& entity) : entity_(entity) {}

void MoveDownCommand::execute()
{
	if (entity_.hasComponent<TransformComponent>())
	{
		entity_.getComponent<TransformComponent>().velocity.y += -1.0f;
		//entity_.getComponent<TransformComponent>().position.y += -2.0f;
	}
}


// ====== MoveRightCommand ======
MoveRightCommand::MoveRightCommand(Entity& entity) : entity_(entity) {}

void MoveRightCommand::execute()
{
	if (entity_.hasComponent<TransformComponent>())
	{
		entity_.getComponent<TransformComponent>().velocity.x += 1.0f;
		//entity_.getComponent<TransformComponent>().position.x += 2.0f;
	}
}


// ====== MoveLeftCommand ======
MoveLeftCommand::MoveLeftCommand(Entity& entity) : entity_(entity) {}

void MoveLeftCommand::execute()
{
	if (entity_.hasComponent<TransformComponent>())
	{
		entity_.getComponent<TransformComponent>().velocity.x += -1.0f;
		//entity_.getComponent<TransformComponent>().position.x += -2.0f;
	}
}