#pragma once

#include "archetypes/archetype.h"
#include "health.h"
#include "stamina.h"

class World;

class IFood
{

public:
    virtual void on_consume(World *world, Health &myHealth, Stamina &myStamina, TYPE_ID foodID) = 0;
};
