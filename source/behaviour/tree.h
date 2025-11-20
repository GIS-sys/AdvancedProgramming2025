#pragma once

#include "behaviour/base.h"
#include "behaviour/tree/base.h"

#include <string>

class World;

class BehaviourTree : public BehaviourBase
{
public:
    BehaviourTree(FOOD_SOURCES_TYPE foodSourceType);
    BehaviourTree(const BehaviourTree &other) = delete;
    BehaviourTree &operator=(const BehaviourTree &other) = delete;
    BehaviourTree(BehaviourTree &&other) : BehaviourTree(other.foodSourceType)
    {
        rootNode = other.rootNode;
        other.rootNode = nullptr;
        currentNode = other.currentNode;
        other.currentNode = nullptr;
    }
    BehaviourTree &operator=(BehaviourTree &&other)
    {
        if (rootNode == other.rootNode)
            return *this;
        if (rootNode)
            delete rootNode;
        rootNode = other.rootNode;
        other.rootNode = nullptr;
        currentNode = other.currentNode;
        other.currentNode = nullptr;
        return *this;
    }
    ~BehaviourTree()
    {
        if (rootNode)
            delete rootNode;
    }
    void update(BehaviourUpdateData data);

    std::tuple<float, float, float> getCurrentColor() const
    {
        if (!currentNode)
            return {0.0f, 0.0f, 0.0f};
        return currentNode->getCurrentColor();
    }

private:
    BehaviourTreeNodeBase *rootNode = nullptr;
    BehaviourTreeNodeBase *currentNode = nullptr;

    void buildTree();
};
