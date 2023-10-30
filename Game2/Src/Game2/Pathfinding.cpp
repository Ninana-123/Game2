#include "pch.h"
#include "pathfinding.h"
#include <climits>
#include <iostream>

Pathfinding::Pathfinding(std::vector<std::vector<int>> map, int width, int height)
    : map(map), width(width), height(height) {}

std::pair<int, int> Pathfinding::minDistance(std::vector<std::vector<int>>& dist, std::vector<std::vector<bool>>& sptSet) {
    int min = INT_MAX;
    std::pair<int, int> minIndex = std::make_pair(-1, -1);

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (!sptSet[x][y] && dist[x][y] <= min) {
                min = dist[x][y];
                minIndex = std::make_pair(x, y);
            }
        }
    }

    return minIndex;
}

std::vector<std::pair<int, int>> Pathfinding::reconstructPath(std::vector<std::vector<int>>& parent, int srcX, int srcY, int targetX, int targetY) {
    std::vector<std::pair<int, int>> path;
    std::pair<int, int> current = std::make_pair(targetX, targetY);

    while (current.first != srcX || current.second != srcY) {
        path.insert(path.begin(), current);
        current = std::make_pair(parent[current.first][current.second] / height, parent[current.first][current.second] % height);
    }

    path.insert(path.begin(), std::make_pair(srcX, srcY));
    return path;
}

bool Pathfinding::isValid(int x, int y) {
    return x >= 0 && x < width&& y >= 0 && y < height&& map[x][y] == 1;
}

std::vector<std::pair<int, int>> Pathfinding::findPath(int srcX, int srcY, int targetX, int targetY) {
    std::vector<std::vector<int>> dist(width, std::vector<int>(height, INT_MAX));
    std::vector<std::vector<bool>> sptSet(width, std::vector<bool>(height, false));
    std::vector<std::vector<int>> parent(width, std::vector<int>(height, -1));

    dist[srcX][srcY] = 0;

    for (int count = 0; count < width * height - 1; count++) {
        std::pair<int, int> u = minDistance(dist, sptSet);
        sptSet[u.first][u.second] = true;

        int dx[] = { -1, 1, 0, 0 };
        int dy[] = { 0, 0, -1, 1 };

        for (int i = 0; i < 4; i++) {
            int x = u.first + dx[i];
            int y = u.second + dy[i];

            if (isValid(x, y) && !sptSet[x][y] && dist[u.first][u.second] != INT_MAX && dist[u.first][u.second] + 1 < dist[x][y]) {
                dist[x][y] = dist[u.first][u.second] + 1;
                parent[x][y] = u.first * height + u.second;
            }
        }
    }

    return reconstructPath(parent, srcX, srcY, targetX, targetY);
}