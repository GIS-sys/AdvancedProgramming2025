#pragma once

#include "archetypes/heroes.h"
#include "world.h"

void HeroesArchetype::update(int i, float dt, World *world)
{
    foodsources[i].on_update(dt, world, transform2ds[i], healths[i], staminas[i]);
    heroes[i].on_update(dt, transform2ds[i], irestrictors[i], staminas[i]);
}
