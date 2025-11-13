#pragma once

#include <vector>

#include "archetypes/archetype.h"

struct TilesArchetype : Archetype
{
    std::vector<Sprite> sprites;
    std::vector<Transform2D> transforms;

    void move(int iFrom, int iTo)
    {
        ids[iFrom] = std::move(ids[iTo]);
        sprites[iFrom] = std::move(sprites[iTo]);
        transforms[iFrom] = std::move(transforms[iTo]);
    }

    void extendMove(TilesArchetype &other)
    {
        ids.insert(ids.end(), std::make_move_iterator(other.ids.begin()), std::make_move_iterator(other.ids.end()));
        sprites.insert(sprites.end(), std::make_move_iterator(other.sprites.begin()), std::make_move_iterator(other.sprites.end()));
        transforms.insert(transforms.end(), std::make_move_iterator(other.transforms.begin()), std::make_move_iterator(other.transforms.end()));
        other.clear();
    }

    void update(int i, float dt)
    {
        // TODO
    }
};
