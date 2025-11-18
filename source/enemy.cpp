#include "enemy.h"
#include "world.h"

void Enemy::on_update(float dt, Transform2D &transform, const DungeonRestrictor &restrictor, World *world, Stamina &stamina, Health &health)
{
    accumulatedTime += dt * stamina.get_speed();
    if (accumulatedTime < 1.0f)
        return;
    accumulatedTime -= 1.0f;

    int2 currentPos = {(int)transform.x, (int)transform.y};
    behaviour.update(world, currentPos, stamina, health);

    int2 target = behaviour.getTarget(world, currentPos, restrictor, pathfinder);

    pathfinder.updatePosition(transform, restrictor, target);
    int2 nextPos = pathfinder.getNextPos();
    if (restrictor.can_pass(nextPos))
    {
        transform.x = nextPos.x;
        transform.y = nextPos.y;
    }
}
