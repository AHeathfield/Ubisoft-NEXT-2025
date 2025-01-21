// Collision.h
#pragma once

#include "stdafx.h"
#include "src/graphics/shapes/Rect.h"
#include "src/graphics/shapes/Circle.h"
#include "src/ecs/ECS.h"

class ParticleColliderComponent;
class ColliderComponent;

/*
 *	This class contains different collision methods
 */
class Collision
{
public:
	// AABB (Axis Aligned Bounding Box) collisions which only work when a rectangle is not rotated
	static bool AABB(const Rect& rectA, const Rect& rectB);
	static bool AABB(const ColliderComponent& collA, const ColliderComponent& collB);
	static bool ballToBox(const Rect& box, const Circle& ball);
	static bool ballToBox(const ColliderComponent& box, const ParticleColliderComponent& ball);
	//static void resolveCollisionWithBox(Rect box, Entity& playerEntity);
};