#pragma once

class World;

class StarvationSystem
{
    float accumulator = 0.0f;
    const float damageInterval = 1.0f; // seconds
    const int damageAmount = 2;        // health points
public:
    void on_update(float dt, World *world);

    StarvationSystem &operator=(StarvationSystem &&other)
    {
        accumulator = other.accumulator;
    }
};
