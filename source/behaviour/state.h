#pragma once

#include <string>

enum class BehaviourState
{
    IDLE,
    AVOID_PREDATORS,
    FIND_FOOD,
    MATE,
    HUNT
};

std::string BehaviourStateToString(const BehaviourState &state);
