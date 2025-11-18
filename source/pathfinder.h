#pragma once

#include "transform2d.h"
#include <queue>
#include <unordered_map>
#include <functional>

class Pathfinder
{
private:
    std::vector<int2> currentPath; // starts from current cell, ends with target position if reachable
    size_t currentPathIndex = 0;
    int2 currentTargetPosition;

public:
    int2 getNextPos() const
    {
        return currentPath[currentPathIndex];
    }

    void updatePosition(const Transform2D &transform, const DungeonRestrictor &restrictor, std::optional<int2> targetPosition = std::nullopt)
    {
        if (!targetPosition)
            targetPosition = currentTargetPosition;

        int2 currentPos = {(int)transform.x, (int)transform.y};

        if (currentPath.empty() || currentPathIndex >= currentPath.size() - 1 || getNextPos() != currentPos || currentTargetPosition != *targetPosition)
        {
            currentTargetPosition = *targetPosition;
            currentPath = findPathAStar(currentPos, currentTargetPosition, restrictor);
            if (currentPath.size() < 2)
            {
                currentPath = findRandomPath(currentPos, restrictor);
            }
            currentPathIndex = 1;
        }
        else
        {
            ++currentPathIndex;
        }
    }

public:
    // A* pathfinding algorithm
    std::vector<int2> findPathAStar(
        int2 start,
        int2 goal,
        const DungeonRestrictor &restrictor,
        std::function<bool(int2)> cellValidator = nullptr,
        std::function<float(int2, int2)> heuristic = heuristicManhattan) const
    {
        // combine restrictor check with optional validator
        auto isValidCell = [&](int2 cell)
        {
            if (!restrictor.can_pass(cell))
                return false;
            if (cellValidator && !cellValidator(cell))
                return false;
            return true;
        };

        // check start
        if (!restrictor.can_pass(start))
        {
            return {};
        }

        // check end
        if (!isValidCell(goal))
        {
            return {};
        }

        // A*
        std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openSet;
        std::unordered_map<int, std::unordered_map<int, float>> gCostMap;
        std::unordered_map<int, std::unordered_map<int, int2>> cameFrom;

        openSet.push({start, 0.0f, heuristic(start, goal)});
        gCostMap[start.x][start.y] = 0.0f;

        const int2 directions[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        while (!openSet.empty())
        {
            Node current = openSet.top();
            openSet.pop();

            // end if the goal is reached
            if (current.position == goal)
            {
                return reconstructPath(cameFrom, current.position, start);
            }

            // explore neighbors
            for (const auto &dir : directions)
            {
                int2 neighbor = current.position + dir;
                if (!isValidCell(neighbor))
                {
                    continue;
                }
                float tentativeGCost = gCostMap[current.position.x][current.position.y] + 1.0f;
                if (!gCostMap.count(neighbor.x) || !gCostMap[neighbor.x].count(neighbor.y) ||
                    tentativeGCost < gCostMap[neighbor.x][neighbor.y])
                {
                    cameFrom[neighbor.x][neighbor.y] = current.position;
                    gCostMap[neighbor.x][neighbor.y] = tentativeGCost;

                    float hCost = heuristic(neighbor, goal);
                    openSet.push({neighbor, tentativeGCost, hCost});
                }
            }
        }

        return {};
    }

    static float heuristicManhattan(int2 a, int2 b)
    {
        return std::abs(a.x - b.x) + std::abs(a.y - b.y);
    }

private:
    struct Node
    {
        int2 position;
        float gCost; // cost from start to this node
        float hCost; // heuristic cost to goal
        float fCost() const { return gCost + hCost; }

        bool operator>(const Node &other) const
        {
            return fCost() > other.fCost();
        }
    };

    static std::vector<int2> reconstructPath(std::unordered_map<int, std::unordered_map<int, int2>> &cameFrom, int2 current, int2 start)
    {
        std::vector<int2> path;

        while (cameFrom.count(current.x) && cameFrom[current.x].count(current.y))
        {
            path.push_back(current);
            current = cameFrom[current.x][current.y];
        }
        path.push_back(start);

        std::reverse(path.begin(), path.end());
        return path;
    }

    static std::vector<int2> findRandomPath(int2 currentPos, const DungeonRestrictor &restrictor)
    {
        std::vector<int2> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        std::vector<int2> directionsPassable;
        std::copy_if(directions.begin(), directions.end(), std::back_inserter(directionsPassable), [&restrictor, &currentPos](const int2 &pos)
                     { return restrictor.can_pass(currentPos + pos); });
        if (directionsPassable.empty())
            return {currentPos, currentPos};

        int i = rand() % directionsPassable.size();
        int2 intDelta = directionsPassable[i];
        int2 newPos = currentPos + intDelta;
        return {currentPos, newPos};
    }
};