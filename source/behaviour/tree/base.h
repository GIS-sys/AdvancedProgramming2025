#pragma once

#include "behaviour/base.h"

class BehaviourTreeNodeBase
{
public:
    virtual void update(BehaviourUpdateData data, std::shared_ptr<BehaviourTreeNodeBase> &currentNode, int2 &currentTarget) { goToParent(currentNode); } // OVERLOAD
    virtual std::tuple<float, float, float> getCurrentColor() const { return {0.0f, 0.0f, 0.0f}; };                                                      // OVERLOAD

    virtual ~BehaviourTreeNodeBase() = default;
    void build(std::shared_ptr<BehaviourTreeNodeBase> currentParent)
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
    std::shared_ptr<BehaviourTreeNodeBase> parent;

    void goToParent(std::shared_ptr<BehaviourTreeNodeBase> &currentNode)
    {
        status = Status::DONE;
        currentNode = parent;
    }

    void goToChild(std::shared_ptr<BehaviourTreeNodeBase> childToGo, std::shared_ptr<BehaviourTreeNodeBase> &currentNode)
    {
        status = Status::WAITING_CHILD;
        currentNode = childToGo;
    }

    virtual void buildWithChildren() {} // OVERLOAD
};
