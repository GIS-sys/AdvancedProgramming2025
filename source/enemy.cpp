#include "enemy.h"
#include "world.h"

void Enemy::on_update(float dt, Transform2D &transform, const DungeonRestrictor &restrictor, World *world, Health &health, Stamina &stamina)
{
    accumulatedTime += dt * stamina.get_speed();
    if (accumulatedTime < 1.0f)
        return;
    accumulatedTime -= 1.0f;

    int2 currentPos = {(int)transform.x, (int)transform.y};
    behaviour.update(BehaviourUpdateData(world, currentPos, restrictor, pathfinder, stamina, health));

    int2 target = behaviour.getTarget();

    pathfinder.updatePosition(transform, restrictor, target);
    int2 nextPos = pathfinder.getNextPos();
    if (restrictor.can_pass(nextPos))
    {
        transform.x = nextPos.x;
        transform.y = nextPos.y;
    }
}

std::tuple<float, float, float> Enemy::getCurrentColor() const
{
    return behaviour.getCurrentColor();
}
