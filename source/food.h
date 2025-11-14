#pragma once

#include <variant>

#include "archetypes/archetype.h"
#include "health.h"
#include "stamina.h"
#include "sprite.h"
#include "math2d.h"

class World;

class HealthFood
{

public:
    int healthRestore;
    HealthFood(int healthRestore) : healthRestore(healthRestore) {}
    void on_consume(World *world, Health &myHealth, Stamina &myStamina, TYPE_ID foodID);
};

class StaminaFood
{

public:
    int staminaRestore;
    StaminaFood(int staminaRestore) : staminaRestore(staminaRestore) {}
    void on_consume(World *world, Health &myHealth, Stamina &myStamina, TYPE_ID foodID);
};

using FOOD_TYPES = std::variant<HealthFood, StaminaFood>;

class HealthFoodFabrique
{
    World *world;
    Sprite sprite;
    int healthRestore;
    int weightValue;

public:
    HealthFoodFabrique(World *world, Sprite sprite, int healthRestore, int weightValue);

    void create_food(int2 position) const;
    int weight() const { return weightValue; } // for random selection
};

class StaminaFoodFabrique
{
    World *world;
    Sprite sprite;
    int staminaRestore;
    int weightValue;

public:
    StaminaFoodFabrique(World *world, Sprite sprite, int staminaRestore, int weightValue);

    void create_food(int2 position) const;
    int weight() const { return weightValue; } // for random selection
};

using FOOD_FABRIQUE_TYPES = std::variant<HealthFoodFabrique, StaminaFoodFabrique>;

static void create_food(const FOOD_FABRIQUE_TYPES &fabrique, int2 position)
{
    if (std::holds_alternative<HealthFoodFabrique>(fabrique))
        std::get<HealthFoodFabrique>(fabrique).create_food(position);
    else if (std::holds_alternative<StaminaFoodFabrique>(fabrique))
        std::get<StaminaFoodFabrique>(fabrique).create_food(position);
    else
        throw "Unexpected Food Fabrique type";
}

static int weight(const FOOD_FABRIQUE_TYPES &fabrique)
{
    if (std::holds_alternative<HealthFoodFabrique>(fabrique))
        return std::get<HealthFoodFabrique>(fabrique).weight();
    else if (std::holds_alternative<StaminaFoodFabrique>(fabrique))
        return std::get<StaminaFoodFabrique>(fabrique).weight();
    else
        throw "Unexpected Food Fabrique type";
}
