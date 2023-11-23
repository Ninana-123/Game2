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
#include "inGameGUI.h"
#include <GLFW/glfw3.h>

namespace Engine
{

    // iterator for entities
    int iter = 0;

    // Declaration for window width and height
    int displayWidth = 0;
    int displayHeight = 0;

    // Declaration for cat's prev textures
    int prevTexture = 0;
    std::vector<int> prevTextures;

    // Declaration for isWalking
    bool isWalking = false;

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

    std::vector<std::pair<int, int>> PathfindingSystem::findShortestPath(int windowWidth, int windowHeight) 
    {

        // Adjusted the indexing to handle negative coordinates
        int adjustedStartX = startX + static_cast<int>(windowWidth/2);
        int adjustedStartY = startY + static_cast<int>(windowHeight/2);
        int adjustedGoalX = goalX + static_cast<int>(windowWidth/2);
        int adjustedGoalY = goalY + static_cast<int>(windowHeight/2);
        std::vector<std::vector<double>> distanceGrid(numRows, std::vector<double>(numCols, INFINITY));
        std::vector<std::vector<std::pair<int, int>>> parent(numRows, std::vector<std::pair<int, int>>(numCols, { -1, -1 }));
        std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;

        distanceGrid[adjustedStartX][adjustedStartY] = 0;
        pq.push(Node(adjustedStartX, adjustedStartY, 0));

        while (!pq.empty()) {
            Node current = pq.top();
            pq.pop();

            int x = current.x;
            int y = current.y;
            double cost = current.cost;

            if (x == adjustedGoalX && y == adjustedGoalY) {
                // We have reached the goal, reconstruct the path
                std::vector<std::pair<int, int>> path;
                while (x != -1 && y != -1) {
                    path.push_back({ x - static_cast<int>(windowWidth/2), y - static_cast<int>(windowHeight/2) });
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

    void PathfindingSystem::Update(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities) 
    {

        glfwGetFramebufferSize(glfwGetCurrentContext(), &displayWidth, &displayHeight); // Initialize window width and height

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
                TextureComponent* textureComponent = dynamic_cast<TextureComponent*>(entity->GetComponent(ComponentType::Texture));

                if (collisionComponent->layer == Layer::World) 
                {
                    startX = transformComponent->position.x;
                    startY = transformComponent->position.y;
                    goalX = pathfindingComponent->goalX;
                    goalY = pathfindingComponent->goalY;

                    if (!(pathfindingComponent->initialized)) 
                    {
                        
                        PathfindingSystem pathfinder(displayWidth, displayHeight);
                        pathfinder.setStart(startX, startY);
                        pathfinder.setGoal(goalX, goalY);
                        pathfindingComponent->path = pathfinder.findShortestPath(displayWidth, displayHeight);
                        pathfindingComponent->initialized = true;

                    }

                    //// Debug print for pathfinding
                    //std::cout << "Shortest Path for Entity " << entity->GetID() << ": ";
                    //for (const auto& point : pathfindingComponent->path) {
                    //    std::cout << "(" << point.first << ", " << point.second << ") ";
                    //}
                    //std::cout << std::endl;

                    // If path is not empty, execute path finding logic
                    if (!pathfindingComponent->path.empty()) 
                    {

                        // Infantry switch to walking mode
                        if ((pathfindingEntityTexture == 7))
                        {
                            if (textureComponent->textureKey.mainIndex == 1 && textureComponent->textureKey.subIndex == 0) 
                            {
                                textureComponent->textureKey = {"", 1, 1};
                            }
                            prevTextures.push_back(pathfindingEntityTexture);
                            prevTexture = pathfindingEntityTexture;
                            isWalking = true;
                        }

                        // Archer switch to walking mode
                        else if ((pathfindingEntityTexture == 8))
                        {
                            if (textureComponent->textureKey.mainIndex == 3 && textureComponent->textureKey.subIndex == 0) 
                            {
                                textureComponent->textureKey = {"", 3, 1};
                            }
                            prevTextures.push_back(pathfindingEntityTexture);
                            prevTexture = pathfindingEntityTexture;
                            isWalking = true;
                        }

                        // Tank switch to walking mode
                        else if ((pathfindingEntityTexture == 9))
                        {
                            if (textureComponent->textureKey.mainIndex == 2 && textureComponent->textureKey.subIndex == 0) 
                            {
                                textureComponent->textureKey = {"", 2, 1};
                            }
                            prevTextures.push_back(pathfindingEntityTexture);
                            prevTexture = pathfindingEntityTexture;
                            isWalking = true;
                        }

                        std::pair<int, int> nextPosition = pathfindingComponent->path[0];

                        // Update the entity's position
                        transformComponent->position.x = static_cast<float>(nextPosition.first);
                        transformComponent->position.y = static_cast<float>(nextPosition.second);

                        // Remove the first position from the path
                        pathfindingComponent->path.erase(pathfindingComponent->path.begin());
                    }

                    // Switch back to idle mode
                    else
                    {
                        // Infantry
                        if (prevTexture != 8 && prevTexture != 9 && textureComponent->textureKey.mainIndex == 1 && textureComponent->textureKey.subIndex == 1)
                        {
                            std::cout << "infantry here" << std::endl;
                            textureComponent->textureKey = {"", 1, 0};
                        }

                        // Archer
                        if (prevTexture != 7 && prevTexture != 9 && textureComponent->textureKey.mainIndex == 3 && textureComponent->textureKey.subIndex == 1)
                        {
                            std::cout << "archer here" << std::endl;
                            textureComponent->textureKey = {"", 3, 0};
                        }

                        // Tank
                        if (prevTexture != 7 && prevTexture != 8 && textureComponent->textureKey.mainIndex == 2 && textureComponent->textureKey.subIndex == 1)
                        {
                            std::cout << "tank here" << std::endl;
                            textureComponent->textureKey = {"", 2, 0};
                        }
                        
                    }

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