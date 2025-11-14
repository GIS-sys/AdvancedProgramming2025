#pragma once

#include <vector>

#include "archetypes/archetype.h"
#include "sprite.h"
#include "transform2d.h"

class World;

struct TilesArchetype : Archetype
{
    std::vector<Sprite> sprites;
    std::vector<Transform2D> transform2ds;

    void move(int iFrom, int iTo)
    {
        ids[iTo] = std::move(ids[iFrom]);
        sprites[iTo] = std::move(sprites[iFrom]);
        transform2ds[iTo] = std::move(transform2ds[iFrom]);
    }

    void shrink(int toSize)
    {
        eraseAfterIndex(ids, toSize);
        eraseAfterIndex(sprites, toSize);
        eraseAfterIndex(transform2ds, toSize);
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

    int sizeNoID() const
    {
        int size = sprites.size();
        if (size != transform2ds.size())
        {
            throw "TilesArchetype: sizeNoID() detected uneven vectors filling (you probably forgot to add some field when creating new object)";
        }
        return size;
    }

    void update(int i, float dt, World *world);
};
