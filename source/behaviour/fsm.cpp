#include "fsm.h"
#include "world.h"

void FSM::decide(World *world, const DungeonRestrictor &restrictor, Transform2D &transform, FOOD_SOURCES_TYPE &food_source, Health &health, Pathfinder &pathfinder)
{
    // TODO
    pathfinder.updatePosition(transform, restrictor, std::make_optional<int2>({63, 8}));
    int2 nextPos = pathfinder.getNextPos();
    if (restrictor.can_pass(nextPos))
    {
        transform.x = nextPos.x;
        transform.y = nextPos.y;
    }
}
