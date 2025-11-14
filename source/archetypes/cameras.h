#pragma once

#include <vector>

#include "archetypes/archetype.h"
#include "camera2d.h"
#include "transform2d.h"

class World;

struct CamerasArchetype : Archetype
{
    std::vector<Camera2D> camera2ds;
    std::vector<Transform2D> transform2ds;

    void move(int iFrom, int iTo)
    {
        ids[iTo] = std::move(ids[iFrom]);
        camera2ds[iTo] = std::move(camera2ds[iFrom]);
        transform2ds[iTo] = std::move(transform2ds[iFrom]);
    }

    void shrink(int toSize)
    {
        eraseAfterIndex(ids, toSize);
        eraseAfterIndex(camera2ds, toSize);
        eraseAfterIndex(transform2ds, toSize);
    }

    void extendMove(CamerasArchetype &other)
    {
        ids.insert(ids.end(), std::make_move_iterator(other.ids.begin()), std::make_move_iterator(other.ids.end()));
        camera2ds.insert(camera2ds.end(), std::make_move_iterator(other.camera2ds.begin()), std::make_move_iterator(other.camera2ds.end()));
        transform2ds.insert(transform2ds.end(), std::make_move_iterator(other.transform2ds.begin()), std::make_move_iterator(other.transform2ds.end()));
        other.ids.clear();
        other.camera2ds.clear();
        other.transform2ds.clear();
    }

    int sizeNoID() const
    {
        int size = camera2ds.size();
        if (size != transform2ds.size())
        {
            throw "CamerasArchetype: sizeNoID() detected uneven vectors filling (you probably forgot to add some field when creating new object)";
        }
        return size;
    }

    void update(int i, float dt, World *world);
};
