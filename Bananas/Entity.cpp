#include "Entity.h"

#include <iostream>
#include "Global.h"

Entity::Entity(const char textureFilePath[], float spawnX, float spawnY, bool canCollide) : canCollide(canCollide)
{
    SDL_Surface* spriteLoader;
    spriteLoader = SDL_LoadBMP(textureFilePath);

    originalTexture = SDL_CreateTextureFromSurface(Global::renderer, spriteLoader);
    currentTexture = originalTexture;
    SDL_FreeSurface(spriteLoader);

    bounds.w = Global::SCREEN_WIDTH / 10.f;
    bounds.h = Global::SCREEN_HEIGHT / 10.f;

    SetLocation(spawnX, spawnY);

    //std::cout << "bounds.x: " << bounds.x << ", bounds.y: " << bounds.y << ", bounds.w: " << bounds.w << ", bounds.h: " << bounds.h << std::endl;
}

void Entity::SetLocation(float locationX, float locationY)
{
    bounds.x = locationX - (bounds.w / 2);
    bounds.y = locationY - (bounds.h / 2);
}

void Entity::Move(float locationX, float locationY)
{
    bounds.x += locationX;
    bounds.y += locationY;
}

void Entity::UpdateRender()
{
    SDL_RenderCopyF(Global::renderer, currentTexture, NULL, &bounds);
}

void Entity::ToggleVisibility()
{
    isVisible = !isVisible;

    if (isVisible)
    {
        currentTexture = originalTexture;
    }
    else
    {
        currentTexture = nullptr;
    }
}

void Entity::DestroyTexture()
{
    SDL_DestroyTexture(originalTexture);
    SDL_DestroyTexture(currentTexture);
}

Entity::~Entity()
{
    DestroyTexture();
}