#pragma once

#include "restrictor.h"
#include "stamina.h"
#include "transform2d.h"
#include <SDL3/SDL.h>
#include <algorithm>

class World;

class Hero
{
private:
    float timeSinceLastMode = 0.f; // seconds between movement steps
    World *world;

    void bind_camera_transform();

public:
    explicit Hero(World *world);

    void on_create()
    {
        bind_camera_transform();
    }

    void on_update(float dt, Transform2D &transform, IRestrictor *restrictor, Stamina &stamina);
};
