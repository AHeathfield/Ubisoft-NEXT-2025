// ColliderComponent.h
#pragma once

#include <string>
#include "../ECS.h"
#include "Components.h"
#include "src/graphics/shapes/Rect.h"
#include "Game.h"
#include "App/app.h"

/*
 *	This is the collider component.
 */

class ColliderComponent : public Component
{
private:
	CSimpleSprite* texture_;
	float scale_;

public:
	Rect collider;
	float colliderSize;
	TransformComponent* transform;
	std::string tag;


	ColliderComponent(std::string tag_)
	{
		tag = tag_;
	}
	ColliderComponent(std::string tag_, const physics::Vector3& position, float size, float scale)
	{
		tag = tag_;
		scale_ = scale;
		collider.position = position;
		collider.h = size;
		collider.w = size;
		colliderSize = size;
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
		transform->position = collider.position;
		transform->height = collider.h;
		transform->width = collider.w;

		if (tag == "hole")
		{
			texture_ = App::CreateSprite("resources/map/hole.png", 1, 1);
		}
		else
		{
			// Comment out to hide collider sprite
			texture_ = App::CreateSprite("resources/map/collisionTexture.png", 1, 1);
		}

		texture_->SetScale(transform->scale);
	}

	void update() override
	{
		if (tag != "terrain" && tag != "hole")
		{
			collider.w = transform->width * transform->scale;
			collider.h = transform->height * transform->scale;
		}
		if (tag == "terrain")
		{
			// I find the collisions work better with this scale
			collider.w = transform->width + 16.0f;
			collider.h = transform->height + 16.0f;
		}
		collider.position.x = transform->position.x + colliderSize / 2;
		collider.position.y = transform->position.y + colliderSize / 2;

		float drawX = transform->position.x - Game::camera.position.x + (colliderSize) / 2;
		float drawY = transform->position.y - Game::camera.position.y + (colliderSize) / 2;
		texture_->SetPosition(drawX, drawY);
	}

	void draw() override
	{
		texture_->Draw();
	}
};