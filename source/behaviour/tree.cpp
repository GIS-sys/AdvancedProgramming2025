#include "behaviour/tree.h"
#include "world.h"

BehaviourTree::BehaviourTree(FOOD_SOURCES_TYPE foodSourceType)
    : BehaviourBase(foodSourceType)
{
}

void BehaviourTree::update(World *world, const int2 &currentPos, const DungeonRestrictor &restrictor, const Pathfinder &pathfinder, Stamina &stamina, Health &health)
{
    // TODO
    currentTarget = {32, 32};
}
