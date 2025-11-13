#include "food_generator.h"
#include "tileset.h"
#include "world.h"
#include "transform2d.h"
#include "health.h"
#include "stamina.h"

class HealthFood : public IFood
{

public:
    int healthRestore;
    HealthFood(int healthRestore) : healthRestore(healthRestore) {}
    void on_consume(World *world, Health &myHealth, Stamina &myStamina, TYPE_ID foodID) override
    {
        myHealth.change(healthRestore);
        world->toDeleteFoods.insert(foodID);
    }
};

class StaminaFood : public IFood
{

public:
    int staminaRestore;
    StaminaFood(int staminaRestore) : staminaRestore(staminaRestore) {}
    void on_consume(World *world, Health &myHealth, Stamina &myStamina, TYPE_ID foodID) override
    {
        myStamina.change(staminaRestore);
        world->toDeleteFoods.insert(foodID);
    }
};

static void create_food_abstract(World &world, Sprite sprite, int2 position, IFood *foodComp)
{
    world.toAddFoods.transform2ds.push_back(Transform2D(position.x, position.y));
    world.toAddFoods.sprites.push_back(sprite);
    world.toAddFoods.foods.push_back(foodComp);
}

class HealthFoodFabrique : public IFoodFabrique
{
    World &world;
    Sprite sprite;
    int healthRestore;
    int weightValue;

public:
    HealthFoodFabrique(World &world, Sprite sprite, int healthRestore, int weightValue)
        : world(world), sprite(sprite), healthRestore(healthRestore), weightValue(weightValue) {}

    virtual void create_food(int2 position) override
    {
        create_food_abstract(world, sprite, position, (IFood *)(new HealthFood(healthRestore)));
    }
    virtual int weight() const override { return weightValue; } // for random selection
};

class StaminaFoodFabrique : public IFoodFabrique
{
    World &world;
    Sprite sprite;
    int staminaRestore;
    int weightValue;

public:
    StaminaFoodFabrique(World &world, Sprite sprite, int staminaRestore, int weightValue)
        : world(world), sprite(sprite), staminaRestore(staminaRestore), weightValue(weightValue) {}

    virtual void create_food(int2 position) override
    {
        create_food_abstract(world, sprite, position, (IFood *)(new StaminaFood(staminaRestore)));
    }
    virtual int weight() const override { return weightValue; } // for random selection
};

std::vector<std::unique_ptr<IFoodFabrique>> create_food_fabriques(World &world, TileSet &tileset)
{
    std::vector<std::unique_ptr<IFoodFabrique>> fabriques;
    fabriques.push_back(std::make_unique<HealthFoodFabrique>(world, tileset.get_tile("health_small"), 10, 100));
    fabriques.push_back(std::make_unique<HealthFoodFabrique>(world, tileset.get_tile("health_large"), 25, 30));

    fabriques.push_back(std::make_unique<StaminaFoodFabrique>(world, tileset.get_tile("stamina_small"), 10, 35));
    fabriques.push_back(std::make_unique<StaminaFoodFabrique>(world, tileset.get_tile("stamina_large"), 25, 20));
    return fabriques;
}
