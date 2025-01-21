// TransformComponent.h
#pragma once

#include <cmath>
#include "Components.h"
#include "physics/include/core.h"
#include "src/core/Utils.h"

/*
 *	Transform component has position, rotation and scale properties.
 *	Adding this instead of 3 separate to remove boiler plate.
 *	These 3 components are usually grouped together if one exists.
 */
class TransformComponent : public Component
{
public:
	physics::Vector3 position;
	physics::Vector3 velocity;
	physics::Vector3 rotation;

	int height = 32;
	int width = 32;

	float scale = 1.0f;
	float speed = 2.0f;	// Should definitely parameterize this
	float damp = 0.98f;	// Idea is when ball is in different terrains the damping changes or I add to the entities vel.

	// Constructors
	TransformComponent()
	{
		position = physics::Vector3();
		rotation = physics::Vector3(0.0f, 1.0f, 0.0f);
	}
	TransformComponent(float scale_)
	{
		position = physics::Vector3();
		rotation = physics::Vector3(0.0f, 1.0f, 0.0f);
		scale = scale_;
	}
	TransformComponent(const physics::Vector3& position_, float scale_)
	{
		position = position_;
		rotation = physics::Vector3(0.0f, 1.0f, 0.0f);
		scale = scale_;
	}
	TransformComponent(const physics::Vector3& position_, float scale_, int width_, int height_)
	{
		position = position_;
		rotation = physics::Vector3(0.0f, 1.0f, 0.0f);
		scale = scale_;
		height = height_;
		width = width_;
	}
	TransformComponent(const physics::Vector3& position_, const physics::Vector3& rotation_, float scale_)
	{
		position = position_;
		rotation = rotation_;
		scale = scale_;
	}
	TransformComponent(const physics::Vector3& position_, const physics::Vector3& rotation_, float scale_, int width_, int height_)
	{
		position = position_;
		rotation = rotation_;
		scale = scale_;
		height = height_;
		width = width_;
	}


	bool isMoving()
	{
		return !Utils::compareFloats(velocity.x, 0.0f, 0.05f) && !Utils::compareFloats(velocity.y, 0.0f, 0.05f);
	}

	// ====== Overides ======
	void init() override
	{
		velocity = physics::Vector3();
	}

	// TODO: get diagonal normal speeds
	void update() override
	{
		velocity *= damp;
		position.addScaledVector(velocity, speed);
	}
};