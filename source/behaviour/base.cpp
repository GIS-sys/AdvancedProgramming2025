#include "behaviour/base.h"

#include "world.h"

bool BehaviourBase::hasPredatorNearby(World *world, const int2 &position, int distance)
{
    for (int i : world->getIndicesEnemiesHunters())
        if ((world->currentEnemies.transform2ds[i].point() - position).manhattanLength() < distance)
            return true;
    return false;
}

int2 BehaviourBase::findOppositeToClosestPredator(World *world, const int2 &position, const Pathfinder &pathfinder)
{
    int2 enemyPosition = findClosestPredator(world, position, pathfinder);
    int2 deltaToEnemy = enemyPosition - position;
    return position - deltaToEnemy.toDirection();
}

int2 BehaviourBase::findClosestFood(World *world, const int2 &position, const Pathfinder &pathfinder)
{
    return findClosestFood(world, position, pathfinder, [](const FoodsArchetype &, int i)
                           { return true; });
}

int2 BehaviourBase::findClosestFoodHealth(World *world, const int2 &position, const Pathfinder &pathfinder)
{
    return findClosestFood(world, position, pathfinder, [](const FoodsArchetype &fa, int i)
                           { return std::holds_alternative<HealthFood>(fa.foods[i]); });
}

int2 BehaviourBase::findClosestFoodStamina(World *world, const int2 &position, const Pathfinder &pathfinder)
{
    return findClosestFood(world, position, pathfinder, [](const FoodsArchetype &fa, int i)
                           { return std::holds_alternative<StaminaFood>(fa.foods[i]); });
}

template <typename F>
int2 BehaviourBase::findClosestFood(World *world, const int2 &position, const Pathfinder &pathfinder, F &&lambdaFilter)
{
    int minIndex = 0;
    for (int i = 0; i < world->currentFoods.size(); ++i)
    {
        if (!lambdaFilter(world->currentFoods, i))
            continue;
        if ((world->currentFoods.transform2ds[i].point() - position).manhattanLength() < (world->currentFoods.transform2ds[minIndex].point() - position).manhattanLength())
            minIndex = i;
    }
    return world->currentFoods.transform2ds[minIndex].point();
}

int2 BehaviourBase::findClosestPredator(World *world, const int2 &position, const Pathfinder &pathfinder)
{
    int minIndex = 0;
    for (int i : world->getIndicesEnemiesHunters())
    {
        if (world->currentEnemies.transform2ds[i].point() == position)
            continue;
        if ((world->currentEnemies.transform2ds[i].point() - position).manhattanLength() < (world->currentEnemies.transform2ds[minIndex].point() - position).manhattanLength())
            minIndex = i;
    }
    return world->currentEnemies.transform2ds[minIndex].point();
}

int2 BehaviourBase::findClosestFoodConsumer(World *world, const int2 &position, const Pathfinder &pathfinder)
{
    int minIndex = 0;
    for (int i : world->getIndicesEnemiesGatherers())
    {
        if (world->currentEnemies.transform2ds[i].point() == position)
            continue;
        if ((world->currentEnemies.transform2ds[i].point() - position).manhattanLength() < (world->currentEnemies.transform2ds[minIndex].point() - position).manhattanLength())
            minIndex = i;
    }
    return world->currentEnemies.transform2ds[minIndex].point();
}
