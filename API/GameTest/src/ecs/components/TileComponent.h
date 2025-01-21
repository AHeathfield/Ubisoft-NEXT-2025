// TileComponent.h
#pragma once

#include "src/ecs/ECS.h"
#include "TransformComponent.h"
#include "src/graphics/shapes/Rect.h"
#include "App/app.h"
#include "Game.h"

// This should probably be put in stdafx.h or something
//#define PIXEL_SIZE 32
/*
 *	For the tile map
 */
class TileComponent : public Component
{
public:
	//TransformComponent* transform;
	//SpriteComponent* sprite;

	//Rect tileRect;
	//int tileID;						// Will automatically assign texture when create a tile
	//char* path;

	CSimpleSprite* texture;
	Rect tile;
	float tileSize_;
	float mapScale_;

	TileComponent() = default;

	TileComponent(int rows, int cols, const physics::Vector3& position, int spriteNum, float tileSize, float mapScale, const char* path)
	{
		tileSize_ = tileSize;
		tile.position = position;
		mapScale_ = mapScale;

		texture = App::CreateSprite(path, cols, rows);
		texture->SetFrame(spriteNum);	// This is texture in the tileset
		texture->SetScale(mapScale);
	}

	~TileComponent()
	{
		delete texture;
	}


	// ====== OVERRIDES ======
	void update() override
	{
		// Updating where we need to draw the image on the screen and adjusting since sprites are drawn from center
		texture->SetPosition(tile.position.x - Game::camera.position.x + (tileSize_ * mapScale_) / 2, tile.position.y - Game::camera.position.y + (tileSize_ * mapScale_) / 2);
	}

	void draw() override
	{
		texture->Draw();
	}


	/*void init() override
	{
		entity->addComponent<TransformComponent>(physics::Vector3(static_cast<float>(tileRect.x), static_cast<float>(tileRect.y), 0.0f), 1.0f, tileRect.w, tileRect.h);
		transform = &entity->getComponent<TransformComponent>();

		entity->addComponent<SpriteComponent>(path);
		sprite = &entity->getComponent<SpriteComponent>();
	}*/
};