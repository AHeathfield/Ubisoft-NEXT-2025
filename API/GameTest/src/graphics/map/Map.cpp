// Map.cpp

#include "stdafx.h"
#include "Map.h"
#include "Game.h"
#include <fstream>	// Allows us to read file
#include "src/ecs/ECS.h"
#include "src/ecs/components/Components.h"

/*
 *	This is the tilemap of the entire screen.
 *	Check the txt files in the resources/map/ they will have a 2D array of numbers
 *	The files can be made using software like aseprite
 *	Basically the number values represent textures,
 *	ex 0 will be grass
 *	At the bottom of GameTest, that's where we create an entity for each pixel (32x32) and its given a TileComponent
 *	The values defined in TileComponent then correspond wiht the txt numbers to reproduce the map
 */

extern Manager manager;	// This basically says we are going to have a manager object defined somewhere else

Map::Map(const char* mapFilePath, const char* tileSetPath, float tileSize, float mapScale)
	: mapFilePath_(mapFilePath)
	, tileSetPath_(tileSetPath)
	, tileSize_(tileSize)
	, mapScale_(mapScale)
{
	scaledSize_ = tileSize * mapScale;
}

Map::~Map()
{
}

// Currently the map can only have 10 textures, this can be changed by having the map.txt include more digits
// Ex if I want 100 textures, 1,2,3,4 will become, 01,02,03,04 and then you can add all the way 00 -> 99
// For now I only need 10 textures
void Map::LoadMap(int mapRows, int mapCols, int tileSetRows, int tileSetCols)
{
	char tileNum;
	std::fstream mapFile;
	mapFile.open(mapFilePath_);

	int spriteNum;

	for (int y = mapCols - 1; y >= 0; y--)
	{
		for (int x = 0; x < mapRows; x++)
		{
			mapFile.get(tileNum);
			spriteNum = atoi(&tileNum);
			physics::Vector3 position = physics::Vector3(x * scaledSize_, y * scaledSize_, 0.0f);
			// void AddTile(int rows, int cols, const physics::Vector3& position, int spriteNum)
			AddTile(tileSetRows, tileSetCols, position, spriteNum);
			mapFile.ignore(); // ignores comma in the txt file
		}
	}

	// This ignores the blank line between the map texture and its corresponding colliders
	mapFile.ignore();

	// This loads our colliders
	for (int y = mapCols - 1; y >= 0; y--)
	{
		for (int x = 0; x < mapRows; x++)
		{
			mapFile.get(tileNum);
			if (tileNum == '1')
			{
				auto& textureCollider(manager.addEntity());
				physics::Vector3 position = physics::Vector3(x * scaledSize_, y * scaledSize_, 0.0f);
				// ColliderComponent(std::string tag_, const physics::Vector3& position, float size, float scale)
				textureCollider.addComponent<ColliderComponent>("terrain", position, scaledSize_, mapScale_);
				textureCollider.addGroup(Game::groupColliders);
			}
			else if (tileNum == '2')
			{
				auto& textureCollider(manager.addEntity());
				physics::Vector3 position = physics::Vector3(x * scaledSize_, y * scaledSize_, 0.0f);
				textureCollider.addComponent<ColliderComponent>("hole", position, scaledSize_, mapScale_);
				textureCollider.addGroup(Game::groupColliders);
			}
			mapFile.ignore();
		}
	}

	mapFile.close();
}


void Map::AddTile(int rows, int cols, const physics::Vector3& position, int spriteNum)
{
	auto& tile(manager.addEntity());
	// TileComponent(int rows, int cols, const physics::Vector3& position, int spriteNum, float tileSize, float mapScale, const char* path)
	tile.addComponent<TileComponent>(rows, cols, position, spriteNum, tileSize_, mapScale_, tileSetPath_);
	tile.addGroup(Game::groupMap);
}