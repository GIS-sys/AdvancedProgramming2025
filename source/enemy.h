#pragma once

#include "dungeon_restrictor.h"
#include "stamina.h"
#include "transform2d.h"
#include "pathfinder.h"
#include <SDL3/SDL.h>
#include <algorithm>

class Enemy
{
private:
    Pathfinder pathfinder;
    // change transform by 1.0 unit when accumulatedDelta reaches 1.0
    float accumulatedTime;

public:
    void on_update(float dt, Transform2D &transform, const DungeonRestrictor &restrictor, Stamina &stamina)
    {
        accumulatedTime += dt * stamina.get_speed();
        if (accumulatedTime < 4.0f)
            return;
        accumulatedTime -= 4.0f;

        pathfinder.updatePosition(transform, restrictor, std::make_optional<int2>({63, 8}));
        int2 nextPos = pathfinder.getNextPos();
        if (restrictor.can_pass(nextPos))
        {
            transform.x = nextPos.x;
            transform.y = nextPos.y;
        }
    }
};