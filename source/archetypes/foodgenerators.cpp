#pragma once

#include "archetypes/foodgenerators.h"
#include "world.h"

void FoodGeneratorsArchetype::update(int i, float dt, World *world)
{
    foodgenerators[i].on_update(dt);
}