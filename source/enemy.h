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
    // change transform by 1.0 unit when accumulatedDelta reaches 1.0
    float accumulatedTime;

public:
    void on_update(float dt, Transform2D &transform, const DungeonRestrictor &restrictor, Stamina &stamina, World *world, FOOD_SOURCES_TYPE &food_source, Health &health);
};
