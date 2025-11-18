#pragma once

#include <cmath>

struct float2
{
    float x, y;
    float2(float x = 0, float y = 0) : x(x), y(y) {}
};

struct int2
{
    int x, y;
    int2(int x = 0, int y = 0) : x(x), y(y) {}

    bool operator==(const int2 &other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(const int2 &other) const
    {
        return !(*this == other);
    }

    int2 operator+(const int2 &other) const
    {
        return {x + other.x, y + other.y};
    }

    int2 operator-() const
    {
        return {-x, -y};
    }

    int2 operator-(const int2 &other) const
    {
        return *this + (-other);
    }

    float length() const { return std::sqrt(x * x + y * y); }

    int2 toDirection() const
    {
        float2 copy{x / length(), y / length()};
        return {(int)(copy.x * 2), (int)(copy.y * 2)};
    }
};
