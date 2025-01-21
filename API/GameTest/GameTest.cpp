///////////////////////////////////////////////////////////////////////////////
// Filename: GameTest.cpp
// Provides a demo of how to use the API
///////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <cstdio>	// For sprintf
#include <windows.h> 
#include <math.h>
#include <atomic>
#include <vector>
#include "App/app.h"
#include "src\core\Clock.h"
#include "src/core/inputs/InputHandler.h"
#include "src/core/inputs/PlayerCommands.h"

// ====== NEW ======
#include "src/graphics/map/Map.h"
#include "src/ecs/ECS.h"
#include "src/ecs/components/Components.h"
#include "src/new/Collision.h"
#include "src/graphics/shapes/Circle.h"
#include "Game.h"

// This is how to print to output
/*sprintf(debug, "Test\n");	// DELETE
OutputDebugStringA(debug);	// DELETE*/

struct GameplayData
{
	Clock clock = Clock(false);	// Infinite clock

};



GameplayData gameData;
physics::Vector3 centerScreen = physics::Vector3(APP_VIRTUAL_WIDTH / 2.0f, APP_VIRTUAL_HEIGHT / 2.0f, 0.0f);	// Problem something I should remove in future (seems like the camera should be able to handle this type of stuff

// ====== NEW For actual competition ======
// Some constants
constexpr float MAP_SCALE = 2.0f;

int currentMap = 0;
bool changeMap = false;
std::vector<Map*> maps;
Map* map1;
Map* map2;
Manager manager;
std::shared_ptr<InputHandler> playerInputs;
Rect Game::camera = Rect(0, 0, APP_VIRTUAL_WIDTH * MAP_SCALE, APP_VIRTUAL_HEIGHT * MAP_SCALE);
auto& player(manager.addEntity());

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	/* FOR printing to terminal
	char debug[50];
	sprintf(debug, "Test\n");
	OutputDebugStringA(debug);
	*/

#pragma region demo
	// Starting Clock
	gameData.clock.start();
#pragma endregion

	// ====== All new things ======
	// Map(const char* mapFilePath, const char* tileSetPath, int tileSize, float mapScale);
	// void LoadMap(int mapRows, int mapCols, int tileSetRows, int tileSetCols);
	maps.push_back(new Map("resources/map/testMap.txt", "resources/map/testTileSet.png", 32, MAP_SCALE));
	maps.push_back(new Map("resources/map/testMap2.txt", "resources/map/testTileSet.png", 32, MAP_SCALE));
	maps[currentMap]->LoadMap(32, 24, 1, 6);

	physics::Vector3 defaultRot = physics::Vector3(0.0f, 1.0f, 0.0f);

	player.addComponent<TransformComponent>(centerScreen, defaultRot, 1.0f);
	player.addComponent<SpriteComponent>("resources/golfballs/white_32x32.png");
	//ParticleColliderComponent(std::string tag_, float radius, float scale)
	player.addComponent<ParticleColliderComponent>("player", 16.0f, 1.0f);
	player.addGroup(Game::groupPlayers);

	// Inputs
	std::shared_ptr<MoveUpCommand> keyW = std::make_shared<MoveUpCommand>(player);
	std::shared_ptr<MoveLeftCommand> keyA = std::make_shared<MoveLeftCommand>(player);
	std::shared_ptr<MoveDownCommand> keyS = std::make_shared<MoveDownCommand>(player);
	std::shared_ptr<MoveRightCommand> keyD = std::make_shared<MoveRightCommand>(player);
	std::shared_ptr<LaunchBallCommand> mouseL = std::make_shared<LaunchBallCommand>(player);
	playerInputs = std::make_shared<InputHandler>(keyW, keyA, keyS, keyD, mouseL);
}

