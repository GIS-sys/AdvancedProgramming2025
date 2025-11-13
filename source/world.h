#pragma once

#include <set>

#include "archetypes/tiles.h"

class World : public std::enable_shared_from_this<World>
{
public:
    void update(float dt)
    {
        filterDelete(currentTiles, toDeleteTiles);
        currentTiles.extendMove(toAddTiles);
        for (int i = 0; i < currentTiles.size(); ++i)
            currentTiles.update(i, this);
    }

public:
    TilesArchetype currentTiles;
    TilesArchetype toAddTiles;
    std::set<TYPE_ID> toDeleteTiles;
};
