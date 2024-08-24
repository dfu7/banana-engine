#pragma once

#include "Entity.h"

namespace Physics
{
	bool CheckCollision(Entity* first, Entity* second); //aligned axis bounding box [optimize maybe quadtree]
};

