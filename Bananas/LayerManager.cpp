#include "LayerManager.h"

#include "Global.h"

LayerManager::~LayerManager()
{
	for (EntityNode* layer : layers)
	{
		delete layer;
	}
}

void LayerManager::AddEntityToRender(Entity* entity, unsigned int layer)
{
	// cap input layer
	if (layer > layers.size() - 1) { layer = layers.size() - 1; }

	// add new object to layer
	EntityNode* newHead = new EntityNode();
	newHead->entity = entity;
	newHead->next = layers[layer];
	layers[layer] = newHead;
}

void LayerManager::UpdateEntities()
{
	SDL_RenderClear(Global::renderer);
	// render entities for each layer
	for (EntityNode* layer : layers)
	{
		EntityNode* curr = layer;
		while (curr != nullptr)
		{
			curr->entity->UpdateRender();
			curr = curr->next;
		}
	}
	SDL_RenderPresent(Global::renderer);
}