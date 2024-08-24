#pragma once

#include <SDL.h>

// anything that can be renderered on screen!
class Entity
{
public:
	SDL_Texture* originalTexture;
	SDL_Texture* currentTexture;
	SDL_FRect bounds;

	bool isVisible = true;
	bool canCollide = false;

public:
	Entity(
		const char textureFilePath[], 
		float spawnX,
		float spawnY,
		bool canCollide
		);

	~Entity();

	void SetLocation(float locationX, float locationY);
	virtual void Move(float moveX, float moveY);
	void UpdateRender();
	void ToggleVisibility();
	void DestroyTexture();
};

