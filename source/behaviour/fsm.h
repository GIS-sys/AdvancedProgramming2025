#pragma once

#include "behaviour/base.h"

#include <string>

class World;

class BehaviourFSM : public BehaviourBase
{
public:
    BehaviourFSM(FOOD_SOURCES_TYPE foodSourceType);
    void update(BehaviourUpdateData data);

private:
    enum class BehaviourState
    {
        IDLE,
        AVOID_PREDATORS,
        FEED_HEALTH,
        FEED_STAMINA,
        MATE
    };

    std::string BehaviourStateToString(const BehaviourState &state)
    {
        switch (state)
        {
        case BehaviourState::IDLE:
            return "IDLE";
        case BehaviourState::AVOID_PREDATORS:
            return "AVOID_PREDATORS";
        case BehaviourState::FEED_HEALTH:
            return "FEED_HEALTH";
        case BehaviourState::FEED_STAMINA:
            return "FEED_STAMINA";
        case BehaviourState::MATE:
            return "MATE";
        default:
            return "UNKNOWN";
        }
    }

    BehaviourState currentState;
    bool stateChanged = true;

    void changeState(BehaviourUpdateData data);
    void executeState(BehaviourUpdateData data);

    void switchToState(BehaviourState newState);
};
