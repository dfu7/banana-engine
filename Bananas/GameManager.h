#pragma once

#include <SDL.h>
#include <vector>
#include "Scene.h"

#undef main


class GameManager
{
private:
	// manual list of scenes
	std::vector<Scene*> scenes;
	Scene* activeScene;

public:
	GameManager();
	~GameManager();

	void CreateAllScenes();
	void RunActiveScene();
	void SetActiveScene(int sceneNum);

	void RunScenes();
};