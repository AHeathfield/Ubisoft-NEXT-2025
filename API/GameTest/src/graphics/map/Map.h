// map.h
#pragma once

#include "stdafx.h"
#include <string>

/*
 *	Will be used to create levels. Essentially its a tilemap like in other game engines.
 *	By default API sets width to 1024 height to 768. Doing 32 bits (can change this if needed)
 *	so that will make 32 columns and 24 rows
 *	I might make this extend GameObject
 *	Refer to background to help with sprite implementation
 *
 *	Cool thing about draw is I can use the same sprite and draw it multiple times to the screen
 */
class Map
{
private:
	const char* mapFilePath_;
	const char* tileSetPath_;
	float tileSize_;
	float mapScale_;
	float scaledSize_;

public:
	Map(const char* mapFilePath, const char* tileSetPath, float tileSize, float mapScale);
	~Map();

	void LoadMap(int mapRows, int mapCols, int tileSetRows, int tileSetCols);
	void AddTile(int rows, int cols, const physics::Vector3& position, int spriteNum);
};