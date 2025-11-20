#include "mate_system.h"
#include "world.h"

void MateSystem::on_update(float dt, World *world)
{
    accumulator += dt;
    if (accumulator < mateInterval)
        return;
    accumulator -= mateInterval;

    for (int i = 0; i < world->currentEnemies.size(); ++i)
    {
        if (world->currentEnemies.healths[i].current < 80)
            continue;
        for (int j = 0; j < world->currentEnemies.size(); ++j)
        {
            if (i == j)
                continue;
            // if (world->currentEnemies.healths[j].current < 80)
            //     continue;
            if (std::holds_alternative<Predator>(world->currentEnemies.foodsources[i]) != std::holds_alternative<Predator>(world->currentEnemies.foodsources[j]))
                continue;
            if ((world->currentEnemies.transform2ds[i].point() - world->currentEnemies.transform2ds[j].point()).manhattanLength() > 1)
                continue;
            world->currentEnemies.healths[i].change(-world->currentEnemies.healths[i].current / 3);
            world->currentEnemies.healths[j].change(-world->currentEnemies.healths[j].current / 3);

            // Spawn
            Transform2D birthPos = world->currentEnemies.transform2ds[i];
            int birthHealth = world->currentEnemies.healths[i].current / 2 + world->currentEnemies.healths[j].current / 2;
            bool birthIsPredator = std::holds_alternative<Predator>(world->currentEnemies.foodsources[i]);

            world->toAddEnemies.sprites.push_back(world->currentEnemies.sprites[i]);
            world->toAddEnemies.transform2ds.push_back(birthPos);
            world->toAddEnemies.irestrictors.push_back(world->currentEnemies.irestrictors[i]);
            world->toAddEnemies.healths.push_back(Health(birthHealth));
            world->toAddEnemies.staminas.push_back(Stamina(100));
            if (birthIsPredator)
                world->toAddEnemies.foodsources.push_back(Predator());
            else
                world->toAddEnemies.foodsources.push_back(FoodConsumer());
            world->toAddEnemies.enemies.push_back(Enemy(world->toAddEnemies.foodsources.back()));
        }
    }
}
