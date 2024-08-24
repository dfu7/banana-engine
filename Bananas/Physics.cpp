#include "Physics.h"


bool Physics::CheckCollision(Entity* first, Entity* second)
{
    if (first->canCollide == false || second->canCollide == false) { return false; }

    if (second->bounds.x > (first->bounds.x + first->bounds.w) ||
        (second->bounds.y + second->bounds.h) < (first->bounds.y) ||
        first->bounds.x > (second->bounds.x + second->bounds.w) ||
        (first->bounds.y + first->bounds.h) < second->bounds.y)
    {
        return false;
    }

    return true;
}