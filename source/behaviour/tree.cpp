#include "behaviour/tree.h"
#include "world.h"

#include "behaviour/tree/action.h"
#include "behaviour/tree/condition.h"
#include "behaviour/tree/consequitive.h"
#include "behaviour/tree/debug.h"

BehaviourTree::BehaviourTree(FOOD_SOURCES_TYPE foodSourceType)
    : BehaviourBase(foodSourceType)
{
    buildTree();
    rootNode->build(nullptr);
    currentNode = rootNode;
}

void BehaviourTree::buildTree()
{
    // TODO
    if (std::holds_alternative<Predator>(foodSourceType))
    {
        rootNode = new BehaviourTreeNodeCondition(
            [](BehaviourUpdateData data) -> bool
            { return data.health.current < 90; },

            new BehaviourTreeNodeConsequitive({
                new BehaviourTreeNodeDebug("PREDATOR MATE"),
                new BehaviourTreeNodeAction(
                    [](BehaviourUpdateData data, int2 &currentTarget) -> bool
                    {
                        currentTarget = findClosestPredator(data.world, data.currentPos, data.pathfinder);
                        return true;
                    },
                    {0.9f, 0.3f, 0.5f}),
                new BehaviourTreeNodeAction(
                    [](BehaviourUpdateData data, int2 &currentTarget) -> bool
                    {
                        if (data.health.current < 80 || data.stamina.current < 50)
                            return true;
                        return data.currentPos == currentTarget;
                    },
                    {0.9f, 0.3f, 0.5f}),
            }),

            new BehaviourTreeNodeConsequitive({
                new BehaviourTreeNodeDebug("PREDATOR FEED"),
                new BehaviourTreeNodeAction(
                    [](BehaviourUpdateData data, int2 &currentTarget) -> bool
                    {
                        currentTarget = findClosestFoodConsumerOrHero(data.world, data.currentPos, data.pathfinder);
                        return true;
                    },
                    {0.3f, 0.5f, 0.5f}),
                new BehaviourTreeNodeAction(
                    [](BehaviourUpdateData data, int2 &currentTarget) -> bool
                    {
                        if (data.health.current > 90)
                            return true;
                        return data.currentPos == currentTarget;
                    },
                    {0.3f, 0.5f, 0.5f}),
            }));
    }
    else
    {
        rootNode = new BehaviourTreeNodeCondition(
            [](BehaviourUpdateData data) -> bool
            { return !hasPredatorNearby(data.world, data.currentPos); },

            new BehaviourTreeNodeConsequitive({
                new BehaviourTreeNodeDebug("CONSUMER AVOID"),
                new BehaviourTreeNodeAction(
                    [](BehaviourUpdateData data, int2 &currentTarget) -> bool
                    {
                        currentTarget = findOppositeToClosestPredator(data.world, data.currentPos, data.pathfinder, data.restrictor);
                        return true;
                    },
                    {0.9f, 0.3f, 0.3f}),
                new BehaviourTreeNodeAction(
                    [](BehaviourUpdateData data, int2 &currentTarget) -> bool
                    {
                        if (!hasPredatorNearby(data.world, data.currentPos))
                            return true;
                        return data.currentPos == currentTarget;
                    },
                    {0.9f, 0.3f, 0.3f}),
            }),

            new BehaviourTreeNodeCondition(
                [](BehaviourUpdateData data) -> bool
                { return data.health.current < 90; },

                new BehaviourTreeNodeConsequitive({
                    new BehaviourTreeNodeDebug("CONSUMER MATE"),
                    new BehaviourTreeNodeAction(
                        [](BehaviourUpdateData data, int2 &currentTarget) -> bool
                        {
                            currentTarget = findClosestPredator(data.world, data.currentPos, data.pathfinder);
                            return true;
                        },
                        {0.6f, 0.3f, 0.5f}),
                    new BehaviourTreeNodeAction(
                        [](BehaviourUpdateData data, int2 &currentTarget) -> bool
                        {
                            if (data.health.current < 80 || data.stamina.current < 50)
                                return true;
                            return data.currentPos == currentTarget;
                        },
                        {0.6f, 0.3f, 0.5f}),
                }),

                new BehaviourTreeNodeConsequitive({
                    new BehaviourTreeNodeDebug("CONSUMER FEED"),
                    new BehaviourTreeNodeAction(
                        [this](BehaviourUpdateData data, int2 &currentTarget) -> bool
                        {
                            if (data.health.current < data.stamina.current)
                                currentTarget = findClosestFoodHealth(data.world, data.currentPos, data.pathfinder);
                            else
                                currentTarget = findClosestFoodStamina(data.world, data.currentPos, data.pathfinder);
                            return true;
                        },
                        {0.3f, 0.7f, 0.7f}),
                    new BehaviourTreeNodeAction(
                        [](BehaviourUpdateData data, int2 &currentTarget) -> bool
                        {
                            if (data.health.current > 90)
                                return true;
                            return data.currentPos == currentTarget;
                        },
                        {0.3f, 0.7f, 0.7f}),
                })));
    }
}

void BehaviourTree::update(BehaviourUpdateData data)
{
    if (!rootNode)
    {
        std::cout << "ERROR" << std::endl;
        return;
    }
    currentNode->update(data, currentNode, currentTarget);
    if (!currentNode)
        currentNode = rootNode;
}
