#pragma once

#include <map>
#include <vector>
#include <utility>
#include "Entity.h"
#include "LayerManager.h"

class Shop
{
private:
	// selection indicator
	Entity* selector;

	// item and cost
	std::vector<std::pair<Entity*, int>> items;

	// locations for the selection
	int selectorIndex = 0;
	std::vector<std::pair<float, float>> shopSlotLocations;

	int shopSize = 0;
public:
	Shop(int size, LayerManager* layerManager);
	~Shop();
	
	bool isOpen = false;

	void OpenShop();
	void AddItem(Entity* item, int cost);
	void RemoveItem(Entity* item);
	void CloseShop();

	void MoveIndicatorRight();
	void MoveIndicatorLeft();
};