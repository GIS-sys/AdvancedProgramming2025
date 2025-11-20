
#include "world.h"
#include "camera2d.h"
#include "sprite.h"
#include "health.h"
#include "stamina.h"
#include <SDL3/SDL_render.h>

void render_world(SDL_Window *window, SDL_Renderer *renderer, World &world)
{
    int screenW, screenH;
    SDL_GetWindowSize(window, &screenW, &screenH);

    // search of camera component
    Camera2D &camera2d = world.currentCameras.camera2ds.back();
    Transform2D &camera_transform = world.currentCameras.transform2ds.back();

    auto render_sprite = [&](Sprite *sprite, Transform2D *transform)
    {
        SDL_FRect dst = to_camera_space(*transform, camera_transform, camera2d);
        dst.x += screenW / 2;
        dst.y += screenH / 2;
        DrawSprite(renderer, *sprite, dst);
    };

    // Draw sprites
    for (int i = 0; i < world.currentTiles.size(); ++i)
        render_sprite(&world.currentTiles.sprites[i], &world.currentTiles.transform2ds[i]);

    // Render what enemies are doing
    for (int i = 0; i < world.currentEnemies.size(); ++i)
    {
        const double gap = 0.2f;
        Transform2D barTransform = world.currentEnemies.transform2ds[i];
        barTransform.x -= barTransform.sizeX * gap;
        barTransform.y -= barTransform.sizeY * gap;
        barTransform.sizeX *= (1.0f + 2 * gap);
        barTransform.sizeY *= (1.0f + 2 * gap);
        SDL_FRect dst = to_camera_space(barTransform, camera_transform, camera2d);
        dst.x += screenW / 2;
        dst.y += screenH / 2;
        std::vector<SDL_FRect> enemyRect;
        enemyRect.push_back(dst);

        auto [red, green, blue] = world.currentEnemies.enemies[i].getCurrentColor();

        SDL_SetRenderDrawColorFloat(renderer, red, green, blue, 1.0f);
        SDL_RenderFillRects(renderer, enemyRect.data(), 1);
    }

    // Draw sprites
    for (int i = 0; i < world.currentFoods.size(); ++i)
        render_sprite(&world.currentFoods.sprites[i], &world.currentFoods.transform2ds[i]);
    for (int i = 0; i < world.currentEnemies.size(); ++i)
        render_sprite(&world.currentEnemies.sprites[i], &world.currentEnemies.transform2ds[i]);
    for (int i = 0; i < world.currentHeroes.size(); ++i)
        render_sprite(&world.currentHeroes.sprites[i], &world.currentHeroes.transform2ds[i]);

    // Draw bars without textures and without OOP
    float grayColor[4] = {0.2f, 0.2f, 0.2f, 1.f};
    float healthColor[4] = {0.91f, 0.27f, 0.22f, 1.f};
    float staminaColor[4] = {0.f, 0.6f, 0.86f, 1.f};

    std::vector<SDL_FRect> backBars;
    std::vector<SDL_FRect> healthBars;
    std::vector<SDL_FRect> staminaBars;
    auto render_bars = [&](Transform2D *transform, Health *health, Stamina *stamina)
    {
        if (health)
        {
            Transform2D barTransform = *transform;
            barTransform.sizeX *= 0.1f;
            SDL_FRect dst = to_camera_space(barTransform, camera_transform, camera2d);
            dst.x += screenW / 2;
            dst.y += screenH / 2;
            backBars.push_back(dst);
            const float value = float(health->current) / float(health->max);
            dst.y += (1.f - value) * dst.h;
            dst.h *= value;
            healthBars.push_back(dst);
        }
        if (stamina)
        {
            Transform2D barTransform = *transform;
            barTransform.x += barTransform.sizeX * 0.9f;
            barTransform.sizeX *= 0.1f;
            SDL_FRect dst = to_camera_space(barTransform, camera_transform, camera2d);
            dst.x += screenW / 2;
            dst.y += screenH / 2;
            backBars.push_back(dst);
            const float value = float(stamina->current) / float(stamina->max);
            dst.y += (1.f - value) * dst.h;
            dst.h *= value;
            staminaBars.push_back(dst);
        }
    };
    for (int i = 0; i < world.currentEnemies.size(); ++i)
        render_bars(&world.currentEnemies.transform2ds[i], &world.currentEnemies.healths[i], &world.currentEnemies.staminas[i]);
    for (int i = 0; i < world.currentHeroes.size(); ++i)
        render_bars(&world.currentHeroes.transform2ds[i], &world.currentHeroes.healths[i], &world.currentHeroes.staminas[i]);

    SDL_SetRenderDrawColorFloat(renderer, grayColor[0], grayColor[1], grayColor[2], grayColor[3]);
    SDL_RenderFillRects(renderer, backBars.data(), int(backBars.size()));
    SDL_SetRenderDrawColorFloat(renderer, healthColor[0], healthColor[1], healthColor[2], healthColor[3]);
    SDL_RenderFillRects(renderer, healthBars.data(), int(healthBars.size()));
    SDL_SetRenderDrawColorFloat(renderer, staminaColor[0], staminaColor[1], staminaColor[2], staminaColor[3]);
    SDL_RenderFillRects(renderer, staminaBars.data(), int(staminaBars.size()));
}
