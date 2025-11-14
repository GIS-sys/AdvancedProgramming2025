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

    static int getNextCounter();
};

template <typename T>
void filterDelete(T &current, std::set<TYPE_ID> &toDelete)
{
    int counterLookup = 0;
    int counterWrite = 0;
    while (counterLookup < current.size())
    {
        if (toDelete.find(current.ids[counterLookup]) == toDelete.end())
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
    current.shrink(counterWrite);
    toDelete.clear();
}

template <typename T>
void fillIDs(T &current)
{
    int size = current.sizeNoID();
    while (current.size() < size)
    {
        current.ids.push_back(Archetype::getNextCounter());
    }
}

template <typename T>
void eraseAfterIndex(std::vector<T> &vec, int i)
{
    if (i < (int)vec.size())
        vec.erase(vec.begin() + i, vec.end());
}
