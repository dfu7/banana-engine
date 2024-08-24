#include "GameManager.h"

#include <SDL_ttf.h>
#include <iostream>
#include "Global.h"

// scenes
#include "Zyla.h"


GameManager::GameManager()
{
    Global::InitializeWindowAndRenderer();
    SDL_SetWindowTitle(Global::window, "FUCK AROUND AND FIND OUT");

    CreateAllScenes();
    SetActiveScene(0);
    RunActiveScene();
}

GameManager::~GameManager()
{
    for (Scene* scene : scenes)
    {
        delete scene;
    }

    SDL_DestroyRenderer(Global::renderer);
    SDL_DestroyWindow(Global::window);
    SDL_Quit();
}

void GameManager::CreateAllScenes()
{
    // manually create each scene and add to scenes list
    Zyla* scene1 = new Zyla();
    scenes.push_back(scene1);
}

void GameManager::RunActiveScene()
{
    if (!activeScene) { return; }
    activeScene->SetActive();
    activeScene->InitializeScene();
    activeScene->RunScene();
}

void GameManager::SetActiveScene(int sceneNum)
{
    if (sceneNum >= scenes.size()) { return; }

    activeScene = scenes[sceneNum];
}

void GameManager::RunScenes()
{
    
}