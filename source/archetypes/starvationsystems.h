#pragma once

#include <vector>

#include "archetypes/archetype.h"
#include "starvation_system.h"

struct StarvationSystemArchetype : Archetype
{
    std::vector<StarvationSystem> starvationsystems;

    void move(int iFrom, int iTo)
    {
        ids[iFrom] = std::move(ids[iTo]);
        starvationsystems[iFrom] = std::move(starvationsystems[iTo]);
    }

    void extendMove(StarvationSystemArchetype &other)
    {
        ids.insert(ids.end(), std::make_move_iterator(other.ids.begin()), std::make_move_iterator(other.ids.end()));
        starvationsystems.insert(starvationsystems.end(), std::make_move_iterator(other.starvationsystems.begin()), std::make_move_iterator(other.starvationsystems.end()));
        other.ids.clear();
        other.starvationsystems.clear();
    }

    void update(int i, float dt, World *world)
    {
        // TODO
    }
};
