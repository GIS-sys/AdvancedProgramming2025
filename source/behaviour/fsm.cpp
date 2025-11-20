#include "behaviour/fsm.h"
#include "world.h"
#include "food_consumer.h"
#include "predator.h"
#include <algorithm>
#include <limits>
#include <iostream>

BehaviourFSM::BehaviourFSM(FOOD_SOURCES_TYPE foodSourceType)
    : BehaviourBase(foodSourceType), currentState(BehaviourState::IDLE)
{
}

void BehaviourFSM::switchToState(BehaviourState newState)
{
    stateChanged = (currentState != newState);
    currentState = newState;
}

void BehaviourFSM::update(BehaviourUpdateData data)
{
    changeState(data);
    executeState(data);
}

void BehaviourFSM::changeState(BehaviourUpdateData data)
{
    // ANY -> AVOID_PREDATORS
    if (std::holds_alternative<FoodConsumer>(foodSourceType) && hasPredatorNearby(data.world, data.currentPos))
    {
        switchToState(BehaviourState::AVOID_PREDATORS);
        return;
    }

    switch (currentState)
    {
    case BehaviourState::IDLE:
        // IDLE -> FEED
        if (data.stamina.current < 30 || data.health.current < 30)
        {
            if (data.stamina.current > data.health.current)
            {
                switchToState(BehaviourState::FEED_HEALTH);
                return;
            }
            else
            {
                switchToState(BehaviourState::FEED_STAMINA);
                return;
            }
        }
        // IDLE -> MATE
        if (data.health.current > 90)
        {
            switchToState(BehaviourState::MATE);
            return;
        }
        break;
    case BehaviourState::AVOID_PREDATORS:
        // AVOID_PREDATORS -> IDLE
        if (!hasPredatorNearby(data.world, data.currentPos))
        {
            switchToState(BehaviourState::IDLE);
            return;
        }
        break;
    case BehaviourState::FEED_HEALTH:
        if (data.health.current > 50)
            switchToState(BehaviourState::IDLE);
        break;
    case BehaviourState::FEED_STAMINA:
        if (data.health.current > 50)
            switchToState(BehaviourState::IDLE);
        break;
    case BehaviourState::MATE:
        if (data.health.current < 80)
        {
            switchToState(BehaviourState::IDLE);
            return;
        }
        break;
    default:
        break;
    }
}

void BehaviourFSM::executeState(BehaviourUpdateData data)
{
    if (!stateChanged && data.currentPos != currentTarget)
        return;

    switch (currentState)
    {
    case BehaviourState::AVOID_PREDATORS:
        currentTarget = findOppositeToClosestPredator(data.world, data.currentPos, data.pathfinder);
        break;
    case BehaviourState::FEED_HEALTH:
        if (std::holds_alternative<FoodConsumer>(foodSourceType))
            currentTarget = findClosestFoodHealth(data.world, data.currentPos, data.pathfinder);
        else
            currentTarget = findClosestFoodConsumer(data.world, data.currentPos, data.pathfinder);
        break;
    case BehaviourState::FEED_STAMINA:
        if (std::holds_alternative<FoodConsumer>(foodSourceType))
            currentTarget = findClosestFoodStamina(data.world, data.currentPos, data.pathfinder);
        else
            currentTarget = findClosestFoodConsumer(data.world, data.currentPos, data.pathfinder);
        break;
    case BehaviourState::IDLE:
        currentTarget = data.restrictor.dungeon->getRandomFloorPosition();
        break;
    case BehaviourState::MATE:
        if (std::holds_alternative<FoodConsumer>(foodSourceType))
            currentTarget = findClosestFoodConsumer(data.world, data.currentPos, data.pathfinder);
        else
            currentTarget = findClosestPredator(data.world, data.currentPos, data.pathfinder);
        break;
    default:
        break;
    }
}
