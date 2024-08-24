#include "Player.h"

#include <iostream>
#include "Global.h"

void Player::Move(float moveX, float moveY)
{
	bounds.x += moveX * speed * (float)Global::deltaTime;
	bounds.y += moveY * speed * (float)Global::deltaTime;
}
