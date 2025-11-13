#pragma once

#include "transform2d.h"
#include "health.h"
#include "stamina.h"

class World;

class FoodConsumer
{
public:
    void on_update(float dt, World *world, Transform2D &myTransform, Health &myHealth, Stamina &myStamina);
};
