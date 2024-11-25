#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <chrono>
#include <sstream>
#include "heuristic1.h"
#include "heuristic2.h"
#include "heuristic3.h"
#include "heuristic4.h"
#include "heuristic5.h"
#include "constants.h"

using namespace std;

// Structure to keep track of various metrics during the search
struct SearchMetrics {
    double executionTime = 0.0;     // Time taken to find the solution
    int nodesGenerated = 0;          // Total number of nodes generated
    int nodesExpanded = 0;           // Total number of nodes expanded
    int depth = 0;                   // Depth of the solution
    double branchingFactor = 0.0;    // Effective branching factor
    string path = "";                // Path taken to reach the goal
};

// Structure representing each state of the 8-puzzle
struct PuzzleState {
    vector<vector<int>> board;  // Current configuration of the puzzle
    int g;                      // Cost from the start node
    int h;                      // Heuristic value
    int x, y;                   // Position of the blank tile (0)
    string path;                // Path taken to reach this state

    // Constructor to initialize the puzzle state
    PuzzleState(vector<vector<int>> b, int g_val, int h_val, int x_pos, int y_pos, string p)
        : board(b), g(g_val), h(h_val), x(x_pos), y(y_pos), path(p) {}

    // Function to calculate f(n) = g(n) + h(n)
    int f() const {
        return g + h;
    }

    // Overloading the less-than operator for priority queue
    bool operator<(const PuzzleState& other) const {
        return f() > other.f(); // Min-heap based on f(n)
    }
};

// Define the goal state of the puzzle
const vector<vector<int>> goal = {
    {1, 2, 3},
    {8, 0, 4},
    {7, 6, 5}
};

// Arrays to represent movement directions: Left, Right, Up, Down
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
const string moves = "LRUD"; // Corresponding move characters

// Function to check if the current state is the goal state
bool isGoal(const vector<vector<int>>& state) {
    return state == goal;
}

// Function to print the current state of the board
void printBoard(const vector<vector<int>>& board) {
    for (const auto& row : board) {
        for (int cell : row) {
            if (cell == 0)
                cout << "   "; // Print blank for the empty tile
            else
                cout << " " << cell << " ";
        }
        cout << endl;
    }
}

// Function to convert the board state to a string for easy comparison
string boardToString(const vector<vector<int>>& board) {
    stringstream ss;
    for (const auto& row : board) {
        for (int cell : row) {
            ss << cell << ",";
        }
    }
    return ss.str();
}

// Function to generate all possible children (next states) from the current state
vector<PuzzleState> generateChildren(const PuzzleState& current, int (*heuristic)(const vector<vector<int>>&)) {
    vector<PuzzleState> children;

    // Iterate through all possible moves
    for (int i = 0; i < 4; i++) {
        int nx = current.x + dx[i];
        int ny = current.y + dy[i];

        // Check if the new position is within the board boundaries
        if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {
            vector<vector<int>> newBoard = current.board;
            swap(newBoard[current.x][current.y], newBoard[nx][ny]); // Move the blank tile

            int newH = heuristic(newBoard); // Calculate the heuristic for the new state
            // Create a new child state with updated parameters
            PuzzleState child(newBoard, current.g + 1, newH, nx, ny, current.path + moves[i]);
            children.push_back(child);
        }
    }
    return children;
}

