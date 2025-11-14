#pragma once

#include <vector>

#include "archetypes/archetype.h"
#include "food_generator.h"

class World;

struct FoodGeneratorsArchetype : Archetype
{
    std::vector<FoodGenerator> foodgenerators;

    void move(int iFrom, int iTo)
    {
        ids[iFrom] = std::move(ids[iTo]);
        foodgenerators[iFrom] = std::move(foodgenerators[iTo]);
    }

    void extendMove(FoodGeneratorsArchetype &other)
    {
        ids.insert(ids.end(), std::make_move_iterator(other.ids.begin()), std::make_move_iterator(other.ids.end()));
        foodgenerators.insert(foodgenerators.end(), std::make_move_iterator(other.foodgenerators.begin()), std::make_move_iterator(other.foodgenerators.end()));
        other.ids.clear();
        other.foodgenerators.clear();
    }

    int sizeNoID() const
    {
        int size = foodgenerators.size();
        return size;
    }

    void update(int i, float dt, World *world);
};
