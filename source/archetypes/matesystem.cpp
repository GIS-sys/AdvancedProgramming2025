#pragma once

#include "archetypes/matesystem.h"
#include "world.h"

void MateSystemsArchetype::update(int i, float dt, World *world)
{
    matesystems[i].on_update(dt, world);
}
