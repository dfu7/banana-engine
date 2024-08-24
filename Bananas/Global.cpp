#include "Global.h"

#include <iostream>
#include <ctime>

std::default_random_engine randomEngine = std::default_random_engine{ static_cast<unsigned>(time(0)) };

SDL_Renderer* Global::renderer = NULL;
SDL_Window* Global::window = NULL;

float Global::SCREEN_CENTER_X = Global::SCREEN_WIDTH / 2;
float Global::SCREEN_CENTER_Y = Global::SCREEN_HEIGHT / 2;

Uint64 Global::NOW = SDL_GetPerformanceCounter();
Uint64 Global::LAST = 0;
double Global::deltaTime = 0;

void Global::UpdateVariables()
{
	CalculateDeltaTime();
}

void Global::CalculateDeltaTime()
{ 
	double step = 0;
	while (step < 0.10)
	{
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();

		deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
		step += deltaTime;
	}
	
	deltaTime /= 1000;
}

void Global::InitializeWindowAndRenderer()
{
	SDL_CreateWindowAndRenderer(
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_RESIZABLE,
		&window, &renderer);
}

int Global::RandomIntInRange(int min, int max)
{
	std::uniform_int_distribution<int> num(min, max);
	return num(randomEngine);
}

float Global::RandomFloatInRange(float min, float max)
{
	std::uniform_real_distribution<float> num(min, max);
	return num(randomEngine);
}