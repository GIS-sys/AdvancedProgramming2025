#pragma once

class World;

class MateSystem
{
    float accumulator = 0.0f;
    const float mateInterval = 1.0f; // seconds
public:
    void on_update(float dt, World *world);

    MateSystem &operator=(MateSystem &&other)
    {
        accumulator = other.accumulator;
        return *this;
    }

    MateSystem(const MateSystem &) = default;
    MateSystem() = default;
};
