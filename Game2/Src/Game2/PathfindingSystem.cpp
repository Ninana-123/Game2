/******************************************************************************/
/*!
\file		PathfindingSystem.cpp
\author		Ang Jun Sheng Aloysius, a.junshengaloysius, 2201807

\par		a.junshengaloysius@digipen.edu

\date		10/10/2023

\brief		Contains the definitions for the logic of the pathfinding system.
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
 */
 /******************************************************************************/

#include "pch.h"
#include "PathfindingSystem.h"
#include "TransformComponent.h"
#include "Entity.h"
#include "EntityManager.h"

namespace Engine
{

    // iterator for entities
    int i = 0;
 
    // Function to check if a cell is within the bounds of the grid
    bool PathfindingSystem::isValid(int x, int y) {
        // Check if x and y are within the grid's bounds
        bool isXWithinBounds = x >= 0 && x < numRows;
        bool isYWithinBounds = y >= 0 && y < numCols;

        // The cell is valid if both x and y are within bounds
        return isXWithinBounds && isYWithinBounds;
    }

    // Function to calculate the Euclidean distance between two points
    double PathfindingSystem::distance(int x1, int y1, int x2, int y2) {
        int dx = x2 - x1;
        int dy = y2 - y1;
        int dxSquared = dx * dx;
        int dySquared = dy * dy;

        return std::sqrt(dxSquared + dySquared);
    }

    PathfindingSystem::PathfindingSystem(int _numRows, int _numCols) {
        numRows = _numRows;
        numCols = _numCols;
        startX = 0;
        startY = 0;
        goalX = 0;
        goalY = 0;
        initialized = false;
    }


    PathfindingSystem::Node::Node(int _x, int _y, double _cost) {
        x = _x;
        y = _y;
        cost = _cost;
    }

    bool PathfindingSystem::Node::operator>(const Node& other) const {
        return cost > other.cost;
    }

    void PathfindingSystem::setStart(int x, int y) {
        startX = x;
        startY = y;
    }

    void PathfindingSystem::setGoal(int x, int y) {
        goalX = x;
        goalY = y;
    }

    // Dijkstra's algorithm to find the shortest path
    std::vector<std::pair<int, int>> PathfindingSystem::findShortestPath() {
        std::vector<std::vector<double>> distanceGrid(numRows, std::vector<double>(numCols, INFINITY));
        std::vector<std::vector<std::pair<int, int>>> parent(numRows, std::vector<std::pair<int, int>>(numCols, { -1, -1 }));
        std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;

        distanceGrid[startX][startY] = 0;
        pq.push(Node(startX, startY, 0));

        while (!pq.empty()) {
            Node current = pq.top();
            pq.pop();

            int x = current.x;
            int y = current.y;
            double cost = current.cost;

            if (x == goalX && y == goalY) {
                // We have reached the goal, reconstruct the path
                std::vector<std::pair<int, int>> path;
                while (x != -1 && y != -1) {
                    path.push_back({ x, y });
                    int newX = parent[x][y].first;
                    int newY = parent[x][y].second;
                    x = newX;
                    y = newY;
                }
                std::reverse(path.begin(), path.end());
                return path;
            }

            // Explore neighbors (up, down, left, right)
            int dx[] = { -1, 1, 0, 0 };
            int dy[] = { 0, 0, -1, 1 };

            for (int i = 0; i < 4; i++) {
                int newX = x + dx[i];
                int newY = y + dy[i];

                if (isValid(newX, newY)) {
                    double newCost = cost + distance(x, y, newX, newY);

                    if (newCost < distanceGrid[newX][newY]) {
                        distanceGrid[newX][newY] = newCost;
                        parent[newX][newY] = { x, y };
                        pq.push(Node(newX, newY, newCost));
                    }
                }
            }
        }

        // No path found
        return {};
    }

