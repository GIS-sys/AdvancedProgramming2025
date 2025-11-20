#include "behaviour/tree.h"
#include "world.h"

#include "behaviour/tree/condition.h"
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
    auto root = new BehaviourTreeNodeCondition([](BehaviourUpdateData data) -> bool
                                               { return data.health.current < 80; });
    rootNode = root;
    root->childLeft = new BehaviourTreeNodeDebug("child left");
    root->childRight = new BehaviourTreeNodeDebug("child right");
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
