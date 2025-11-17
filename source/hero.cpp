#include "hero.h"
#include "world.h"

void Hero::bind_camera_transform()
{
    Transform2D &mainCameraTransform2D = world->currentCameras.transform2ds.back();
    Transform2D &mainOwnerTransform2D = world->currentHeroes.transform2ds.back();
    mainCameraTransform2D.x = mainOwnerTransform2D.x;
    mainCameraTransform2D.y = mainOwnerTransform2D.y;
}

Hero::Hero(World *world)
    : world(world) {}

void Hero::on_update(float dt, Transform2D &transform, const DungeonRestrictor &restrictor, Stamina &stamina)
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
    if (restrictor.can_pass(newPos))
    {
        transform.x += intDelta.x;
        transform.y += intDelta.y;
        bind_camera_transform();
    }
}
