#pragma once

#include <vector>
#include "Entity.h"

class LayerManager
{
public:
	struct EntityNode
	{
		class Entity* entity = nullptr;
		EntityNode* next = nullptr;
	};

	std::vector<EntityNode*> layers;

	~LayerManager();
public:
	LayerManager(unsigned int numOfLayers) : layers(numOfLayers) {};
	void AddEntityToRender(Entity* entity, unsigned int layer);
	void UpdateEntities();
};
