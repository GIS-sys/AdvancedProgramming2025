#pragma once

#include "behaviour/tree/base.h"
#include <functional>

class BehaviourTreeNodeConsequitive : public BehaviourTreeNodeBase
{
    int executingIndex = 0;

public:
    std::vector<BehaviourTreeNodeBase *> children;

    BehaviourTreeNodeConsequitive(std::vector<BehaviourTreeNodeBase *> children = {}) : children(children) {}

    ~BehaviourTreeNodeConsequitive()
    {
        for (BehaviourTreeNodeBase *child : children)
            delete child;
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
            executingIndex = 0;
            if (children.size() <= executingIndex)
            {
                goToParent(currentNode);
                return;
            }

            goToChild(children[executingIndex], currentNode);
        }
        else if (status == Status::WAITING_CHILD)
        {
            // We moved here from child
            ++executingIndex;
            if (children.size() <= executingIndex)
            {
                goToParent(currentNode);
                return;
            }
            goToChild(children[executingIndex], currentNode);
        }
    }

    std::tuple<float, float, float> getCurrentColor() const override
    {
        return {0.3f, 0.3f, 0.3f};
    }

private:
    void buildWithChildren() override
    {
        std::cout << "conseq" << std::endl;
        for (BehaviourTreeNodeBase *child : children)
            child->build(this);
    }
};
