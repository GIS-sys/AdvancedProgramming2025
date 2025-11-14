#pragma once

class World;

class TirednessSystem
{
    float accumulator = 0.0f;
    const float tirednessInterval = 1.0f; // seconds
    const int tirednessAmount = 5;        // stamina points
public:
    void on_update(float dt, World *world);

    TirednessSystem &operator=(TirednessSystem &&other)
    {
        accumulator = other.accumulator;
        return *this;
    }

    TirednessSystem(const TirednessSystem &) = default;
    TirednessSystem() = default;
};
