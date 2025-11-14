#include "predator.h"
#include "world.h"

void Predator::on_update(float dt, World *world, Transform2D &myTransform, Health &myHealth, TYPE_ID myID)
{
    for (int i = 0; i < world->currentHeroes.size(); ++i)
    {
        if (world->currentHeroes.ids[i] == myID)
            continue;
        Transform2D &victimTransform = world->currentHeroes.transform2ds[i];
        if (int(myTransform.x) == int(victimTransform.x) &&
            int(myTransform.y) == int(victimTransform.y))
        {
            Health &victimHp = world->currentHeroes.healths[i];
            myHealth.change(victimHp.current);                         // heal predator
            world->toDeleteHeroes.insert(world->currentHeroes.ids[i]); // kill victim
            return;                                                    // Consume only one victim at a time
        }
    }
    for (int i = 0; i < world->currentEnemies.size(); ++i)
    {
        if (world->currentEnemies.ids[i] == myID)
            continue;
        Transform2D &victimTransform = world->currentEnemies.transform2ds[i];
        if (int(myTransform.x) == int(victimTransform.x) &&
            int(myTransform.y) == int(victimTransform.y))
        {
            Health &victimHp = world->currentEnemies.healths[i];
            myHealth.change(victimHp.current);                           // heal predator
            world->toDeleteEnemies.insert(world->currentEnemies.ids[i]); // kill victim
            return;                                                      // Consume only one victim at a time
        }
    }
}
