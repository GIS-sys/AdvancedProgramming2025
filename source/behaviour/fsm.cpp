#include "fsm.h"
#include "world.h"
#include "food_consumer.h"
#include "predator.h"
#include <algorithm>
#include <limits>
#include <iostream>

FSM::FSM(FOOD_SOURCES_TYPE foodSourceType)
    : foodSourceType(foodSourceType), currentState(BehaviourState::IDLE)
{
}

void FSM::update(World *world, const int2 &currentPos, Stamina &stamina, Health &health)
{
    if (std::holds_alternative<FoodConsumer>(foodSourceType))
    {
        updateFoodConsumer(world, currentPos, stamina, health);
    }
    else
    {
        updatePredator(world, currentPos, stamina, health);
    }
}

int2 FSM::getTarget(World *world, const int2 &currentPos, const DungeonRestrictor &restrictor, const Pathfinder &pathfinder) const
{
    switch (getCurrentState())
    {
    case BehaviourState::AVOID_PREDATORS:
        return findOppositeToClosestPredator(world, currentPos, pathfinder);
    case BehaviourState::FIND_FOOD:
        return findClosestFood(world, currentPos, pathfinder);
    case BehaviourState::IDLE:
        return restrictor.dungeon->getRandomFloorPosition();
    case BehaviourState::MATE:
        return findClosestMate(world, currentPos, pathfinder, foodSourceType);
    case BehaviourState::HUNT:
        return findClosestFoodConsumer(world, currentPos, pathfinder);
    }
    return currentPos;
}

void FSM::updateFoodConsumer(World *world, const int2 &currentPos, Stamina &stamina, Health &health)
{
    if (hasPredatorNearby(world, currentPos))
    {
        currentState = BehaviourState::AVOID_PREDATORS;
    }
    else if (stamina.current < 30 || health.current < 30)
    {
        currentState = BehaviourState::FIND_FOOD;
    }
    else if (health.current > 80)
    {
        currentState = BehaviourState::MATE;
    }
    else
    {
        currentState = BehaviourState::IDLE;
    }
}

void FSM::updatePredator(World *world, const int2 &currentPos, Stamina &stamina, Health &health)
{
    if (health.current > 80)
    {
        currentState = BehaviourState::MATE;
    }
    else
    {
        currentState = BehaviourState::HUNT;
    }
}

bool FSM::hasPredatorNearby(World *world, const int2 &position, int distance)
{
    for (int i : world->getIndicesEnemiesHunters())
        if ((world->currentEnemies.transform2ds[i].point() - position).manhattanLength() < distance)
            return true;
    return false;
}

int2 FSM::findOppositeToClosestPredator(World *world, const int2 &position, const Pathfinder &pathfinder)
{
    int2 enemyPosition = findClosestPredator(world, position, pathfinder);
    int2 deltaToEnemy = enemyPosition - position;
    return position - deltaToEnemy.toDirection();
}

int2 FSM::findClosestFood(World *world, const int2 &position, const Pathfinder &pathfinder)
{
    int minIndex = 0;
    for (int i = 0; i < world->currentFoods.size(); ++i)
        if ((world->currentFoods.transform2ds[i].point() - position).manhattanLength() < (world->currentFoods.transform2ds[minIndex].point() - position).manhattanLength())
            minIndex = i;
    return world->currentFoods.transform2ds[minIndex].point();
}

int2 FSM::findClosestMate(World *world, const int2 &position, const Pathfinder &pathfinder, FOOD_SOURCES_TYPE foodSourceType)
{
    if (std::holds_alternative<FoodConsumer>(foodSourceType))
    {
        return findClosestFoodConsumer(world, position, pathfinder);
    }
    else
    {
        return findClosestPredator(world, position, pathfinder);
    }
}

int2 FSM::findClosestPredator(World *world, const int2 &position, const Pathfinder &pathfinder)
{
    // TODO
    int minIndex = 0;
    for (int i : world->getIndicesEnemiesHunters())
    {
        if (world->currentEnemies.transform2ds[i].point() == position)
            continue;
        if ((world->currentEnemies.transform2ds[i].point() - position).manhattanLength() < (world->currentEnemies.transform2ds[minIndex].point() - position).manhattanLength())
            minIndex = i;
    }
    return world->currentEnemies.transform2ds[minIndex].point();
}

int2 FSM::findClosestFoodConsumer(World *world, const int2 &position, const Pathfinder &pathfinder)
{
    // TODO
    int minIndex = 0;
    for (int i : world->getIndicesEnemiesGatherers())
    {
        if (world->currentEnemies.transform2ds[i].point() == position)
            continue;
        if ((world->currentEnemies.transform2ds[i].point() - position).manhattanLength() < (world->currentEnemies.transform2ds[minIndex].point() - position).manhattanLength())
            minIndex = i;
    }
    return world->currentEnemies.transform2ds[minIndex].point();
}
