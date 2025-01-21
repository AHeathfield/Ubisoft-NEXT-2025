// ECS.cpp

#include "stdafx.h"
#include "ECS.h"

void Entity::addGroup(Group group_)
{
	groupBitSet[group_] = true;
	manager.AddToGroup(this, group_);
}