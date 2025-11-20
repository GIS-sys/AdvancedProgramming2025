#pragma once

#include "behaviour/tree/base.h"
#include <functional>

class BehaviourTreeNodeCondition : public BehaviourTreeNodeBase
{
public:
    std::shared_ptr<BehaviourTreeNodeBase> childLeft;
    std::shared_ptr<BehaviourTreeNodeBase> childRight;
    std::function<bool(BehaviourUpdateData)> conditionIsRight;

    BehaviourTreeNodeCondition(std::function<bool(BehaviourUpdateData)> conditionIsRight) : conditionIsRight(conditionIsRight) {}

    void update(BehaviourUpdateData data, std::shared_ptr<BehaviourTreeNodeBase> &currentNode, int2 &currentTarget) override
    {
        return;
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
        // std::cout << "childLeft" << childLeft;
        // if (childLeft)
        //     childLeft->build(std::shared_ptr<BehaviourTreeNodeCondition>(this));
        // if (childRight)
        //     childRight->build(std::shared_ptr<BehaviourTreeNodeCondition>(this));
    }
};
