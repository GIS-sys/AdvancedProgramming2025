#include "world.h"

#include "image.h"
#include "dungeon_generator.h"
#include "transform2d.h"
#include "sprite.h"
#include "hero.h"
#include "enemy.h"
#include "world.h"
#include "camera2d.h"
#include "dungeon_restrictor.h"
#include "tileset.h"
#include "food_generator.h"
#include "health.h"
#include "stamina.h"
#include "food_consumer.h"
#include "predator.h"

const int LevelWidth = 120;
const int LevelHeight = 50;
const int RoomAttempts = 100;
const int BotPopulationCount = 100;
const float PredatorProbability = 0.2f;
const int InitialFoodAmount = 100;

std::vector<FOOD_FABRIQUE_TYPES> create_food_fabriques(World *world, TileSet &tileset);

void init_world(SDL_Renderer *renderer, World &world)
{
    world.toAddCameras.camera2ds.push_back(Camera2D(32.f));
    world.toAddCameras.transform2ds.push_back(Transform2D(0, 0));

    const int tileSize = 16;
    TexturePtr tilemap = LoadTextureFromFile("assets/kenney_tiny-dungeon/Tilemap/tilemap.png", renderer);
    std::vector<Sprite> sprites;
    if (!tilemap)
    {
        std::cerr << "Failed to load tilemap texture\n";
        return;
    }
    TileSet tileset(tilemap);
    // Возьмем несколько тайлов из тайлсета
    const std::vector<std::pair<int, int>> tileIndices = {
        {4, 0}, // dirty floor
        {4, 1}, // dirty floor
        {3, 4}, // wall
        {8, 1}, // knight
        {9, 0}, // ghost
    };
    for (const auto &[i, j] : tileIndices)
    {
        sprites.push_back(Sprite(
            tilemap,
            SDL_FRect{float(j * (tileSize + 1)), float(i * (tileSize + 1)), float(tileSize), float(tileSize)}));
    }

    auto dungeon = std::make_shared<Dungeon>(LevelWidth, LevelHeight, RoomAttempts);
    const auto &grid = dungeon->getGrid();
    for (int i = 0; i < LevelHeight; ++i)
        for (int j = 0; j < LevelWidth; ++j)
        {
            const char *spriteName = nullptr;
            if (grid[i][j] == Dungeon::FLOOR)
            {
                spriteName = rand() % 2 == 0 ? "floor1" : "floor2";
            }
            else if (grid[i][j] == Dungeon::WALL)
            {
                spriteName = "wall";
            }
            if (spriteName)
            {
                world.toAddTiles.sprites.push_back(tileset.get_tile(spriteName));
                world.toAddTiles.transform2ds.push_back(Transform2D(j, i));
            }
        }

    auto heroPos = dungeon->getRandomFloorPosition();
    world.toAddHeroes.sprites.push_back(tileset.get_tile("knight"));
    world.toAddHeroes.transform2ds.push_back(Transform2D(heroPos.x, heroPos.y));
    world.toAddHeroes.heroes.push_back(Hero(&world));
    world.toAddHeroes.irestrictors.push_back(DungeonRestrictor(dungeon));
    world.toAddHeroes.healths.push_back(Health(100));
    world.toAddHeroes.staminas.push_back(Stamina(100));
    world.toAddHeroes.foodsources.push_back(FoodConsumer());

    for (int e = 0; e < BotPopulationCount; ++e)
    {
        const bool isPredator = (rand() % 100) < int(PredatorProbability * 100.f);
        auto enemyPos = dungeon->getRandomFloorPosition();
        world.toAddEnemies.sprites.push_back(isPredator ? tileset.get_tile("ghost") : tileset.get_tile("peasant"));
        world.toAddEnemies.transform2ds.push_back(Transform2D(enemyPos.x, enemyPos.y));
        world.toAddEnemies.enemies.push_back(Enemy());
        world.toAddEnemies.irestrictors.push_back(DungeonRestrictor(dungeon));
        world.toAddEnemies.healths.push_back(Health(100));
        world.toAddEnemies.staminas.push_back(Stamina(100));
        if (isPredator)
            world.toAddEnemies.foodsources.push_back(Predator());
        else
            world.toAddEnemies.foodsources.push_back(FoodConsumer());
    }

    auto foodFabriques = create_food_fabriques(&world, tileset);

    world.toAddFoodGenerators.foodgenerators.push_back(FoodGenerator(dungeon, std::move(foodFabriques), 2.f / RoomAttempts));
    for (int i = 0; i < InitialFoodAmount; i++)
        world.toAddFoodGenerators.foodgenerators[0].generate_random_food();
    world.toAddStarvationSystems.starvationsystems.push_back(StarvationSystem());
    world.toAddTirednessSystems.tirednesssystems.push_back(TirednessSystem());
}