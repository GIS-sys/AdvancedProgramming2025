#pragma once

#include "starvation_system.h"
#include "world.h"

void StarvationSystem::on_update(float dt, World *world)
{
    accumulator += dt;
    if (accumulator < damageInterval)
        return;
    accumulator -= damageInterval;
    for (int i = 0; i < world->currentHeroes.size(); ++i)
    {
        world->currentHeroes.healths[i].change(-damageAmount);
        if (world->currentHeroes.healths[i].current <= 0)
        {
            world.toDeleteHeroes.insert(world->currentHeroes.ids[i]);
        }
    }
    for (int i = 0; i < world->currentEnemies.size(); ++i)
    {
        world->currentEnemies.healths[i].change(-damageAmount);
        if (world->currentEnemies.healths[i].current <= 0)
        {
            world.toDeleteEnemies.insert(world->currentEnemies.ids[i]);
        }
    }
}
