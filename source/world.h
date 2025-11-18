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

#include "cache.h"

class World : public std::enable_shared_from_this<World>
{
private:
    std::vector<int> indicesEnemiesHunters;
    std::vector<int> indicesEnemiesGatherers;

    void recalculateIndices();

public:
    const std::vector<int> getIndicesEnemiesHunters() const { return indicesEnemiesHunters; }
    const std::vector<int> getIndicesEnemiesGatherers() const { return indicesEnemiesGatherers; }

public:
    void update(float dt);

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
