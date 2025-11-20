#include "behaviour/base.h"

#include "world.h"

bool hasPredatorNearby2(World *world, const int2 &position, int distance)
{
    for (int i : world->getIndicesEnemiesHunters())
        if ((world->currentEnemies.transform2ds[i].point() - position).manhattanLength() < distance)
            return true;
    return false;
}

bool BehaviourBase::hasPredatorNearby(World *world, const int2 &position, int distance)
{
    bool x = hasPredatorNearby2(world, position, distance);
    return x;
}

int2 BehaviourBase::findOppositeToClosestPredator(World *world, const int2 &position, const Pathfinder &pathfinder, const DungeonRestrictor &restrictor)
{
    int2 enemyPosition = findClosestPredator(world, position, pathfinder);
    int maxLength = 0;
    int2 maxTargetPosition = position;
    for (int dx = -3; dx <= 3; ++dx)
    {
        for (int dy = -3; dy <= 3; ++dy)
        {
            int2 newTargetPosition = position + int2(dx, dy);
            if (!restrictor.can_pass(newTargetPosition))
                continue;
            int lengthToEnemy = (enemyPosition - newTargetPosition).manhattanLength();
            if (lengthToEnemy > maxLength)
            {
                maxLength = lengthToEnemy;
                maxTargetPosition = newTargetPosition;
            }
        }
    }

    return maxTargetPosition;
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
