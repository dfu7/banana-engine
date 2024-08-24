#include "Scene.h"

void Scene::InitializeScene()
{
    // override
}

void Scene::RunScene()
{
    // override
}

Scene::~Scene()
{
    for (Entity* entity : allEntities)
    {
        delete entity;
    }
}