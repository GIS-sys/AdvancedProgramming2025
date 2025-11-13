#pragma once

#include <vector>

#include "archetypes/archetype.h"
#include "sprite.h"
#include "transform2d.h"
#include "enemy.h"
#include "restrictor.h"
#include "health.h"
#include "stamina.h"
#include "food_consumer.h"

struct EnemiesArchetype : Archetype
{
    std::vector<Sprite> sprites;
    std::vector<Transform2D> transform2ds;
    std::vector<Enemy> enemies;
    std::vector<IRestrictor *> irestrictors;
    std::vector<Health> healths;
    std::vector<Stamina> staminas;
    std::vector<std::variant<Predator, FoodConsumer>> foodsources;

    void move(int iFrom, int iTo)
    {
        ids[iFrom] = std::move(ids[iTo]);
        sprites[iFrom] = std::move(sprites[iTo]);
        transform2ds[iFrom] = std::move(transform2ds[iTo]);
        heroes[iFrom] = std::move(heroes[iTo]);
        irestrictors[iFrom] = std::move(irestrictors[iTo]);
        healths[iFrom] = std::move(healths[iTo]);
        staminas[iFrom] = std::move(staminas[iTo]);
        foodsources[iFrom] = std::move(foodsources[iTo]);
    }

    void extendMove(EnemiesArchetype &other)
    {
        ids.insert(ids.end(), std::make_move_iterator(other.ids.begin()), std::make_move_iterator(other.ids.end()));
        sprites.insert(sprites.end(), std::make_move_iterator(other.sprites.begin()), std::make_move_iterator(other.sprites.end()));
        transform2ds.insert(transform2ds.end(), std::make_move_iterator(other.transform2ds.begin()), std::make_move_iterator(other.transform2ds.end()));
        heroes.insert(heroes.end(), std::make_move_iterator(other.heroes.begin()), std::make_move_iterator(other.heroes.end()));
        irestrictors.insert(irestrictors.end(), std::make_move_iterator(other.irestrictors.begin()), std::make_move_iterator(other.irestrictors.end()));
        healths.insert(healths.end(), std::make_move_iterator(other.healths.begin()), std::make_move_iterator(other.healths.end()));
        staminas.insert(staminas.end(), std::make_move_iterator(other.staminas.begin()), std::make_move_iterator(other.staminas.end()));
        foodsources.insert(foodsources.end(), std::make_move_iterator(other.foodsources.begin()), std::make_move_iterator(other.foodsources.end()));
        other.ids.clear();
        other.sprites.clear();
        other.transform2ds.clear();
        other.heroes.clear();
        other.irestrictors.clear();
        other.healths.clear();
        other.staminas.clear();
        other.foodsources.clear();
    }

    void update(int i, float dt, World *world)
    {
        // TODO
    }
};
