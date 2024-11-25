//MANHATTAN DISTANCE

#ifndef HEURISTIC1_H
#define HEURISTIC1_H

#include <vector>
#include <cmath>
#include "constants.h"
using namespace std;

int heuristic1(const vector<vector<int>>& current) {
    int cost = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (current[i][j] != 0) {
                int tile = current[i][j];
                int goalX = (tile - 1) / 3;
                int goalY = (tile - 1) % 3;
                cost += std::abs(i - goalX) + std::abs(j - goalY);
            }
        }
    }
    return cost;
}

#endif // HEURISTIC1_H
