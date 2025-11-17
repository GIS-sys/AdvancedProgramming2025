#pragma once

#include "predator.h"
#include "food_consumer.h"
#include <variant>

using FOOD_SOURCES_TYPE = std::variant<Predator, FoodConsumer>;
