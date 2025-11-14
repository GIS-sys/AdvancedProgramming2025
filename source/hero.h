#pragma once

#include "restrictor.h"
#include "stamina.h"
#include "transform2d.h"
#include <SDL3/SDL.h>
#include <algorithm>

class Hero
{
private:
    float timeSinceLastMode = 0.f; // seconds between movement steps
    Transform2D *mainOwnerTransform2D;
    Transform2D *mainCameraTransform2D;

    void bind_camera_transform()
    {
        if (mainCameraTransform2D && mainOwnerTransform2D)
        {
            mainCameraTransform2D->x = mainOwnerTransform2D->x;
            mainCameraTransform2D->y = mainOwnerTransform2D->y;
        }
    }

public:
    Hero(Transform2D *mainOwnerTransform2D = nullptr, Transform2D *mainCameraTransform2D = nullptr)
        : mainOwnerTransform2D(mainOwnerTransform2D), mainCameraTransform2D(mainCameraTransform2D) {}

    void on_create()
    {
        bind_camera_transform();
    }

    void on_update(float dt, Transform2D &transform, IRestrictor *restrictor, Stamina &stamina)
    {
        const bool *keys = SDL_GetKeyboardState(nullptr);
        const float cellPerSecond = stamina.get_speed();
        int2 intDelta;
        bool moved = false;
        if (keys[SDL_SCANCODE_W])
        {
            intDelta.y -= 1;
            moved = true;
        }
        if (keys[SDL_SCANCODE_S])
        {
            intDelta.y += 1;
            moved = true;
        }
        if (keys[SDL_SCANCODE_A])
        {
            intDelta.x -= 1;
            moved = true;
        }
        if (keys[SDL_SCANCODE_D])
        {
            intDelta.x += 1;
            moved = true;
        }
        if (!moved)
            return;
        if (moved && (timeSinceLastMode < 1.f / cellPerSecond))
        {
            timeSinceLastMode += dt;
            return;
        }
        timeSinceLastMode = 0.f;
        int2 newPos = int2((int)transform.x + intDelta.x, (int)transform.y + intDelta.y);
        if (restrictor->can_pass(newPos))
        {
            transform.x += intDelta.x;
            transform.y += intDelta.y;
            bind_camera_transform();
        }
    }
};
