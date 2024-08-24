#pragma once

#include <SDL.h>
#include <stdio.h>
#include <vector>

#include "Entity.h"

class Scene
{
private:

protected:
	std::vector<Entity*> allEntities;
	bool isActive = false;

public:
	~Scene();
	void SetActive() { isActive = true; }
	virtual void InitializeScene();
	virtual void RunScene();
	void Deactivate() { isActive = false; }
};