// Function implementing the A* search algorithm
bool aStarSearch(const vector<vector<int>>& initial, int (*heuristic)(const vector<vector<int>>&), SearchMetrics& metrics) {
    auto start = chrono::high_resolution_clock::now(); // Start the timer

    int blank_x, blank_y;
    bool found = false;
    // Find the position of the blank tile (0) in the initial state
    for(int i = 0; i < 3 && !found; ++i) {
        for(int j = 0; j < 3 && !found; ++j) {
            if(initial[i][j] == 0) {
                blank_x = i;
                blank_y = j;
                found = true;
            }
        }
    }

    int root_h = heuristic(initial); // Calculate heuristic for the root node
    PuzzleState root(initial, 0, root_h, blank_x, blank_y, ""); // Create the root state

    priority_queue<PuzzleState> open; // Priority queue for open states
    open.push(root);
    unordered_set<string> open_set;    // To keep track of states in the open list
    open_set.insert(boardToString(initial));

    unordered_set<string> closed_set;  // To keep track of states already evaluated

    metrics.nodesGenerated = 1; // Initialize nodes generated with the root node
    metrics.nodesExpanded = 0;  // Initialize nodes expanded

    // Main loop of the A* search
    while(!open.empty()) {
        PuzzleState current = open.top(); // Get the state with the lowest f(n)
        open.pop();
        open_set.erase(boardToString(current.board)); // Remove it from the open set

        metrics.nodesExpanded++; // Increment nodes expanded

        // Check if the current state is the goal
        if(isGoal(current.board)) {
            auto end = chrono::high_resolution_clock::now(); // Stop the timer
            chrono::duration<double> duration = end - start;
            metrics.executionTime = duration.count(); // Record execution time
            metrics.depth = current.g;                // Record depth of solution
            metrics.path = current.path;              // Record the path taken

            // Calculate the effective branching factor
            if(metrics.nodesExpanded != 0)
                metrics.branchingFactor = static_cast<double>(metrics.nodesGenerated) / metrics.nodesExpanded;
            else
                metrics.branchingFactor = 0.0;

            return true; // Solution found
        }

        closed_set.insert(boardToString(current.board)); // Add current state to closed set

        // Generate all possible children from the current state
        vector<PuzzleState> children = generateChildren(current, heuristic);

        // Iterate through each child
        for(auto &child : children) {
            string child_str = boardToString(child.board);

            // Skip the child if it's already in the closed set
            if(closed_set.find(child_str) != closed_set.end())
                continue;

            // Skip the child if it's already in the open set
            if(open_set.find(child_str) != open_set.end())
                continue;

            open.push(child);           // Add the child to the open priority queue
            open_set.insert(child_str); // Add the child to the open set
            metrics.nodesGenerated++;    // Increment nodes generated
        }
    }

    auto end = chrono::high_resolution_clock::now(); // Stop the timer if no solution
    chrono::duration<double> duration = end - start;
    metrics.executionTime = duration.count(); // Record execution time

    // Calculate the effective branching factor
    if(metrics.nodesExpanded != 0)
        metrics.branchingFactor = static_cast<double>(metrics.nodesGenerated) / metrics.nodesExpanded;
    else
        metrics.branchingFactor = 0.0;

    return false; // No solution found
}

// Function to print the search results in a readable format
void printResults(const string& heuristicName, const SearchMetrics& metrics, const string& path, int cost, const vector<vector<int>>& finalState) {
    cout << "=======================================================" << endl;
    cout << "Heuristic: " << heuristicName << endl;
    cout << "-------------------------------------------------------" << endl;
    cout << "Solution Found!" << endl;
    cout << "Path to Goal: " << path << endl;
    cout << "Solution Cost (Depth): " << cost << endl;
    cout << "Execution Time: " << metrics.executionTime << " seconds" << endl;
    cout << "Nodes Generated: " << metrics.nodesGenerated << endl;
    cout << "Nodes Expanded: " << metrics.nodesExpanded << endl;
    cout << "Effective Branching Factor: " << metrics.branchingFactor << endl;
    cout << "-------------------------------------------------------" << endl;
    cout << "Final State:" << endl;
    printBoard(finalState); // Display the final state of the puzzle
    cout << "=======================================================" << endl;
}

// Main function to run the A* search with different heuristics and initial states
int main() {
    // Define two initial states for the puzzle
    vector<vector<int>> initialState1 = {
        {2, 8, 3},
        {1, 6, 4},
        {0, 7, 5}
    };
    vector<vector<int>> initialState2 = {
        {2, 1, 6},
        {4, 0, 8},
        {7, 5, 3}
    };

    // List of heuristics to use, each with a name and corresponding function
    vector<pair<string, int (*)(const vector<vector<int>>&)> > heuristics = {
        {"Heuristic 1 (Manhattan Distance)", heuristic1},
        {"Heuristic 2 (Misplaced Tiles)", heuristic2},
        {"Heuristic 3 (Umer Seliya - Pattern Database)", heuristic3},
        {"Heuristic 4 (Samuel Poulis - Linear Conflict)", heuristic4},
        {"Heuristic 5 (Alex Hakimzadeh - Weighted Manhattan)", heuristic5}
    };

    // List of initial states to test
    vector<pair<string, vector<vector<int>>>> initialStates = {
        {"Initial State #1", initialState1},
        {"Initial State #2", initialState2}
    };

    SearchMetrics metrics; // Create a SearchMetrics object to store results

    // Loop through each heuristic
    for (const auto& heuristic : heuristics) {
        // Loop through each initial state
        for (const auto& initialState : initialStates) {
            cout << "\nRunning " << initialState.first << "\n";
            // Perform A* search with the current heuristic and initial state
            if (aStarSearch(initialState.second, heuristic.second, metrics)) {
                // If solution is found, print the results
                printResults(heuristic.first, metrics, metrics.path, metrics.depth, goal);
            } else {
                // If no solution is found, display a message
                cout << "No solution found with " << heuristic.first << " on " << initialState.first << "." << endl;
            }
        }
    }

    cout << "\nPress Enter to exit...";
    cin.get(); // Wait for user input before closing
    return 0;
}
