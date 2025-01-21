// SpriteComponent.h
#pragma once

#include "Components.h"
#include "App/app.h"
#include "src/graphics/shapes/Rect.h"
#include "Game.h"

/*
 *	The sprite component gives entities textures.
 *	Key things to note is at least for now I'm using 32x32 texture
 */

class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	CSimpleSprite* sprite;
	Rect destRect;		// Where we are drawing

	bool animated = false;
	int frames = 0;
	int speed = 100;	// This is the delay between frames

public:
	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		setTexture(path);
	}
	SpriteComponent(const char* path, int frames_, int speed_)
	{
		animated = true;
		frames = frames_;
		speed = speed_;
		setTexture(path);
	}

	~SpriteComponent()
	{
		delete sprite;
	}


	// If texture needs to change
	void setTexture(const char* path)
	{
		sprite = App::CreateSprite(path, 1, 1);
	}

	physics::Vector3 getPosition()
	{
		float x = 0.0f;
		float y = 0.0f;
		sprite->GetPosition(x, y);
		return physics::Vector3(x, y, 0.0f);
	}

	// ====== OVERRIDES ======
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
	}


	void update() override
	{
		destRect.position = transform->position - Game::camera.position;
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;

		sprite->SetPosition(destRect.position.x, destRect.position.y);
		sprite->SetAngle(transform->rotation.getAngleRadians());
		sprite->SetScale(transform->scale);
	}

	void draw() override
	{
		//physics::Vector3 originalPos = transform->position;
		int height = static_cast<int>(destRect.h);
		int width = static_cast<int>(destRect.w);
		float tempX = 0.0f;
		float tempY = 0.0f;

		// Problem is that im drawing more sprites than I need to due to overlapping
		// I basically need to find how many 32x32 full sprites + bonus (so if the remaining value is < 32) I need to meet dimensions
		//
		// destRect / 32 = the number of 32x32 full sprites
		// temps = position after the first loop, we then go to the destRect dimensions - 32 (since 0,0 is bottom left)

		// Full sprites
		for (int y = 0; y < height / 32; y++)
		{
			for (int x = 0; x < width / 32; x++)
			{
				sprite->SetPosition(destRect.position.x + (32 * x), destRect.position.y + (32 * y));
				sprite->Draw();
			}
		}

		// Extra Overlaps
		sprite->GetPosition(tempX, tempY);
		for (int y = static_cast<int>(tempY + 1); y <= height - 32; y++)
		{
			for (int x = static_cast<int>(tempX + 1); x <= width - 32; x++)
			{
				sprite->SetPosition(destRect.position.x + x, destRect.position.y + y);
				sprite->Draw();
			}
		}
	}
};