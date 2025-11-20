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
            { return data.health.current > 90; },

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
                    {0.9f, 0.3f, 0.5f}),
                new BehaviourTreeNodeAction(
                    [](BehaviourUpdateData data, int2 &currentTarget) -> bool
                    {
                        if (data.health.current > 90)
                            return true;
                        return data.currentPos == currentTarget;
                    },
                    {0.9f, 0.3f, 0.5f}),
            }));
    }
    else
    {
        rootNode = new BehaviourTreeNodeDebug("CONSUMER");
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
