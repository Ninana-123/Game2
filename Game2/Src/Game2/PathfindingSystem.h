//#pragma once

#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include "System.h"
#include "PathfindingComponent.h"

namespace Engine
{
    class PathfindingSystem : public System
    {
    public:
        void Update(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities) override;
    
        PathfindingSystem(): numRows(0), numCols(0), startX(0), startY(0), goalX(0), goalY(0), initialized(false) {}
        PathfindingSystem(int numRows, int numCols);

        void setStart(int x, int y);
        void setGoal(int x, int y);

        std::vector<std::pair<int, int>> findShortestPath();

    private:
        struct Node {
            int x, y;
            double cost;

            Node(int _x, int _y, double _cost);

            bool operator>(const Node& other) const;
        };

        bool isValid(int x, int y);
        double distance(int x1, int y1, int x2, int y2);

        int numRows = 0;
        int numCols = 0;
        int startX = 0;
        int startY = 0;
        int goalX = 0;
        int goalY = 0;

        bool initialized; // A flag to check if the pathfinder has been initialized
    };
}


#endif


