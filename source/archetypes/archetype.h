#pragma once

#include <set>
#include <vector>

using TYPE_ID = int;

struct Archetype
{
    std::vector<TYPE_ID> ids;

    int size() const
    {
        return (int)ids.size();
    }
};

template <typename T>
void filterDelete(T &current, std::set<TYPE_ID> &toDelete)
{
    int counterLookup = 0;
    int counterWrite = 0;
    while (counterLookup < current.size())
    {
        if (toDelete.find(current.ids[counterLookup]) != toDelete.end())
        {
            current.move(counterLookup, counterWrite);
            ++counterLookup;
            ++counterWrite;
        }
        else
        {
            ++counterLookup;
        }
    }
    toDelete.clear();
}
