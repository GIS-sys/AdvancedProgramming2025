#pragma once

#include "food_sources.h"
#include "pathfinder.h"
#include "stamina.h"
#include "health.h"

class World;

struct BehaviourUpdateData
{
    World *world;
    const int2 &currentPos;
    const DungeonRestrictor &restrictor;
    const Pathfinder &pathfinder;
    Stamina &stamina;
    Health &health;
};

class BehaviourBase
{
protected:
    FOOD_SOURCES_TYPE foodSourceType;
    int2 currentTarget;

public:
    int2 getTarget() const { return currentTarget; }

    // Override these
    BehaviourBase(FOOD_SOURCES_TYPE foodSourceType) : foodSourceType(foodSourceType) {}
    void update(BehaviourUpdateData data) { currentTarget = data.currentPos; }
    // Override these

protected:
    static bool hasPredatorNearby(World *world, const int2 &position, int distance = 10);
    static int2 findOppositeToClosestPredator(World *world, const int2 &position, const Pathfinder &pathfinder);
    int2 findClosestFood(World *world, const int2 &position, const Pathfinder &pathfinder);
    int2 findClosestFoodHealth(World *world, const int2 &position, const Pathfinder &pathfinder);
    int2 findClosestFoodStamina(World *world, const int2 &position, const Pathfinder &pathfinder);
    template <typename F>
    int2 findClosestFood(World *world, const int2 &position, const Pathfinder &pathfinder, F &&lambdaFilter);
    static int2 findClosestFoodConsumer(World *world, const int2 &position, const Pathfinder &pathfinder);
    static int2 findClosestPredator(World *world, const int2 &position, const Pathfinder &pathfinder);
};
