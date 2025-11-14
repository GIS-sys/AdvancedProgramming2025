#pragma once

#include <variant>
#include <vector>

#include "archetypes/archetype.h"
#include "sprite.h"
#include "transform2d.h"
#include "enemy.h"
#include "dungeon_restrictor.h"
#include "health.h"
#include "stamina.h"
#include "predator.h"
#include "food_consumer.h"

class World;

struct EnemiesArchetype : Archetype
{
    std::vector<Sprite> sprites;
    std::vector<Transform2D> transform2ds;
    std::vector<Enemy> enemies;
    std::vector<DungeonRestrictor> irestrictors;
    std::vector<Health> healths;
    std::vector<Stamina> staminas;
    std::vector<std::variant<Predator, FoodConsumer>> foodsources;

    void move(int iFrom, int iTo)
    {
        ids[iTo] = std::move(ids[iFrom]);
        sprites[iTo] = std::move(sprites[iFrom]);
        transform2ds[iTo] = std::move(transform2ds[iFrom]);
        enemies[iTo] = std::move(enemies[iFrom]);
        irestrictors[iTo] = std::move(irestrictors[iFrom]);
        healths[iTo] = std::move(healths[iFrom]);
        staminas[iTo] = std::move(staminas[iFrom]);
        foodsources[iTo] = std::move(foodsources[iFrom]);
    }

    void shrink(int toSize)
    {
        eraseAfterIndex(ids, toSize);
        eraseAfterIndex(sprites, toSize);
        eraseAfterIndex(transform2ds, toSize);
        eraseAfterIndex(enemies, toSize);
        eraseAfterIndex(irestrictors, toSize);
        eraseAfterIndex(healths, toSize);
        eraseAfterIndex(staminas, toSize);
        eraseAfterIndex(foodsources, toSize);
    }

    void extendMove(EnemiesArchetype &other)
    {
        ids.insert(ids.end(), std::make_move_iterator(other.ids.begin()), std::make_move_iterator(other.ids.end()));
        sprites.insert(sprites.end(), std::make_move_iterator(other.sprites.begin()), std::make_move_iterator(other.sprites.end()));
        transform2ds.insert(transform2ds.end(), std::make_move_iterator(other.transform2ds.begin()), std::make_move_iterator(other.transform2ds.end()));
        enemies.insert(enemies.end(), std::make_move_iterator(other.enemies.begin()), std::make_move_iterator(other.enemies.end()));
        irestrictors.insert(irestrictors.end(), std::make_move_iterator(other.irestrictors.begin()), std::make_move_iterator(other.irestrictors.end()));
        healths.insert(healths.end(), std::make_move_iterator(other.healths.begin()), std::make_move_iterator(other.healths.end()));
        staminas.insert(staminas.end(), std::make_move_iterator(other.staminas.begin()), std::make_move_iterator(other.staminas.end()));
        foodsources.insert(foodsources.end(), std::make_move_iterator(other.foodsources.begin()), std::make_move_iterator(other.foodsources.end()));
        other.ids.clear();
        other.sprites.clear();
        other.transform2ds.clear();
        other.enemies.clear();
        other.irestrictors.clear();
        other.healths.clear();
        other.staminas.clear();
        other.foodsources.clear();
    }

    int sizeNoID() const
    {
        int size = sprites.size();
        if (size != transform2ds.size() ||
            size != enemies.size() ||
            size != irestrictors.size() ||
            size != healths.size() ||
            size != staminas.size() ||
            size != foodsources.size())
        {
            throw "EnemiesArchetype: sizeNoID() detected uneven vectors filling (you probably forgot to add some field when creating new object)";
        }
        return size;
    }

    void update(int i, float dt, World *world);
};
