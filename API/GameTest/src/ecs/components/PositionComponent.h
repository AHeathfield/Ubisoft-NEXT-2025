// PositionComponent.h
#pragma once

#include "Components.h"

// For now this is just to test the ECS and to use as an example to look back to
// I would probably just have a transform component, instead of a position, rotation, and scale component
// Just because the code will be very boiler plate adding those all time
class PositionComponent : public Component
{
private:
	int xpos;
	int ypos;

public:
	int x() { return xpos; }
	int y() { return ypos; }

	// ====== OVERRIDES ======
	void init() override
	{
		xpos = 0;
		ypos = 0;
	}

	void update() override
	{
		xpos++;
		ypos++;
	}

	void setPos(int x, int y)
	{
		xpos = x;
		ypos = y;
	}
};