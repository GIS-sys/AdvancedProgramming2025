#pragma once

#include "behaviour/base.h"

class BehaviourTreeNodeBase
{
public:
    virtual void update(BehaviourUpdateData data, BehaviourTreeNodeBase *&currentNode, int2 &currentTarget) { goToParent(currentNode); } // OVERLOAD
    virtual std::tuple<float, float, float> getCurrentColor() const { return {0.0f, 0.0f, 0.0f}; };                                      // OVERLOAD

    virtual ~BehaviourTreeNodeBase() = default;
    void build(BehaviourTreeNodeBase *currentParent)
    {
        parent = currentParent;
        buildWithChildren();
    }

protected:
    enum class Status
    {
        EXECUTING,
        WAITING_CHILD,
        DONE
    };
    Status status = Status::DONE;
    BehaviourTreeNodeBase *parent = nullptr;

    void goToParent(BehaviourTreeNodeBase *&currentNode)
    {
        status = Status::DONE;
        currentNode = parent;
    }

    void goToChild(BehaviourTreeNodeBase *childToGo, BehaviourTreeNodeBase *&currentNode)
    {
        status = Status::WAITING_CHILD;
        currentNode = childToGo;
    }

    virtual void buildWithChildren() {} // OVERLOAD
};
