// Collision.cpp

#include "stdafx.h"
#include "Collision.h"
#include "src/ecs/components/ColliderComponent.h"

bool Collision::AABB(const Rect& rectA, const Rect& rectB)
{
	// If all these cases are true there has been a collision
	// Note we are comparing floats so this might not be a good solution ( i don't think Ill even use this collision anymore )
	if (
		rectA.position.x + rectA.w >= rectB.position.x &&
		rectB.position.x + rectB.w >= rectA.position.x &&
		rectA.position.y + rectA.h >= rectB.position.y &&
		rectB.position.y + rectB.h >= rectA.position.y
		)
	{
		return true;
	}

	return false;
}

bool Collision::AABB(const ColliderComponent& collA, const ColliderComponent& collB)
{
	if (AABB(collA.collider, collB.collider))
	{
		//char debug[50];
		//sprintf(debug, "%s hit: %s\n", collA.tag.c_str(), collB.tag.c_str());	//c_str() turns it into char*
		//OutputDebugStringA(debug);
		return true;
	}

	return false;
}
// 62

bool Collision::ballToBox(const Rect& box, const Circle& ball)
{
	float distance = ball.position.getDistanceBetween(box.position);

	return distance <= (ball.radius + box.w / 2) || distance <= (ball.radius + box.h / 2);
}

bool Collision::ballToBox(const ColliderComponent& box, const ParticleColliderComponent& ball)
{
	if (ballToBox(box.collider, ball.collider))
	{
		return true;
	}

	return false;
}