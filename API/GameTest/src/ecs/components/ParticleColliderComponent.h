// ParticleColliderComponent.h
#pragma once

#include <string>
#include "../ECS.h"
#include "Components.h"
#include "src/graphics/shapes/Circle.h"
#include "Game.h"
#include "App/app.h"

/*
 *	This is the collider component.
 */

class ParticleColliderComponent : public Component
{
private:
	CSimpleSprite* texture_;
	float scale_;

public:
	Circle collider;
	TransformComponent* transform;
	std::string tag;


	ParticleColliderComponent(std::string tag_, float radius, float scale)
	{
		tag = tag_;
		scale_ = scale;
		collider.radius = radius;
	}
	ParticleColliderComponent(std::string tag_, const physics::Vector3& position, float radius, float scale)
	{
		tag = tag_;
		scale_ = scale;		// This is more like a safe guard if the the collider doesn't have a transform
		collider.position = position;
		collider.radius = radius;
	}

	// ====== OVERRIDES ======
	// Just gets the Transform component
	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>(scale_);
		}
		transform = &entity->getComponent<TransformComponent>();


		texture_ = App::CreateSprite("resources/map/ParticleCollider.png", 1, 1);
		texture_->SetScale(transform->scale);
	}

	void update() override
	{
		if (tag != "terrain")
		{
			collider.position.x = transform->position.x;
			collider.position.y = transform->position.y;
			collider.radius *= transform->scale;
		}

		texture_->SetPosition(collider.position.x - Game::camera.position.x, collider.position.y - Game::camera.position.y);
	}

	void draw() override
	{
		texture_->Draw();
	}
};