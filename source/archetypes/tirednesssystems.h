#pragma once

#include <vector>

#include "archetypes/archetype.h"
#include "tiredness_system.h"

class World;

struct TirednessSystemsArchetype : Archetype
{
    std::vector<TirednessSystem> tirednesssystems;

    void move(int iFrom, int iTo)
    {
        ids[iFrom] = std::move(ids[iTo]);
        tirednesssystems[iFrom] = std::move(tirednesssystems[iTo]);
    }

    void extendMove(TirednessSystemsArchetype &other)
    {
        ids.insert(ids.end(), std::make_move_iterator(other.ids.begin()), std::make_move_iterator(other.ids.end()));
        tirednesssystems.insert(tirednesssystems.end(), std::make_move_iterator(other.tirednesssystems.begin()), std::make_move_iterator(other.tirednesssystems.end()));
        other.ids.clear();
        other.tirednesssystems.clear();
    }

    int sizeNoID() const
    {
        int size = tirednesssystems.size();
        return size;
    }

    void update(int i, float dt, World *world);
};
