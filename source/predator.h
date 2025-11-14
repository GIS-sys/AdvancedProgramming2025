#pragma once

#include "health.h"
#include "transform2d.h"
#include "archetypes/archetype.h"

class World;

class Predator
{
public:
    void on_update(float dt, World *world, Transform2D &myTransform, Health &myHealth, TYPE_ID myID);
};
