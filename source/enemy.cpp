#pragma once

#include "enemy.h"
#include "world.h"

void Enemy::on_update(float dt, Transform2D &transform, const DungeonRestrictor &restrictor, Stamina &stamina, World *world, FOOD_SOURCES_TYPE &food_source, Health &health)
{
    accumulatedTime += dt * stamina.get_speed();
    if (accumulatedTime < 1.0f)
        return;
    accumulatedTime -= 1.0f;

    behaviour.decide(world, restrictor, transform, food_source, health, pathfinder);
}
