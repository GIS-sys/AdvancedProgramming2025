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
            if (currentPath.empty() || currentPath.size() == 1)
            {
                currentPath = findRandomPath(currentPos, restrictor);
            }
            currentPathIndex = 1;
            // std::cout << std::endl;
            // std::cout << currentPath.size() << " ";
            // std::cout << currentPos.x << "," << currentPos.y << " ";
            // std::cout << currentTargetPosition.x << "," << currentTargetPosition.y << " ";
            // std::cout << std::endl;
        }
        else
        {
            ++currentPathIndex;
        }
    }

private:
    // A* pathfinding algorithm const
    std::vector<int2> findPathAStar(
        int2 start,
        int2 goal,
        const DungeonRestrictor &restrictor,
        std::function<bool(int2)> cellValidator = nullptr,
        std::function<float(int2, int2)> heuristic = heuristicManhattan)
    {
        // If start or goal is not passable, return empty path
        if (!restrictor.can_pass(start) || !restrictor.can_pass(goal))
        {
            return {};
        }

        // Custom validation: combine restrictor check with optional validator
        auto isValidCell = [&](int2 cell)
        {
            if (!restrictor.can_pass(cell))
                return false;
            if (cellValidator && !cellValidator(cell))
                return false;
            return true;
        };

        // If goal is not valid according to custom validator, return empty path
        if (cellValidator && !cellValidator(goal))
        {
            return {};
        }

        // A* algorithm implementation
        struct Node
        {
            int2 position;
            float gCost; // Cost from start to this node
            float hCost; // Heuristic cost to goal
            float fCost() const { return gCost + hCost; }

            bool operator>(const Node &other) const
            {
                return fCost() > other.fCost();
            }
        };

        // Priority queue for open set
        std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openSet;

        // Maps for tracking costs and paths
        std::unordered_map<int, std::unordered_map<int, float>> gCostMap;
        std::unordered_map<int, std::unordered_map<int, int2>> cameFrom;

        // Initialize start node
        openSet.push({start, 0.0f, heuristic(start, goal)});
        gCostMap[start.x][start.y] = 0.0f;

        // Possible movement directions (4-way movement)
        const int2 directions[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        while (!openSet.empty())
        {
            Node current = openSet.top();
            openSet.pop();

            // Check if we reached the goal
            if (current.position.x == goal.x && current.position.y == goal.y)
            {
                return reconstructPath(cameFrom, current.position, start);
            }

            // Explore neighbors
            for (const auto &dir : directions)
            {
                int2 neighbor = {current.position.x + dir.x, current.position.y + dir.y};

                // Check if neighbor is valid
                if (!isValidCell(neighbor))
                {
                    continue;
                }

                // Calculate tentative gCost
                float tentativeGCost = gCostMap[current.position.x][current.position.y] + 1.0f;

                // Check if we found a better path to neighbor
                if (!gCostMap.count(neighbor.x) || !gCostMap[neighbor.x].count(neighbor.y) ||
                    tentativeGCost < gCostMap[neighbor.x][neighbor.y])
                {

                    // This path to neighbor is better than any previous one
                    cameFrom[neighbor.x][neighbor.y] = current.position;
                    gCostMap[neighbor.x][neighbor.y] = tentativeGCost;

                    float hCost = heuristic(neighbor, goal);
                    openSet.push({neighbor, tentativeGCost, hCost});
                }
            }
        }

        // No path found
        return {};
    }

    static float heuristicManhattan(int2 a, int2 b)
    {
        return std::abs(a.x - b.x) + std::abs(a.y - b.y);
    }

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