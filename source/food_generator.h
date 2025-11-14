#pragma once

#include "math2d.h"
#include "food.h"
#include "dungeon_generator.h"

class FoodGenerator
{
private:
    std::shared_ptr<Dungeon> dungeon;
    std::vector<FOOD_FABRIQUE_TYPES> fabriques;
    float timeSinceLastSpawn = 0.f; // seconds between spawns
    float spawnInterval = 1.f;
    int fabriquesProbabilitySum = 0;

public:
    FoodGenerator(std::shared_ptr<Dungeon> dungeon, std::vector<FOOD_FABRIQUE_TYPES> fabriques, float spawnInterval)
        : dungeon(dungeon), fabriques(std::move(fabriques)), spawnInterval(spawnInterval)
    {
        for (const auto &fabrique : this->fabriques)
            fabriquesProbabilitySum += weight(fabrique);
    }

    void generate_random_food()
    {
        auto position = dungeon->getRandomFloorPosition();
        int rand_value = rand() % fabriquesProbabilitySum;
        for (const auto &fabrique : fabriques)
        {
            if (rand_value < weight(fabrique))
            {
                create_food(fabrique, position);
                break;
            }
            rand_value -= weight(fabrique);
        }
    }
    void on_update(float dt)
    {
        timeSinceLastSpawn += dt;
        if (timeSinceLastSpawn >= spawnInterval)
        {
            timeSinceLastSpawn = 0.f;
            // spawn food
            generate_random_food();
        }
    }
};
