#include "pch.h"
#include "pathfinding.h"

const int numRows = 720; // Number of rows
const int numCols = 1280; // Number of columns

// Function to check if a cell is within the bounds of the grid
bool Pathfinding::isValid(int x, int y) {
    // Check if x and y are within the grid's bounds
    bool isXWithinBounds = x >= 0 && x < numRows;
    bool isYWithinBounds = y >= 0 && y < numCols;

    // The cell is valid if both x and y are within bounds
    return isXWithinBounds && isYWithinBounds;
}

// Function to calculate the Euclidean distance between two points
double Pathfinding::distance(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int dxSquared = dx * dx;
    int dySquared = dy * dy;

    return std::sqrt(dxSquared + dySquared);
}

Pathfinding::Pathfinding(int _numRows, int _numCols) {
    numRows = _numRows;
    numCols = _numCols;
    startX = 0;
    startY = 0;
    goalX = 0;
    goalY = 0;
}

Pathfinding::Node::Node(int _x, int _y, double _cost) {
    x = _x;
    y = _y;
    cost = _cost;
}

bool Pathfinding::Node::operator>(const Node& other) const {
    return cost > other.cost;
}

void Pathfinding::setStart(int x, int y) {
    startX = x;
    startY = y;
}

void Pathfinding::setGoal(int x, int y) {
    goalX = x;
    goalY = y;
}

// Dijkstra's algorithm to find the shortest path
std::vector<std::pair<int, int>> Pathfinding::findShortestPath() {
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

//#include "pathfinding.h"
//#include <climits>
//#include <iostream>
//Pathfinding::Pathfinding(std::vector<std::vector<int>> map, int width, int height)
//    : map(map), width(width), height(height) {}
//
//std::pair<int, int> Pathfinding::minDistance(std::vector<std::vector<int>>& dist, std::vector<std::vector<bool>>& sptSet) {
//    int min = INT_MAX;
//    std::pair<int, int> minIndex = std::make_pair(-1, -1);
//
//    for (int x = 0; x < width; x++) {
//        for (int y = 0; y < height; y++) {
//            if (!sptSet[x][y] && dist[x][y] <= min) {
//                min = dist[x][y];
//                minIndex = std::make_pair(x, y);
//            }
//        }
//    }
//
//    return minIndex;
//}
//
//std::vector<std::pair<int, int>> Pathfinding::reconstructPath(std::vector<std::vector<int>>& parent, int srcX, int srcY, int targetX, int targetY) {
//    std::vector<std::pair<int, int>> path;
//    std::pair<int, int> current = std::make_pair(targetX, targetY);
//
//    while (current.first != srcX || current.second != srcY) {
//        path.insert(path.begin(), current);
//        current = std::make_pair(parent[current.first][current.second] / height, parent[current.first][current.second] % height);
//    }
//
//    path.insert(path.begin(), std::make_pair(srcX, srcY));
//    return path;
//}
//
//bool Pathfinding::isValid(int x, int y) {
//    return x >= 0 && x < width&& y >= 0 && y < height&& map[x][y] == 1;
//}
//
//std::vector<std::pair<int, int>> Pathfinding::findPath(int srcX, int srcY, int targetX, int targetY) {
//    std::vector<std::vector<int>> dist(width, std::vector<int>(height, INT_MAX));
//    std::vector<std::vector<bool>> sptSet(width, std::vector<bool>(height, false));
//    std::vector<std::vector<int>> parent(width, std::vector<int>(height, -1));
//
//    dist[srcX][srcY] = 0;
//
//    for (int count = 0; count < width * height - 1; count++) {
//        std::pair<int, int> u = minDistance(dist, sptSet);
//        sptSet[u.first][u.second] = true;
//
//        int dx[] = { -1, 1, 0, 0 };
//        int dy[] = { 0, 0, -1, 1 };
//
//        for (int i = 0; i < 4; i++) {
//            int x = u.first + dx[i];
//            int y = u.second + dy[i];
//
//            if (isValid(x, y) && !sptSet[x][y] && dist[u.first][u.second] != INT_MAX && dist[u.first][u.second] + 1 < dist[x][y]) {
//                dist[x][y] = dist[u.first][u.second] + 1;
//                parent[x][y] = u.first * height + u.second;
//            }
//        }
//    }
//
//    return reconstructPath(parent, srcX, srcY, targetX, targetY);
//}
