#pragma once

#include "behaviour/tree/base.h"
#include <functional>

class BehaviourTreeNodeAction : public BehaviourTreeNodeBase
{
public:
    std::function<bool(BehaviourUpdateData, int2 &)> actionWhetherNext;
    std::tuple<float, float, float> color;

    BehaviourTreeNodeAction(std::function<bool(BehaviourUpdateData, int2 &)> actionWhetherNext, std::tuple<float, float, float> color = {0.1f, 0.1f, 0.7f})
        : actionWhetherNext(actionWhetherNext), color(color)
    {
    }

    void update(BehaviourUpdateData data, BehaviourTreeNodeBase *&currentNode, int2 &currentTarget) override
    {
        if (status == Status::EXECUTING)
        {
            // We are here after last step
            if (actionWhetherNext(data, currentTarget))
                goToParent(currentNode);
        }
        else if (status == Status::DONE)
        {
            // We moved here from parent
            status = Status::EXECUTING;
            if (actionWhetherNext(data, currentTarget))
                goToParent(currentNode);
        }
        else if (status == Status::WAITING_CHILD)
        {
            // We moved here from child
        }
    }

    std::tuple<float, float, float> getCurrentColor() const override
    {
        return color;
    }
};