    bool PathfindingSystem::bellmanFord() {
        std::vector<std::vector<double>> distanceGrid(numRows, std::vector<double>(numCols, INFINITY));
        std::vector<std::vector<std::pair<int, int>>> parent(numRows, std::vector<std::pair<int, int>>(numCols, { -1, -1 }));

        distanceGrid[startX][startY] = 0;

        // Relax edges repeatedly
        for (int k = 0; k < numRows * numCols - 1; k++) {
            for (int i = 0; i < numRows; i++) {
                for (int j = 0; j < numCols; j++) {
                    if (distanceGrid[i][j] != INFINITY) {
                        // Explore neighbors (up, down, left, right)
                        int dx[] = { -1, 1, 0, 0 };
                        int dy[] = { 0, 0, -1, 1 };

                        for (int l = 0; l < 4; l++) {
                            int newX = i + dx[l];
                            int newY = j + dy[l];

                            if (isValid(newX, newY)) {
                                double newCost = distanceGrid[i][j] + distance(i, j, newX, newY);

                                if (newCost < distanceGrid[newX][newY]) {
                                    distanceGrid[newX][newY] = newCost;
                                    parent[newX][newY] = { i, j };
                                }
                            }
                        }
                    }
                }
            }
        }

        // Check for negative cycles
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                if (distanceGrid[i][j] != INFINITY) {
                    int dx[] = { -1, 1, 0, 0 };
                    int dy[] = { 0, 0, -1, 1 };

                    for (int l = 0; l < 4; l++) {
                        int newX = i + dx[l];
                        int newY = j + dy[l];

                        if (isValid(newX, newY)) {
                            double newCost = distanceGrid[i][j] + distance(i, j, newX, newY);

                            if (newCost < distanceGrid[newX][newY]) {
                                // Negative cycle detected
                                return false;
                            }
                        }
                    }
                }
            }
        }

        return true;
    }

    void PathfindingSystem::Update(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities) 
    {
        

        // Iterate through entities that require pathfinding updates.
        for (const auto& it : *entities) 
        {
            Entity* entity = it.second.get();

            if (entity->HasComponent(ComponentType::Pathfinding) && entity->HasComponent(ComponentType::Transform) 
                && entity->HasComponent(ComponentType::Collision))
            {

                PathfindingComponent* pathfindingComponent = dynamic_cast<PathfindingComponent*>(entity->GetComponent(ComponentType::Pathfinding));
                TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(entity->GetComponent(ComponentType::Transform));
                CollisionComponent* collisionComponent = dynamic_cast<CollisionComponent*>(entity->GetComponent(ComponentType::Collision));

                //int startX = transformComponent->position.x;
                //int startY = transformComponent->position.y;
                startX = pathfindingComponent->startX;
                startY = pathfindingComponent->startY;
                goalX = pathfindingComponent->goalX;
                goalY = pathfindingComponent->goalY;
                //if (!(pathfindingComponent->initialized)) {
                //    
                //    PathfindingSystem pathfinder(720, 1280);
                //    pathfinder.setStart(startX, startY);
                //    pathfinder.setGoal(goalX, goalY);
                //    pathfindingComponent->path = pathfinder.findShortestPath();
                //    //path = pathfinder.findShortestPath();
                //    pathfindingComponent->initialized = true;

                //}


                if (2 > i) {

                    PathfindingSystem pathfinder(720, 1280);
                    pathfinder.setStart(startX, startY);
                    pathfinder.setGoal(goalX, goalY);
                    pathfindingComponent->path = pathfinder.findShortestPath();
                    //path = pathfinder.findShortestPath();
                    //pathfindingComponent->initialized = true;
                    i++;
                }

                //std::cout << "Shortest Path for Entity " << entity->GetID() << ": ";
                //for (const auto& point : pathfindingComponent->path) {
                //    std::cout << "(" << point.first << ", " << point.second << ") ";
                //}
                //std::cout << std::endl;

                if (!pathfindingComponent->path.empty()) {
                    std::pair<int, int> nextPosition = pathfindingComponent->path[0];

                    // Update the entity's position
                    transformComponent->position.x = static_cast<float>(nextPosition.first);
                    transformComponent->position.y = static_cast<float>(nextPosition.second);

                    // Remove the first position from the path
                    pathfindingComponent->path.erase(pathfindingComponent->path.begin());
                }

                // Testing for collision 
                // Variables for last position
                float lastPositionX = transformComponent->position.x;
                float lastPositionY = transformComponent->position.y;
                float nextPositionX = lastPositionX + 1;
                float nextPositionY = lastPositionY + 1;

                if (collisionComponent->isColliding) {
                    if (lastPositionY < nextPositionY) {
                        transformComponent->position.y = lastPositionY - 5.f;
                    }
                    if ((lastPositionY > nextPositionY)) {
                        transformComponent->position.y = lastPositionY + 5.f;
                    }
                    if ((lastPositionX < nextPositionX)) {
                        transformComponent->position.x = lastPositionX + 5.f;
                    }
                    if ((lastPositionX > nextPositionX)) {
                        transformComponent->position.x = lastPositionX - 5.f;
                    }
                }
            }
        }
    }
}


