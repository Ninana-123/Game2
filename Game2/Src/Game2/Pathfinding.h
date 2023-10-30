//#pragma once

#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <vector>

class Pathfinding {
public:
    // Constructor to initialize the map and its dimensions
    Pathfinding(std::vector<std::vector<int>> map, int width, int height);

    // Find a path from the source position to the target position
    std::vector<std::pair<int, int>> findPath(int srcX, int srcY, int targetX, int targetY);

private:
    std::vector<std::vector<int>> map;
    int width;
    int height;

    std::pair<int, int> minDistance(std::vector<std::vector<int>>& dist, std::vector<std::vector<bool>>& sptSet);
    std::vector<std::pair<int, int>> reconstructPath(std::vector<std::vector<int>>& parent, int srcX, int srcY, int targetX, int targetY);
    bool isValid(int x, int y);
};

#endif