#pragma once

#include <vector>

#include "archetypes/archetype.h"

class World;

struct TilesArchetype : Archetype
{
    std::vector<Sprite> sprites;
    std::vector<Transform2D> transform2ds;

    void move(int iFrom, int iTo)
    {
        ids[iFrom] = std::move(ids[iTo]);
        sprites[iFrom] = std::move(sprites[iTo]);
        transform2ds[iFrom] = std::move(transform2ds[iTo]);
    }

    void extendMove(TilesArchetype &other)
    {
        ids.insert(ids.end(), std::make_move_iterator(other.ids.begin()), std::make_move_iterator(other.ids.end()));
        sprites.insert(sprites.end(), std::make_move_iterator(other.sprites.begin()), std::make_move_iterator(other.sprites.end()));
        transform2ds.insert(transform2ds.end(), std::make_move_iterator(other.transform2ds.begin()), std::make_move_iterator(other.transform2ds.end()));
        other.ids.clear();
        other.sprites.clear();
        other.transform2ds.clear();
    }

    void update(int i, float dt, World *world);
};
