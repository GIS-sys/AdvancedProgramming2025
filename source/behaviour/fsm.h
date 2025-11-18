#pragma once

#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include <string>
#include "math2d.h"
#include "food_sources.h"
#include "behaviour/state.h"
#include "stamina.h"
#include "health.h"
#include "dungeon_restrictor.h"
#include "pathfinder.h"

class World;

class FSM
{
public:
    FSM(FOOD_SOURCES_TYPE foodSourceType);

    void update(World *world, const int2 &currentPos, Stamina &stamina, Health &health);
    int2 getTarget(World *world, const int2 &currentPos, const DungeonRestrictor &restrictor, const Pathfinder &pathfinder) const;

    BehaviourState getCurrentState() const { return currentState; }

private:
    BehaviourState currentState;
    FOOD_SOURCES_TYPE foodSourceType;

    void updateFoodConsumer(World *world, const int2 &currentPos, Stamina &stamina, Health &health);
    void updatePredator(World *world, const int2 &currentPos, Stamina &stamina, Health &health);

    bool hasPredatorNearby(World *world, const int2 &position, float distance = 10.0f);
    static int2 findOppositeToClosestPredator(World *world, const int2 &position, const Pathfinder &pathfinder);
    static int2 findClosestFood(World *world, const int2 &position, const Pathfinder &pathfinder);
    static int2 findClosestMate(World *world, const int2 &position, const Pathfinder &pathfinder, FOOD_SOURCES_TYPE foodSourceType);
    static int2 findClosestFoodConsumer(World *world, const int2 &position, const Pathfinder &pathfinder);
    static int2 findClosestPredator(World *world, const int2 &position, const Pathfinder &pathfinder);
};
