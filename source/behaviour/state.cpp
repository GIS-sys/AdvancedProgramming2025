#include "behaviour/state.h"

std::string BehaviourStateToString(const BehaviourState &state)
{
    switch (state)
    {
    case BehaviourState::IDLE:
        return "IDLE";
    case BehaviourState::AVOID_PREDATORS:
        return "AVOID_PREDATORS";
    case BehaviourState::FIND_FOOD:
        return "FIND_FOOD";
    case BehaviourState::MATE:
        return "MATE";
    case BehaviourState::HUNT:
        return "HUNT";
    default:
        return "UNKNOWN";
    }
}
