#pragma once

#include "archetypes/starvationsystems.h"
#include "world.h"

void StarvationSystemsArchetype::update(int i, float dt, World *world)
{
    starvationsystems[i].on_update(dt, world);
}
