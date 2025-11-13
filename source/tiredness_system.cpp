#pragma once

#include "tiredness_system.h"
#include "world.h"

void TirednessSystem::on_update(float dt, World *world)
{
    accumulator += dt;
    if (accumulator < tirednessInterval)
        return;
    accumulator -= tirednessInterval;
    for (int i = 0; i < world->currentHeroes.size(); ++i)
    {
        world->currentHeroes.staminas[i].change(-tirednessAmount);
    }
    for (int i = 0; i < world->currentEnemies.size(); ++i)
    {
        world->currentEnemies.staminas[i].change(-tirednessAmount);
    }
}
