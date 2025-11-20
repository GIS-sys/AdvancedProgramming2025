#pragma once

#include "behaviour/tree/base.h"
#include <functional>

class BehaviourTreeNodeCondition : public BehaviourTreeNodeBase
{
public:
    BehaviourTreeNodeBase *childLeft = nullptr;
    BehaviourTreeNodeBase *childRight = nullptr;
    std::function<bool(BehaviourUpdateData)> conditionIsRight;

    BehaviourTreeNodeCondition(std::function<bool(BehaviourUpdateData)> conditionIsRight) : conditionIsRight(conditionIsRight) {}
    ~BehaviourTreeNodeCondition()
    {
        if (childLeft)
            delete childLeft;
        if (childRight)
            delete childRight;
    }

    void update(BehaviourUpdateData data, BehaviourTreeNodeBase *&currentNode, int2 &currentTarget) override
    {
        if (status == Status::EXECUTING)
        {
            // We are here after last step
        }
        else if (status == Status::DONE)
        {
            // We moved here from parent
            status = Status::EXECUTING;
            if (!conditionIsRight(data))
                goToChild(childLeft, currentNode);
            else
                goToChild(childRight, currentNode);
        }
        else if (status == Status::WAITING_CHILD)
        {
            // We moved here from child
            goToParent(currentNode);
        }
    }

    std::tuple<float, float, float> getCurrentColor() const override
    {
        return {0.7f, 0.7f, 0.7f};
    }

private:
    void buildWithChildren() override
    {
        if (childLeft)
            childLeft->build(this);
        if (childRight)
            childRight->build(this);
    }
};
