#include "world.h"

void World::update(float dt)
{
    filterDelete(currentCameras, toDeleteCameras);
    filterDelete(currentTiles, toDeleteTiles);
    filterDelete(currentHeroes, toDeleteHeroes);
    filterDelete(currentEnemies, toDeleteEnemies);
    filterDelete(currentFoodGenerators, toDeleteFoodGenerators);
    filterDelete(currentFoods, toDeleteFoods);
    filterDelete(currentTirednessSystems, toDeleteTirednessSystems);
    filterDelete(currentStarvationSystems, toDeleteStarvationSystems);

    int last_heroes_size = currentHeroes.size();

    fillIDs(toAddCameras);
    fillIDs(toAddTiles);
    fillIDs(toAddHeroes);
    fillIDs(toAddEnemies);
    fillIDs(toAddFoodGenerators);
    fillIDs(toAddFoods);
    fillIDs(toAddTirednessSystems);
    fillIDs(toAddStarvationSystems);
    currentCameras.extendMove(toAddCameras);
    currentTiles.extendMove(toAddTiles);
    currentHeroes.extendMove(toAddHeroes);
    currentEnemies.extendMove(toAddEnemies);
    currentFoodGenerators.extendMove(toAddFoodGenerators);
    currentFoods.extendMove(toAddFoods);
    currentTirednessSystems.extendMove(toAddTirednessSystems);
    currentStarvationSystems.extendMove(toAddStarvationSystems);

    for (int i = last_heroes_size; i < currentHeroes.size(); ++i)
    {
        currentHeroes.heroes[i].on_create();
    }

    for (int i = 0; i < currentCameras.size(); ++i)
        currentCameras.update(dt, i, this);
    for (int i = 0; i < currentTiles.size(); ++i)
        currentTiles.update(dt, i, this);
    for (int i = 0; i < currentHeroes.size(); ++i)
        currentHeroes.update(dt, i, this);
    for (int i = 0; i < currentEnemies.size(); ++i)
        currentEnemies.update(dt, i, this);
    for (int i = 0; i < currentFoodGenerators.size(); ++i)
        currentFoodGenerators.update(dt, i, this);
    for (int i = 0; i < currentFoods.size(); ++i)
        currentFoods.update(dt, i, this);
    for (int i = 0; i < currentTirednessSystems.size(); ++i)
        currentTirednessSystems.update(dt, i, this);
    for (int i = 0; i < currentStarvationSystems.size(); ++i)
        currentStarvationSystems.update(dt, i, this);
}
