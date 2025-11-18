#pragma once

#include <vector>

class CacheModule
{
private:
    int cacheIndex;

    int generateRand()
    {
        cacheIndex = rand();
    }

public:
    CacheModule()
    {
        generateRand();
    }

    void invalidate()
    {
        generateRand();
    }

    bool operator==(const CacheModule &other)
    {
        return cacheIndex == other.cacheIndex;
    }
};
