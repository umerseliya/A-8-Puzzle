//Alex Hakimzadeh
#ifndef HEURISTIC5_H
#define HEURISTIC5_H

#include <vector>
#include <cmath>
using namespace std;
#include "constants.h"

const int WEIGHTS[3][3] = {
    {1, 2, 1}, // Weights for the first row
    {2, 3, 2}, // Weights for the second row (center is more important)
    {1, 2, 1}  // Weights for the third row
};

int heuristic5(const vector<vector<int>>& current) {
    int cost = 0;

    // Loop through the current state to compute the weighted Manhattan distance
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (current[i][j] != 0) { // Ignore the empty tile
                int value = current[i][j] - 1; // Convert tile number to zero-based index
                int goalX = value / 3;         // Row of the goal position
                int goalY = value % 3;         // Column of the goal position

                // Compute Manhattan distance and apply the weight
                int manhattanDist = abs(i - goalX) + abs(j - goalY);
                cost += WEIGHTS[i][j] * manhattanDist;
            }
        }
    }

    return cost;
}

#endif // HEURISTIC5_H