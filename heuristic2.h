//MISPLACED TILES

#ifndef HEURISTIC2_H
#define HEURISTIC2_H

#include <vector>
#include "constants.h"
using namespace std;

int heuristic2(const vector<vector<int>>& board) {
    int misplaced = 0;
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            if (board[i][j] != 0 && board[i][j] != goal[i][j]) {
                misplaced++;
            }
        }
    }
    return misplaced;
}

#endif // HEURISTIC2_H
