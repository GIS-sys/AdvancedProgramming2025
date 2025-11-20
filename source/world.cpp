#include "world.h"

void World::update(float dt)
{
    dt /= 10;

    filterDelete(currentCameras, toDeleteCameras);
    filterDelete(currentTiles, toDeleteTiles);
    filterDelete(currentHeroes, toDeleteHeroes);
    filterDelete(currentEnemies, toDeleteEnemies);
    filterDelete(currentFoodGenerators, toDeleteFoodGenerators);
    filterDelete(currentFoods, toDeleteFoods);
    filterDelete(currentTirednessSystems, toDeleteTirednessSystems);
    filterDelete(currentStarvationSystems, toDeleteStarvationSystems);
    filterDelete(currentMateSystems, toDeleteMateSystems);

    int last_heroes_size = currentHeroes.size();

    fillIDs(toAddCameras);
    fillIDs(toAddTiles);
    fillIDs(toAddHeroes);
    fillIDs(toAddEnemies);
    fillIDs(toAddFoodGenerators);
    fillIDs(toAddFoods);
    fillIDs(toAddTirednessSystems);
    fillIDs(toAddStarvationSystems);
    fillIDs(toAddMateSystems);
    currentCameras.extendMove(toAddCameras);
    currentTiles.extendMove(toAddTiles);
    currentHeroes.extendMove(toAddHeroes);
    currentEnemies.extendMove(toAddEnemies);
    currentFoodGenerators.extendMove(toAddFoodGenerators);
    currentFoods.extendMove(toAddFoods);
    currentTirednessSystems.extendMove(toAddTirednessSystems);
    currentStarvationSystems.extendMove(toAddStarvationSystems);
    currentMateSystems.extendMove(toAddMateSystems);

    recalculateIndices();

    for (int i = last_heroes_size; i < currentHeroes.size(); ++i)
    {
        currentHeroes.heroes[i].on_create();
    }

    for (int i = 0; i < currentCameras.size(); ++i)
        currentCameras.update(i, dt, this);
    for (int i = 0; i < currentTiles.size(); ++i)
        currentTiles.update(i, dt, this);
    for (int i = 0; i < currentHeroes.size(); ++i)
        currentHeroes.update(i, dt, this);
    for (int i = 0; i < currentEnemies.size(); ++i)
        currentEnemies.update(i, dt, this);
    for (int i = 0; i < currentFoodGenerators.size(); ++i)
        currentFoodGenerators.update(i, dt, this);
    for (int i = 0; i < currentFoods.size(); ++i)
        currentFoods.update(i, dt, this);
    for (int i = 0; i < currentTirednessSystems.size(); ++i)
        currentTirednessSystems.update(i, dt, this);
    for (int i = 0; i < currentStarvationSystems.size(); ++i)
        currentStarvationSystems.update(i, dt, this);
    for (int i = 0; i < currentMateSystems.size(); ++i)
        currentMateSystems.update(i, dt, this);
}

void World::recalculateIndices()
{
    indicesEnemiesHunters.clear();
    indicesEnemiesGatherers.clear();
    for (int i = 0; i < currentEnemies.size(); ++i)
    {
        if (std::holds_alternative<Predator>(currentEnemies.foodsources[i]))
            indicesEnemiesHunters.push_back(i);
        if (std::holds_alternative<FoodConsumer>(currentEnemies.foodsources[i]))
            indicesEnemiesGatherers.push_back(i);
    }
}
