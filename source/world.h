#pragma once

#include <memory>
#include <set>

#include "archetypes/cameras.h"
#include "archetypes/enemies.h"
#include "archetypes/foodgenerators.h"
#include "archetypes/foods.h"
#include "archetypes/heroes.h"
#include "archetypes/starvationsystems.h"
#include "archetypes/tiles.h"
#include "archetypes/tirednesssystems.h"

class World : public std::enable_shared_from_this<World>
{
public:
    void update(float dt)
    {
        filterDelete(currentCameras, toDeleteCameras);
        filterDelete(currentTiles, toDeleteTiles);
        filterDelete(currentHeroes, toDeleteHeroes);
        filterDelete(currentEnemies, toDeleteEnemies);
        filterDelete(currentFoodGenerators, toDeleteFoodGenerators);
        filterDelete(currentFoods, toDeleteFoods);
        filterDelete(currentTirednessSystems, toDeleteTirednessSystems);
        filterDelete(currentStarvationSystems, toDeleteStarvationSystems);

        currentCameras.extendMove(toAddCameras);
        currentTiles.extendMove(toAddTiles);
        currentHeroes.extendMove(toAddHeroes);
        currentEnemies.extendMove(toAddEnemies);
        currentFoodGenerators.extendMove(toAddFoodGenerators);
        currentFoods.extendMove(toAddFoods);
        currentTirednessSystems.extendMove(toAddTirednessSystems);
        currentStarvationSystems.extendMove(toAddStarvationSystems);

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

public:
    CamerasArchetype currentCameras;
    CamerasArchetype toAddCameras;
    std::set<TYPE_ID> toDeleteCameras;

    TilesArchetype currentTiles;
    TilesArchetype toAddTiles;
    std::set<TYPE_ID> toDeleteTiles;

    HeroesArchetype currentHeroes;
    HeroesArchetype toAddHeroes;
    std::set<TYPE_ID> toDeleteHeroes;

    EnemiesArchetype currentEnemies;
    EnemiesArchetype toAddEnemies;
    std::set<TYPE_ID> toDeleteEnemies;

    FoodGeneratorsArchetype currentFoodGenerators;
    FoodGeneratorsArchetype toAddFoodGenerators;
    std::set<TYPE_ID> toDeleteFoodGenerators;

    FoodsArchetype currentFoods;
    FoodsArchetype toAddFoods;
    std::set<TYPE_ID> toDeleteFoods;

    TirednessSystemsArchetype currentTirednessSystems;
    TirednessSystemsArchetype toAddTirednessSystems;
    std::set<TYPE_ID> toDeleteTirednessSystems;

    StarvationSystemsArchetype currentStarvationSystems;
    StarvationSystemsArchetype toAddStarvationSystems;
    std::set<TYPE_ID> toDeleteStarvationSystems;
};
