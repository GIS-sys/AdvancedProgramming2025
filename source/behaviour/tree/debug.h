#pragma once

#include "behaviour/tree/base.h"
#include <functional>
#include <string>

class BehaviourTreeNodeDebug : public BehaviourTreeNodeBase
{
public:
    std::string text;

    BehaviourTreeNodeDebug(std::string text) : text(text) {}

    void update(BehaviourUpdateData data, BehaviourTreeNodeBase *&currentNode, int2 &currentTarget) override
    {
        std::cout << text << std::endl;
        goToParent(currentNode);
    }

    std::tuple<float, float, float> getCurrentColor() const override
    {
        return {0.9f, 0.9f, 0.9f};
    }
};