// List of groups to render (in order)
auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(const float deltaTime)
{
	gameData.clock.update(deltaTime / 1000.0f);

	if (changeMap && currentMap < maps.size())
	{
		currentMap++;
		for (int i = 0; i < colliders.size(); i++)
		{
			if (!colliders[i]->hasComponent<ParticleColliderComponent>())
			{
				colliders[i]->destroy();
			}
		}
		for (int i = 0; i < tiles.size(); i++)
		{
			tiles[i]->destroy();
		}
		manager.refresh();
		maps[currentMap]->LoadMap(32, 24, 1, 6);
		changeMap = false;
	}

	// ======= NEW For Competiton =======
	Circle playerColl = player.getComponent<ParticleColliderComponent>().collider;
	physics::Vector3 playerPos = player.getComponent<TransformComponent>().position;	// This acts as memory of the players last position before they move
	auto& pTransform = player.getComponent<TransformComponent>();

	playerInputs->handleInput();	// Handle all player inputs
	manager.refresh();				// Removes any inactive entities
	manager.update();				// Will update all entities, entities updates components

	// Each collider in colliders, will be checking player Collider against map colliders
	// This part will be hard coded and moved to a method later
	float damp = 0.8;
	bool xCollision = false;
	bool yCollision = false;
	bool isColliding = false;
	for (auto& c : colliders)
	{
		Rect box = c->getComponent<ColliderComponent>().collider;

		if (Collision::ballToBox(box, playerColl))
		{
			// Next Level!!!
			if (c->getComponent<ColliderComponent>().tag == "hole")
			{
				changeMap = true;
				pTransform.position = centerScreen;
				break;
			}
			if (isColliding)
			{
				continue;
			}

			xCollision = false;
			yCollision = false;

			if (playerColl.position.x - playerColl.radius < box.position.x - box.w / 2)
			{
				if (pTransform.velocity.x > 0)
				{
					xCollision = true;
				}
			}
			else if (playerColl.position.x + playerColl.radius > box.position.x + box.w / 2)
			{
				//sprintf(debug, "right\n");
				//OutputDebugStringA(debug);
				if (pTransform.velocity.x < 0)
				{
					xCollision = true;
				}
			}

			if (playerColl.position.y - playerColl.radius < box.position.y - box.h / 2)
			{
				//sprintf(debug, "bottom\n");
				//OutputDebugStringA(debug);
				if (pTransform.velocity.y > 0)
				{
					yCollision = true;
				}
			}
			else if (playerColl.position.y + playerColl.radius > box.position.y + box.h / 2)
			{
				//sprintf(debug, "top\n");
				//OutputDebugStringA(debug);
				if (pTransform.velocity.y < 0)
				{
					yCollision = true;
				}
			}

			if (xCollision && yCollision)
			{
				pTransform.velocity.x *= -1.0f * damp;  // Reflect the x velocity
				pTransform.velocity.y *= -1.0f * damp;  // Reflect the y velocity

				float cornerDampFactor = 0.8f;
				pTransform.velocity.x *= cornerDampFactor;
				pTransform.velocity.y *= cornerDampFactor;
			}
			else if (xCollision)
			{
				pTransform.velocity.x *= -1.0f * damp;
			}
			else if (yCollision)
			{
				pTransform.velocity.y *= -1.0f * damp;
			}
		}
		else
		{
			isColliding = false;
		}
	}

	// Updates Camera Position
	Game::camera.position.x = player.getComponent<TransformComponent>().position.x - (APP_VIRTUAL_WIDTH / 2);
	Game::camera.position.y = player.getComponent<TransformComponent>().position.y - (APP_VIRTUAL_HEIGHT / 2);

	// Setting bounds for camera
	// This is temp, would only work if map is exactly screen size
	int mapScale = static_cast<int>(MAP_SCALE);
	if (mapScale == 1)
	{
		Game::camera.position.zero();
	}
	else
	{
		if (Game::camera.position.x < 0)
			Game::camera.position.x = 0;
		if (Game::camera.position.y < 0)
			Game::camera.position.y = 0;
		if (Game::camera.position.x > Game::camera.w - (APP_VIRTUAL_WIDTH))
			Game::camera.position.x = Game::camera.w - (APP_VIRTUAL_WIDTH);
		if (Game::camera.position.y > Game::camera.h - (APP_VIRTUAL_HEIGHT))
			Game::camera.position.y = Game::camera.h - (APP_VIRTUAL_HEIGHT);
	}
}


//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{
	// This will draw entity in group
	for (auto& tile : tiles)
	{
		tile->draw();
	}
	for (auto& coll : colliders)
	{
		coll->draw();
	}
	for (auto& player : players)
	{
		player->draw();
	}
}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{
	//------------------------------------------------------------------------
	// Example Sprite Code....
	//delete playerOLD;
	//delete background;
	//------------------------------------------------------------------------
}