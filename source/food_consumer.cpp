#pragma once

#include "food_consumer.h"
#include "world.h"

void FoodConsumer::on_update(float dt, World *world, Transform2D &myTransform, Health &myHealth, Stamina &myStamina)
{
    for (int i = 0; i < world->currentFoods.size(); ++i)
    {
        // Simple collision check (assuming both have Transform2D)
        Transform2D &foodTransform = world->currentFoods.transform2ds[i];
        if (int(myTransform.x) == int(foodTransform.x) &&
            int(myTransform.y) == int(foodTransform.y))
        {
            if (std::holds_alternative<HealthFood>(world->currentFoods.foods[i]))
                std::get<HealthFood>(world->currentFoods.foods[i]).on_consume(world, myHealth, myStamina, world->currentFoods.ids[i]);
            else if (std::holds_alternative<StaminaFood>(world->currentFoods.foods[i]))
                std::get<StaminaFood>(world->currentFoods.foods[i]).on_consume(world, myHealth, myStamina, world->currentFoods.ids[i]);
            else
                throw "Unexpected Food type";
            break; // Consume only one food at a time
        }
    }
}
