#pragma once

#include <vector>

#include "archetypes/archetype.h"
#include "camera2d.h"
#include "transform2d.h"

class World;

struct FoodsArchetype : Archetype
{
    std::vector<Transform2D> transform2ds;
    std::vector<Sprite> sprites;
    std::vector<IFood *> foods;

    void move(int iFrom, int iTo)
    {
        ids[iTo] = std::move(ids[iFrom]);
        transform2ds[iTo] = std::move(transform2ds[iFrom]);
        sprites[iTo] = std::move(sprites[iFrom]);
        foods[iTo] = std::move(foods[iFrom]);
    }

    void shrink(int toSize)
    {
        eraseAfterIndex(ids, toSize);
        eraseAfterIndex(transform2ds, toSize);
        eraseAfterIndex(sprites, toSize);
        eraseAfterIndex(foods, toSize);
    }

    void extendMove(FoodsArchetype &other)
    {
        ids.insert(ids.end(), std::make_move_iterator(other.ids.begin()), std::make_move_iterator(other.ids.end()));
        transform2ds.insert(transform2ds.end(), std::make_move_iterator(other.transform2ds.begin()), std::make_move_iterator(other.transform2ds.end()));
        sprites.insert(sprites.end(), std::make_move_iterator(other.sprites.begin()), std::make_move_iterator(other.sprites.end()));
        foods.insert(foods.end(), std::make_move_iterator(other.foods.begin()), std::make_move_iterator(other.foods.end()));
        other.ids.clear();
        other.transform2ds.clear();
        other.sprites.clear();
        other.foods.clear();
    }

    int sizeNoID() const
    {
        int size = sprites.size();
        if (size != transform2ds.size() ||
            size != foods.size())
        {
            throw "FoodsArchetype: sizeNoID() detected uneven vectors filling (you probably forgot to add some field when creating new object)";
        }
        return size;
    }

    void update(int i, float dt, World *world);
};
