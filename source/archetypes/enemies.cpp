#pragma once

#include <vector>

#include "archetypes/enemies.h"
#include "world.h"

void EnemiesArchetype::update(int i, float dt, World *world)
{
    if (std::holds_alternative<Predator>(foodsources[i]))
        std::get<Predator>(foodsources[i]).on_update(dt, world, transform2ds[i], healths[i], staminas[i], ids[i]);
    else
        std::get<FoodConsumer>(foodsources[i]).on_update(dt, world, transform2ds[i], healths[i], staminas[i]);
    enemies[i].on_update(dt, transform2ds[i], irestrictors[i], world, healths[i], staminas[i]);
}
