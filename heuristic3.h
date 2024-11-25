//UMER SELIYA PATTERN DATABASE

#ifndef HEURISTIC3_H
#define HEURISTIC3_H

#include <vector>
#include <cmath>
#include <unordered_map>
#include <sstream>
#include "constants.h"

using namespace std;

// Extracts the positions of specific tiles and creates a pattern string
string extractPattern(const vector<vector<int>>& board, const vector<int>& patternTiles) {
    stringstream ss;
    for (const auto& tile : patternTiles) {
        bool found = false;
        for(int i = 0; i < board.size() && !found; ++i) {
            for(int j = 0; j < board[i].size() && !found; ++j) {
                if(board[i][j] == tile) {
                    ss << i << "," << j << ";";
                    found = true;
                }
            }
        }
        if(!found) {
            ss << "-1,-1;";
        }
    }
    return ss.str();
}

// Computes the heuristic value based on a pattern database
int heuristic3(const vector<vector<int>>& board) {
    // Define the subset of tiles to consider
    vector<int> patternTiles = {1, 2};

    // Predefined pattern database with minimal moves for specific patterns
    static unordered_map<string, int> patternDatabase = {
        {"0,0;0,1;", 0},
        {"0,1;0,0;", 2},
        {"0,0;-1,-1;", 1},
        {"-1,-1;0,1;", 1}
    };

    // Generate the current pattern string from the board
    string currentPattern = extractPattern(board, patternTiles);

    // Check if the current pattern exists in the database
    auto it = patternDatabase.find(currentPattern);
    if(it != patternDatabase.end()) {
        return it->second;
    }

    // If pattern not found, calculate fallback heuristic using Manhattan Distance
    int fallbackHeuristic = 0;
    for(const auto& tile : patternTiles) {
        for(int i = 0; i < board.size(); ++i) {
            for(int j = 0; j < board[i].size(); ++j) {
                if(board[i][j] == tile) {
                    int goal_i = -1, goal_j = -1;
                    // Find the goal position of the current tile
                    for(int gi = 0; gi < goal.size(); ++gi) {
                        for(int gj = 0; gj < goal[gi].size(); ++gj) {
                            if(goal[gi][gj] == tile) {
                                goal_i = gi;
                                goal_j = gj;
                                break;
                            }
                        }
                        if(goal_i != -1) break;
                    }
                    // Add the Manhattan Distance to the fallback heuristic
                    if(goal_i != -1) {
                        fallbackHeuristic += abs(i - goal_i) + abs(j - goal_j);
                    }
                }
            }
        }
    }
    return fallbackHeuristic;
}

#endif // HEURISTIC3_H
