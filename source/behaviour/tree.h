#pragma once

#include "behaviour/base.h"
#include "behaviour/tree/base.h"

#include <string>

class World;

class BehaviourTree : public BehaviourBase
{
public:
    BehaviourTree(FOOD_SOURCES_TYPE foodSourceType);
    void update(BehaviourUpdateData data);

    std::tuple<float, float, float> getCurrentColor() const { return currentNode->getCurrentColor(); }

private:
    std::shared_ptr<BehaviourTreeNodeBase> rootNode;
    std::shared_ptr<BehaviourTreeNodeBase> currentNode;

    void buildTree();
};
