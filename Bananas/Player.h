#pragma once

#include "Entity.h"

class Player : public Entity
{
private:
	float speed = 300.f;
	int coins = 0;
public:
	using Entity::Entity;

	float getSpeed() { return speed; }
	int getCoins() { return coins; }
	void addCoins(unsigned int i) { coins += i; }
	void removeCoins(unsigned int i) { coins -= i; }

	void Move(float moveX, float moveY) override;
};

