#pragma once

#include "behaviour/base.h"

#include <string>

class World;

class BehaviourTree : public BehaviourBase
{
public:
    BehaviourTree(FOOD_SOURCES_TYPE foodSourceType);
    void update(World *world, const int2 &currentPos, const DungeonRestrictor &restrictor, const Pathfinder &pathfinder, Stamina &stamina, Health &health);
};
