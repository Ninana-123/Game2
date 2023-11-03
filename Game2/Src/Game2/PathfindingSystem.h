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

        void InitializePathfinder(int numRows, int numCols); 

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

        int numRows;
        int numCols;
        int startX;
        int startY;
        int goalX;
        int goalY;

        bool initialized; // A flag to check if the pathfinder has been initialized
    };
}


#endif


