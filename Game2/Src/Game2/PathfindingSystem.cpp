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

    // Variables to try to get pathfinding to work from b to c and onwards
    std::vector<std::pair<int, int>> towerPositions = { {-275, -35}, {-70, 245} };
    std::pair<int, int> closestTower = { 0 ,0 };
    std::pair<int, int> firstTower = { 0 ,0 };
    std::pair<int, int> currentClosestTower = { 0 ,0 };
    int endPointX = 0;
    int endPointY = 0;
    std::pair<int, int> prevPos1 = { 0, 0 };
    std::pair<int, int> prevPos2 = { 0, 0 };

    // Define the collision map as a dynamically allocated 2D array
    int** collisionMap = nullptr;

    void PathfindingSystem::createLogicalCollisionMap() 
    {
        // Vector to store obstacle rectangles
        std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> obstacles;

        // Add obstacles to the vector (example with two obstacles)
        obstacles.push_back({ {190, -60}, {640, 360} });
        obstacles.push_back({ {-640, -360}, {10, 0} });
        obstacles.push_back({ {10, -220}, {640, -220} });
        obstacles.push_back({ {-640, 150}, {5, 360} });
        
        for (int i = 0; i < displayWidth; ++i) 
        {
            for (int j = 0; j < displayHeight; ++j) 
            {
                // Check if the cell is within any obstacle region
                bool isObstacle = false;
                for (const auto& obstacle : obstacles) {
                    if (i >= (displayWidth / 2) + obstacle.first.first && i < (displayWidth / 2) + obstacle.second.first &&
                        j >= (displayHeight / 2) + obstacle.first.second && j < (displayHeight / 2) + obstacle.second.second) 
                    {
                        isObstacle = true;
                        break;
                    }
                }

                // Set to 1 for obstacles, 0 for free cells
                collisionMap[i][j] = isObstacle ? 1 : 0;
            }
        }
    }

    void PathfindingSystem::initializeCollisionMap() 
    {
        // Set the size of the collision map based on displayWidth and displayHeight
        collisionMap = new int* [displayWidth];
        for (int i = 0; i < displayWidth; ++i) 
        {
            collisionMap[i] = new int[displayHeight];
        }

        // Create a logical collision map
        createLogicalCollisionMap();
    }

    // Check if a specific cell has collision
    bool PathfindingSystem::hasCollision(int x, int y) 
    {
        // Ensure the coordinates are within the grid bounds
        if (x >= 0 && x < displayWidth && y >= 0 && y < displayHeight) 
        {
            // Return true if the cell has collision
            return collisionMap[x][y] == 1;
        }
        // If the coordinates are outside the grid, consider it as having collision
        return true;
    }

    // Function to check if a cell is within the bounds of the grid
    bool PathfindingSystem::isValid(int x, int y) {
        // Check if x and y are within the grid's bounds
        bool isXWithinBounds = x >= 0 && x < numRows;
        bool isYWithinBounds = y >= 0 && y < numCols;

        // The cell is valid if both x and y are within bounds
        return isXWithinBounds && isYWithinBounds && !hasCollision(x, y);
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
        isWalking = false;

        // Call initializeCollisionMap only once in the constructor
        if (!collisionMap) {
            initializeCollisionMap();
        }
    }

    //PathfindingSystem::~PathfindingSystem() {
    //    // Release the memory for the collision map
    //    if (collisionMap != nullptr) {
    //        for (int i = 0; i < 1280; ++i) {
    //            delete[] collisionMap[i];
    //        }
    //        delete[] collisionMap;
    //    }
    //}

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

    //void PathfindingSystem::setStart(int x, int y) {
    //    if (hasCollision(x, y)) {
    //        // Starting point is inside a collided area, find the closest free cell
    //        std::pair<int, int> newStart = findClosestFreeCell(x, y);
    //        startX = newStart.first;
    //        startY = newStart.second;
    //    }
    //    else {
    //        startX = x;
    //        startY = y;
    //    }

    //}

    void PathfindingSystem::setGoal(int x, int y) {
        goalX = x;
        goalY = y;
    }

    //void PathfindingSystem::setGoal(int x, int y) {
    //    if (hasCollision(x, y)) {
    //        // Ending point is inside a collided area, find the closest free cell
    //        std::pair<int, int> newGoal = findClosestFreeCell(x, y);
    //        goalX = newGoal.first;
    //        goalY = newGoal.second;
    //    }
    //    else {
    //        goalX = x;
    //        goalY = y;
    //    }
    //}

    std::pair<int, int> PathfindingSystem::findClosestFreeCell(int x, int y) {
        // Define the search area as a rectangle with a given width and height
        const int SEARCH_WIDTH = 500;
        const int SEARCH_HEIGHT = 500;

        // Iterate through the cells in the rectangular search area
        for (int i = -SEARCH_WIDTH / 2; i <= SEARCH_WIDTH / 2; ++i) {
            for (int j = -SEARCH_HEIGHT / 2; j <= SEARCH_HEIGHT / 2; ++j) {
                int newX = x + i;
                int newY = y + j;

                // Check if the current cell is within the bounds of the collision map
                if (isValid(newX, newY)) {
                    // Check if the current cell is not colliding
                    if (!hasCollision(newX, newY)) {
                        //std::cout << "newGoal.first: " << newX << "newGoal.second: " << newY << std::endl;
                        return { newX, newY };  // Found a free cell
                    }
                }
            }
        }
        
        //std::cout << "function did nothing " << std::endl;
        // If no free cell is found in the search area, return the original point
        return { x, y };
    }

    std::pair<int, int> PathfindingSystem::getClosestPair(int startPosX, int startPosY, const std::vector<std::pair<int, int>>& towersPositions) 
    {
        double minDistance = std::numeric_limits<double>::max();

        for (const auto& tower : towersPositions) 
        {
            double currentDistance = distance(startPosX, startPosY, tower.first, tower.second);
            // std::cout << "tower.first : " << tower.first << "tower.second: " << tower.second << std::endl;
            if (currentDistance < minDistance) 
            {
                minDistance = currentDistance;
                closestTower = tower;
                if (closestTower.first == towersPositions[0].first) 
                {
                    prevPos1 = towersPositions[0];
                }
                if (closestTower.first == towersPositions[1].first)
                {
                    prevPos1 = towersPositions[1];
                }
                
            }
        }
        // Set new current endpoint check
        endPointX = startPosX;
        endPointY = startPosY;

        // Change path to other tower if at current tower
        if (towersPositions.size() > 1 && endPointX == closestTower.first && endPointY == closestTower.second + 80) 
        {
            if (closestTower.first == towersPositions[0].first && closestTower.second == towersPositions[0].second) 
            {
                currentClosestTower = towerPositions[1];
                prevPos2 = towersPositions[0];
            }
        }
        if (towersPositions.size() > 1 && endPointX == closestTower.first && endPointY == closestTower.second - 105) 
        {
            if (closestTower.first == towersPositions[1].first && closestTower.second == towersPositions[1].second)
            {
                currentClosestTower = towerPositions[0];
                prevPos2 = towersPositions[1];
            }
            return currentClosestTower;
        }
        else 
        {
            return closestTower;
        }   
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

        // std::cout << "MouseX: " << Input::GetMouseX() << "MouseY: " << Input::GetMouseY() << std::endl;

        // Iterate through entities that require pathfinding updates.
        for (const auto& it : *entities)
        {
            Entity* entity = it.second.get();

            if (entity->HasComponent(ComponentType::Transform) && entity->HasComponent(ComponentType::Collision))
            {

                PathfindingComponent* pathfindingComponent = dynamic_cast<PathfindingComponent*>(entity->GetComponent(ComponentType::Pathfinding));
                TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(entity->GetComponent(ComponentType::Transform));
                CollisionComponent* collisionComponent = dynamic_cast<CollisionComponent*>(entity->GetComponent(ComponentType::Collision));
                TextureComponent* textureComponent = dynamic_cast<TextureComponent*>(entity->GetComponent(ComponentType::Texture));

                if (entity->HasComponent(ComponentType::Pathfinding))
                {

                    if (collisionComponent->layer == Layer::World)
                    {

                        startX = static_cast<int>(transformComponent->position.x);
                        startY = static_cast<int>(transformComponent->position.y);

                        closestTower = getClosestPair(startX, startY, towerPositions);
                        // std::cout << currentClosestTower.first << currentClosestTower.second << std::endl;
                        if (endPointX != closestTower.first && endPointY != closestTower.second) 
                        {
                            goalX = closestTower.first;
                            goalY = closestTower.second;
                        }
                        
                        if (Input::IsKeyPressed(KEY_SPACE))
                        {
                            // std::cout << "currentClosestTower.first: " << currentClosestTower.first << "currentClosestTower.second: " << currentClosestTower.second << std::endl;
                            goalX = currentClosestTower.first;
                            goalY = currentClosestTower.second;

                            // Mark the pathfinding component as not initialized to recalculate the path
                            pathfindingComponent->initialized = false;
                        }

                        
                        if (!(pathfindingComponent->initialized))
                        {
                            PathfindingSystem pathfinder(displayWidth, displayHeight);
                            pathfinder.setStart(startX,startY);

                            // Check if both positions were attained before, go to castle if yes
                            if (pathfindingComponent->previousPos1.first && pathfindingComponent->previousPos2.first)
                            {
                                goalX = 345;
                                goalY = 75 - 140;
                            }

                            // If tower 1
                            if (goalX == -275 && goalY == -35) 
                            {
                                goalY = goalY + 80;
                                pathfindingComponent->previousPos1 = prevPos1;
                                // std::cout << "previousPos1: " << pathfindingComponent->previousPos1.first << std::endl;
                            }
                            // If tower 2
                            if (goalX == -70 && goalY == 245)
                            {
                                goalY = goalY - 105;
                                pathfindingComponent->previousPos2 = prevPos2;
                                // std::cout << "previousPos2: " << pathfindingComponent->previousPos2.first << std::endl;
                            }
                            
                            pathfinder.setGoal(goalX, goalY);
                            // std::cout << "inside goalX: " << goalX << "inside goalY: " << goalY << std::endl;
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
                                if ((textureComponent->textureKey.mainIndex == 1 && textureComponent->textureKey.subIndex == 0)
                                    || textureComponent->textureKey.mainIndex == 1 && textureComponent->textureKey.subIndex == 2)
                                {
                                    textureComponent->textureKey = { 1, 1 };
                                }
                                prevTextures.push_back(pathfindingEntityTexture);
                                prevTexture = pathfindingEntityTexture;
                                isWalking = true;
                            }

                            // Archer switch to walking mode
                            else if ((pathfindingEntityTexture == 8))
                            {
                                if ((textureComponent->textureKey.mainIndex == 3 && textureComponent->textureKey.subIndex == 0)
                                    || textureComponent->textureKey.mainIndex == 3 && textureComponent->textureKey.subIndex == 2)
                                {
                                    textureComponent->textureKey = { 3, 1 };
                                }
                                prevTextures.push_back(pathfindingEntityTexture);
                                prevTexture = pathfindingEntityTexture;
                                isWalking = true;
                            }

                            // Tank switch to walking mode
                            else if ((pathfindingEntityTexture == 9))
                            {
                                if ((textureComponent->textureKey.mainIndex == 2 && textureComponent->textureKey.subIndex == 0)
                                    || textureComponent->textureKey.mainIndex == 2 && textureComponent->textureKey.subIndex == 2)
                                {
                                    textureComponent->textureKey = { 2, 1 };
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

                        // Switch back to attacking mode
                        else
                        {
                            // Infantry
                            if (prevTexture != 8 && prevTexture != 9 && textureComponent->textureKey.mainIndex == 1 && textureComponent->textureKey.subIndex == 1)
                            {
                                // std::cout << "infantry here" << std::endl;
                                textureComponent->textureKey = { 1, 2 };
                            }

                            // Archer
                            if (prevTexture != 7 && prevTexture != 9 && textureComponent->textureKey.mainIndex == 3 && textureComponent->textureKey.subIndex == 1)
                            {
                                // std::cout << "archer here" << std::endl;
                                textureComponent->textureKey = { 3, 2 };
                            }

                            // Tank
                            if (prevTexture != 7 && prevTexture != 8 && textureComponent->textureKey.mainIndex == 2 && textureComponent->textureKey.subIndex == 1)
                            {
                                // std::cout << "tank here" << std::endl;
                                textureComponent->textureKey = { 2, 2 };
                            }

                            if (Input::IsMouseClicked(LEFT_MOUSE_BUTTON)) 
                            {
                                isGameOver = true;
                                // std::cout << "Hello check" << std::endl;
                            }

                        }

                    }
                }


                //// Testing for collision 
                //// Variables for last position
                //float lastPositionX = transformComponent->position.x;
                //float lastPositionY = transformComponent->position.y;
                //float nextPositionX = lastPositionX + 1;
                //float nextPositionY = lastPositionY + 1;

                //if (collisionComponent->isColliding) 
                //{
                //    if (lastPositionY < nextPositionY) 
                //    {
                //        transformComponent->position.y = lastPositionY - 5.f;
                //    }
                //    if ((lastPositionY > nextPositionY)) 
                //    {
                //        transformComponent->position.y = lastPositionY + 5.f;
                //    }
                //    if ((lastPositionX < nextPositionX)) 
                //    {
                //        transformComponent->position.x = lastPositionX + 5.f;
                //    }
                //    if ((lastPositionX > nextPositionX)) 
                //    {
                //        transformComponent->position.x = lastPositionX - 5.f;
                //    }
                //}
            }
        }
    }
}


