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
        return findClosestNonPredator(world, currentPos, pathfinder);
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
    // TODO
    return false;
}

int2 FSM::findOppositeToClosestPredator(World *world, const int2 &position, const Pathfinder &pathfinder)
{
    // TODO
    return position;
}

int2 FSM::findClosestFood(World *world, const int2 &position, const Pathfinder &pathfinder)
{
    // TODO
    return position - int2{2, 0};
}

int2 FSM::findClosestNonPredator(World *world, const int2 &position, const Pathfinder &pathfinder)
{
    // TODO
    return position;
}

int2 FSM::findClosestFoodConsumer(World *world, const int2 &position, const Pathfinder &pathfinder)
{
    // TODO
    return position + int2{2, 0};
}
