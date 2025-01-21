// Game.h
#pragma once

#include <vector>
#include "src/graphics/shapes/Rect.h"

/*
 *	Class holds game information
 *	This will hold static variables for now, HOPEFULLY WILL REMOVE :(
 */

class ColliderComponent;	// This is because we don't need the full header file for this I think

class Game
{
public:
	// Defining groups
	enum groupLabels : std::size_t
	{
		groupMap,
		groupPlayers,
		groupColliders
	};
	static std::vector<ColliderComponent*> colliders;
	static Rect camera;
};
