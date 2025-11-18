#pragma once

#include "dungeon_restrictor.h"
#include "health.h"
#include "stamina.h"
#include "transform2d.h"
#include "pathfinder.h"
#include "food_sources.h"
#include "behaviour/init.h"
#include <SDL3/SDL.h>
#include <algorithm>

class World;

class Enemy
{
private:
    BEHAVIOUR_MANAGER behaviour;
    Pathfinder pathfinder;
    float accumulatedTime = 0.0f;

public:
    Enemy(FOOD_SOURCES_TYPE food_source) : behaviour(food_source) {}

    void on_update(float dt, Transform2D &transform, const DungeonRestrictor &restrictor, World *world, Stamina &stamina, Health &health);
};
