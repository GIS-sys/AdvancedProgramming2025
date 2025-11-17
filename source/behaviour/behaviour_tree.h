#pragma once

#include "dungeon_restrictor.h"
#include "transform2d.h"
#include "food_sources.h"
#include "health.h"
#include "pathfinder.h"

class World;

class BehaviourTree
{
public:
    void decide(World *world, const DungeonRestrictor &restrictor, Transform2D &transform, FOOD_SOURCES_TYPE &food_source, Health &health, Pathfinder &pathfinder);
};
