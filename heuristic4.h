// Samuel Poulis

#ifndef HEURISTIC4_H
#define HEURISTIC4_H

#include <vector>
#include <cmath>
#include <cstdlib>
using namespace std;
#include "constants.h"

// Heuristic 4: Manhattan Distance with Linear Conflict penalties
int heuristic4(const vector<vector<int>>& current) {
    int cost = 0;
    int linear_conflicts = 0;

    // Manhattan distance
    for (int i = 0; i < 3; i++) { // rows
        for (int j = 0; j < 3; j++) { // columns
            int tile = current[i][j];
            if (tile != 0) {
                int goal_i = (tile - 1) / 3;
                int goal_j = (tile - 1) % 3;
                cost += abs(i - goal_i) + abs(j - goal_j);
            }
        }
    }

    // Linear conflicts
    // Check rows for conflicts
    for (int row = 0; row < 3; row++) {
        vector<int> current_row(3);
        vector<int> goal_row(3);
        for (int col = 0; col < 3; col++) {
            current_row[col] = current[row][col];
            goal_row[col] = goal[row][col];
        }

        for (int i = 0; i < 3; i++) {
            int tile_i = current_row[i];
            if (tile_i != 0 && (tile_i - 1) / 3 == row) { // Tile is in its goal row
                for (int j = i + 1; j < 3; j++) {
                    int tile_j = current_row[j];
                    if (tile_j != 0 && (tile_j - 1) / 3 == row) { // Tile is in its goal row
                        if (tile_i > tile_j) {
                            linear_conflicts++;
                        }
                    }
                }
            }
        }
    }

    // Check columns for conflicts
    for (int col = 0; col < 3; col++) {
        vector<int> current_col(3);
        vector<int> goal_col(3);
        for (int row = 0; row < 3; row++) {
            current_col[row] = current[row][col];
            goal_col[row] = goal[row][col];
        }

        for (int i = 0; i < 3; i++) {
            int tile_i = current_col[i];
            if (tile_i != 0 && (tile_i - 1) % 3 == col) { // Tile is in its goal column
                for (int j = i + 1; j < 3; j++) {
                    int tile_j = current_col[j];
                    if (tile_j != 0 && (tile_j - 1) % 3 == col) { // Tile is in its goal column
                        if (tile_i > tile_j) {
                            linear_conflicts++;
                        }
                    }
                }
            }
        }
    }

    return cost + 2 * linear_conflicts;
}

#endif // HEURISTIC4_H