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
    auto root = std::make_shared<BehaviourTreeNodeCondition>([](BehaviourUpdateData data) -> bool
                                                             { return data.health.current < 80; });
    rootNode = root;
    root->childLeft = std::make_shared<BehaviourTreeNodeDebug>("child left");
    root->childRight = std::make_shared<BehaviourTreeNodeDebug>("child right");
    // auto root = std::make_shared<BehaviourTreeNodeDebug>("AAAAAAAA");
    // rootNode = root;
}

void BehaviourTree::update(BehaviourUpdateData data)
{
    // auto [r, g, b] = currentNode->getCurrentColor();
    // std::cout << r << g << b << std::endl;
    currentNode->update(data, currentNode, currentTarget);
    if (!currentNode)
        currentNode = rootNode;
}
