//#pragma once

#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

class Pathfinding {
public:
    Pathfinding(int numRows, int numCols);

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
};

#endif


//class Pathfinding {
//public:
//    // Constructor to initialize the map and its dimensions
//    Pathfinding(std::vector<std::vector<int>> map, int width, int height);
//
//    // Constructor for screen-based pathfinding
//    Pathfinding(int screenWidth, int screenHeight);
//
//    // Find a path from the source position to the target position
//    std::vector<std::pair<int, int>> findPath(int srcX, int srcY, int targetX, int targetY);
//
//private:
//    std::vector<std::vector<int>> map;
//    int width;
//    int height;
//    bool useBinaryMap;  // To determine whether to use binary map or screen dimensions
//    std::pair<int, int> minDistance(std::vector<std::vector<int>>& dist, std::vector<std::vector<bool>>& sptSet);
//    std::vector<std::pair<int, int>> reconstructPath(std::vector<std::vector<int>>& parent, int srcX, int srcY, int targetX, int targetY);
//    bool isValid(int x, int y);
//};

//#endif
