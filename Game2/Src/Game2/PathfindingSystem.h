/******************************************************************************/
/*!
\file		PathfindingSystem.h
\author		Ang Jun Sheng Aloysius, a.junshengaloysius, 2201807

\par		a.junshengaloysius@digipen.edu

\date		10/10/2023

\brief		Contains the declaration for the logic of the pathfinding system.
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
 */
 /******************************************************************************/

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
        /**************************************************************************/
        /*!
        \brief Update function to process pathfinding for a collection of entities.

        \param[in] entities
        A pointer to an `std::unordered_map` containing entities associated with unique IDs.

        */
        /**************************************************************************/
        void Update(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities) override;
    
        /**************************************************************************/
        /*!
        \brief Initialize the pathfinding system for a grid-based map with a specified number of rows and columns.

        \param[in] numRows
        The number of rows in the grid.

        \param[in] numCols
        The number of columns in the grid.

        */
        /**************************************************************************/
        PathfindingSystem() : numRows(0), numCols(0), startX(0), startY(0), goalX(0), goalY(0), initialized(false) {}

        /**************************************************************************/
        /*!
        \brief Constructor for the PathfindingSystem with a specified number of rows and columns for pathfinding.

        \param[in] numRows
        The number of rows in the grid.

        \param[in] numCols
        The number of columns in the grid.

        */
        /**************************************************************************/
        PathfindingSystem(int numRows, int numCols);

        PathfindingSystem(int numRows, int numCols, const std::vector<std::pair<float, float>>& _towerPositions);


        /**************************************************************************/
        /*!
        \brief Set the starting point for pathfinding in the grid.

        \param[in] x
        The x-coordinate of the starting point.

        \param[in] y
        The y-coordinate of the starting point.

        */
        /**************************************************************************/
        void setStart(int x, int y);

        /**************************************************************************/
        /*!
        \brief Set the goal or target point for pathfinding in the grid.

        \param[in] x
        The x-coordinate of the goal point.

        \param[in] y
        The y-coordinate of the goal point.

        */
        /**************************************************************************/
        void setGoal(int x, int y);

        /**************************************************************************/
        /*!
        \brief Find the shortest path between the set starting and goal points on the grid.

        \param[out]
        A vector containing pairs of x and y coordinates representing the shortest path.

        */
        /**************************************************************************/
        std::vector<std::pair<int, int>> findShortestPath(int windowWidth, int windowHeight);

        std::vector<std::pair<int, int>> findShortestPath(int windowWidth, int windowHeight, const std::vector<std::pair<float, float>>& towers);

        void createLogicalCollisionMap();

        void initializeCollisionMap();

        bool hasCollision(int x, int y);

        std::pair<int, int> findClosestFreeCell(int x, int y);

    private:
        struct Node {
            int x, y;
            double cost;

            Node(int _x, int _y, double _cost);

            bool operator>(const Node& other) const;
        };

        /**************************************************************************/
        /*!
        \brief Check the validity of a grid position with the specified x and y coordinates.

        \param[in] x
        The x-coordinate of the grid position to be checked.

        \param[in] y
        The y-coordinate of the grid position to be checked.

        \return
        `true` if the position is valid; otherwise, `false`.

        */
        /**************************************************************************/
        bool isValid(int x, int y);

        /**************************************************************************/
        /*!
        \brief Calculate the Euclidean distance between two grid positions with the specified coordinates.

        \param[in] x1
        The x-coordinate of the first position.

        \param[in] y1
        The y-coordinate of the first position.

        \param[in] x2
        The x-coordinate of the second position.

        \param[in] y2
        The y-coordinate of the second position.

        \return
        The Euclidean distance between the two positions.

        */
        /**************************************************************************/
        double distance(int x1, int y1, int x2, int y2);

        std::pair<float, float> getClosestPair(float startPosX, float startPosY, const std::vector<std::pair<float, float>>& towerPositions);

        int numRows = 0;
        int numCols = 0;
        int startX = 0;
        int startY = 0;
        int goalX = 0;
        int goalY = 0;

        bool initialized; // A flag to check if the pathfinder has been initialized
        bool isWalking;
    };
}


#endif


