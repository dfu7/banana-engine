#pragma once

#include <SDL.h>

#include <random>

namespace Global
{
	static std::default_random_engine randomEngine;

	extern SDL_Renderer* renderer;
	extern SDL_Window* window;

	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	extern float SCREEN_CENTER_X;
	extern float SCREEN_CENTER_Y;

	extern Uint64 NOW;
	extern Uint64 LAST;
	extern double deltaTime;

	void UpdateVariables();

	void CalculateDeltaTime();
	void InitializeWindowAndRenderer();

	int RandomIntInRange(int min, int max);
	float RandomFloatInRange(float min, float max);

	template<class T>
	inline T* Spawn(const char textureFilePath[], float spawnX, float spawnY, bool canCollide)
	{
		return new T(textureFilePath, spawnX, spawnY, canCollide);
	}
}