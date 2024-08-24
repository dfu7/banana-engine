#pragma once
#include "Scene.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "LayerManager.h"
#include "Entity.h"
#include "Player.h"
#include "Shop.h"


class Zyla : public Scene
{
private:
	LayerManager* layerManager;

	TTF_Font* Sans;
	SDL_Color White = { 255, 255, 255 };
	std::string numStr;
	char tab2[1024];
	SDL_Surface* CoinTextSurface;
	SDL_Texture* CoinText;
	SDL_Rect CoinTextRect;

	Player* player;
	Entity* rupee;
	Entity* ui_shop;
	Entity* ui_hotbar;

	Entity* r1;
	Entity* r2;
	Entity* r3;
	Entity* r4;

	Shop* shop;
public:
	void InitializeScene() override;
	void RunScene() override;
};