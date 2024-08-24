#include "Shop.h"

#include <iostream>
#include "Global.h"

Shop::Shop(int size, LayerManager* layerManager) : shopSize(size)
{
	// selector ui
	selector = Global::Spawn<Entity>("itemcontainer.bmp", 100.f, 100.f, false);
	selector->bounds.w = 85;
	selector->bounds.h = 75;
	selector->ToggleVisibility();

	// render selecter
	layerManager->AddEntityToRender(selector, 6);

	// setup empty item slots and shop slot locations
	std::cout << shopSize << std::endl;
	for (int i = 0; i < shopSize; ++i)
	{
		items.push_back(std::make_pair(nullptr, 0));

		shopSlotLocations.push_back(
			std::make_pair(
				Global::SCREEN_WIDTH * ((i + 1) / ((float)shopSize + 1)),
				Global::SCREEN_CENTER_Y
			)
		);

		std::cout << "X" << Global::SCREEN_WIDTH << std::endl;
		std::cout << ((i + 1) / (float)shopSize) << std::endl;
	}
}

Shop::~Shop()
{
	for (const auto& kv : items)
	{
		delete kv.first;
	}
}

void Shop::OpenShop()
{
	// evenly distribute all items in shop across the screen
	isOpen = true;
	
	for (int i = 0; i < shopSize; ++i)
	{
		if (items[i].first == nullptr) { continue; }
		items[i].first->SetLocation(shopSlotLocations[i].first, shopSlotLocations[i].second);
		items[i].first->ToggleVisibility();
	}

	selector->SetLocation(shopSlotLocations[0].first, shopSlotLocations[0].second);
	selector->ToggleVisibility();
}

void Shop::AddItem(Entity* item, int cost)
{
	// fill next empty slot with visibility off
	item->ToggleVisibility();

	// create item and add to list
	for (auto& kv : items)
	{
		if (kv.first == nullptr)
		{
			kv.first = item;
			kv.second = cost;
			break;
		}
	}
}

void Shop::RemoveItem(Entity* item)
{
	for (auto& kv : items)
	{
		if (kv.first == item)
		{
			kv.first = nullptr;
			// can set cost to 0 but not necessary because adding item only checks for item
			break;
		}
	}
}

void Shop::CloseShop()
{
	isOpen = false;
	for (const auto& kv : items)
	{
		if (kv.first == nullptr) { continue; }
		kv.first->ToggleVisibility();
	}
	selector->ToggleVisibility();
	selectorIndex = 0;
}

void Shop::MoveIndicatorRight()
{
	selectorIndex++;
	if (selectorIndex > shopSize - 1) { selectorIndex = 0; }
	selector->SetLocation(
		shopSlotLocations[selectorIndex].first,
		shopSlotLocations[selectorIndex].second
	);
}

void Shop::MoveIndicatorLeft()
{
	selectorIndex--;
	if (selectorIndex < 0) { selectorIndex = items.size() - 1; }
	selector->SetLocation(
		shopSlotLocations[selectorIndex].first,
		shopSlotLocations[selectorIndex].second
	);
}