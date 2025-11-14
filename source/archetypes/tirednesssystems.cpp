#pragma once

#include "archetypes/tirednesssystems.h"
#include "world.h"

void TirednessSystemsArchetype::update(int i, float dt, World *world)
{
    tirednesssystems[i].on_update(dt, world);
}
