#include "food.h"
#include "food_generator.h"
#include "tileset.h"
#include "world.h"
#include "transform2d.h"
#include "health.h"
#include "stamina.h"

void HealthFood::on_consume(World *world, Health &myHealth, Stamina &myStamina, TYPE_ID foodID)
{
    myHealth.change(healthRestore);
    world->toDeleteFoods.insert(foodID);
}

void StaminaFood::on_consume(World *world, Health &myHealth, Stamina &myStamina, TYPE_ID foodID)
{
    myStamina.change(staminaRestore);
    world->toDeleteFoods.insert(foodID);
}

static void create_food_abstract(World *world, Sprite sprite, int2 position, FOOD_TYPES foodComp)
{
    world->toAddFoods.transform2ds.push_back(Transform2D(position.x, position.y));
    world->toAddFoods.sprites.push_back(sprite);
    world->toAddFoods.foods.push_back(foodComp);
}

HealthFoodFabrique::HealthFoodFabrique(World *world, Sprite sprite, int healthRestore, int weightValue)
    : world(world), sprite(sprite), healthRestore(healthRestore), weightValue(weightValue) {}

void HealthFoodFabrique::create_food(int2 position) const
{
    create_food_abstract(world, sprite, position, HealthFood(healthRestore));
}

StaminaFoodFabrique::StaminaFoodFabrique(World *world, Sprite sprite, int staminaRestore, int weightValue)
    : world(world), sprite(sprite), staminaRestore(staminaRestore), weightValue(weightValue) {}

void StaminaFoodFabrique::create_food(int2 position) const
{
    create_food_abstract(world, sprite, position, StaminaFood(staminaRestore));
}

std::vector<FOOD_FABRIQUE_TYPES> create_food_fabriques(World *world, TileSet &tileset)
{
    std::vector<FOOD_FABRIQUE_TYPES> fabriques;
    fabriques.push_back(HealthFoodFabrique(world, tileset.get_tile("health_small"), 10, 100));
    fabriques.push_back(HealthFoodFabrique(world, tileset.get_tile("health_large"), 25, 30));

    fabriques.push_back(StaminaFoodFabrique(world, tileset.get_tile("stamina_small"), 10, 35));
    fabriques.push_back(StaminaFoodFabrique(world, tileset.get_tile("stamina_large"), 25, 20));
    return fabriques;
}
