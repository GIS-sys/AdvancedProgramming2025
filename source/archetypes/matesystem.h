#pragma once

#include <vector>

#include "archetypes/archetype.h"
#include "mate_system.h"

class World;

struct MateSystemsArchetype : Archetype
{
    std::vector<MateSystem> matesystems;

    void move(int iFrom, int iTo)
    {
        ids[iTo] = std::move(ids[iFrom]);
        matesystems[iTo] = std::move(matesystems[iFrom]);
    }

    void shrink(int toSize)
    {
        eraseAfterIndex(ids, toSize);
        eraseAfterIndex(matesystems, toSize);
    }

    void extendMove(MateSystemsArchetype &other)
    {
        ids.insert(ids.end(), std::make_move_iterator(other.ids.begin()), std::make_move_iterator(other.ids.end()));
        matesystems.insert(matesystems.end(), std::make_move_iterator(other.matesystems.begin()), std::make_move_iterator(other.matesystems.end()));
        other.ids.clear();
        other.matesystems.clear();
    }

    int sizeNoID() const
    {
        int size = matesystems.size();
        return size;
    }

    void update(int i, float dt, World *world);
};
