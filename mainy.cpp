#include "Node.cpp"
#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <limits>
using namespace std;

// Helper function to check if a move is valid and within grid bounds
bool isValidMove(int x, int y, int gridSize) {
    return (x >= 0 && x < gridSize) && (y >= 0 && y < gridSize);
}

// Function to print the current state of the grid
void printGrid(Node **grid, int gridSize) {
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            grid[i][j].print();
        }
        cout << endl;
    }
}

// Function to evaluate the distance to the nearest cop
double distanceToNearestCop(int x, int y, const vector<pair<int, int>>& copPositions) {
    double minDist = numeric_limits<double>::max();
    for (const auto& cop : copPositions) {
        double dist = hypot(x - cop.first, y - cop.second);
        minDist = min(minDist, dist);
    }
    return minDist;
}

// Function to predict the next positions of the cops
vector<pair<int, int>> predictCopMoves(int robberX, int robberY, const vector<pair<int, int>>& copPositions, int gridSize) {
    vector<pair<int, int>> newCopPositions = copPositions;
    int dir[5][2] = {{0, 0}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    for (auto& pos : newCopPositions) {
        int x = pos.first;
        int y = pos.second;

        int bestX = x, bestY = y;
        int minDist = abs(x - robberX) + abs(y - robberY);

        for (int i = 0; i < 5; i++) {
            int newX = x + dir[i][0];
            int newY = y + dir[i][1];
            if (isValidMove(newX, newY, gridSize)) {
                int dist = abs(newX - robberX) + abs(newY - robberY);
                if (dist < minDist) {
                    bestX = newX;
                    bestY = newY;
                    minDist = dist;
                }
            }
        }

        pos = make_pair(bestX, bestY);
    }

    return newCopPositions;
}

// Move function for the robber, trying to maximize distance from nearest cop after predicting their moves
void moveRobber(Node **grid, int &x, int &y, int gridSize, const vector<pair<int, int>>& copPositions) {
    int dir[5][2] = {{0, 0}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    for (int move = 0; move < 2; move++) {
        double maxDist = -1;
        int bestX = x, bestY = y;

        for (int i = 0; i < 5; i++) {
            int newX = x + dir[i][0];
            int newY = y + dir[i][1];
            if (isValidMove(newX, newY, gridSize) && grid[newX][newY].isEmpty()) {
                vector<pair<int, int>> newCopPositions = predictCopMoves(newX, newY, copPositions, gridSize);
                double dist = distanceToNearestCop(newX, newY, newCopPositions);
                if (dist > maxDist) {
                    maxDist = dist;
                    bestX = newX;
                    bestY = newY;
                }
            }
        }

        // Move the robber to the best position found
        if (bestX != x || bestY != y) {
            grid[x][y].removeRobber();
            grid[bestX][bestY].setRobber();
            x = bestX;
            y = bestY;
        }
    }
}

// Function to handle cop moves, seeking to surround or move closer to the robber
void moveCops(Node **grid, vector<pair<int, int>>& copPositions, int robberX, int robberY, int gridSize, bool &copWin) {
    int dir[5][2] = {{0, 0}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    for (auto& pos : copPositions) {
        int x = pos.first;
        int y = pos.second;

        int bestX = x, bestY = y;
        int minDist = abs(x - robberX) + abs(y - robberY);

        for (int i = 0; i < 5; i++) {
            int newX = x + dir[i][0];
            int newY = y + dir[i][1];
            if (isValidMove(newX, newY, gridSize) && grid[newX][newY].isEmpty()) {
                int dist = abs(newX - robberX) + abs(newY - robberY);
                if (dist < minDist) {
                    bestX = newX;
                    bestY = newY;
                    minDist = dist;
                }
            }
        }

        if (bestX != x || bestY != y) {
            grid[x][y].removeCop();
            grid[bestX][bestY].setCop();
            pos = make_pair(bestX, bestY);
        }

        // Check if the cop catches the robber after moving
        if (bestX == robberX && bestY == robberY) {
            copWin = true;
            return;
        }
    }

    // Check if any cop is adjacent to the robber
    for (auto& pos : copPositions) {
        int x = pos.first;
        int y = pos.second;
        if ((abs(x - robberX) == 1 && y == robberY) || (abs(y - robberY) == 1 && x == robberX)) {
            copWin = true;
            return;
        }
    }
}

int main() {
    int gridSize = 10, numCops = 2;
    cout << "Enter the dimensions of the square grid: ";
    cin >> gridSize;
    cout << "Enter the number of cops: ";
    cin >> numCops;

    Node **grid = new Node*[gridSize];
    for (int i = 0; i < gridSize; i++) {
        grid[i] = new Node[gridSize];
    }

    vector<pair<int, int>> copPositions;
    for (int i = 0; i < numCops; i++) {
        int copX, copY;
        cout << "Enter the coordinates of cop " << (i + 1) << ": ";
        cin >> copX >> copY;
        grid[copX][copY].setCop();
        copPositions.push_back({copX, copY});
    }

    int robX, robY;
    cout << "Enter the coordinates of the robber: ";
    cin >> robX >> robY;
    grid[robX][robY].setRobber();

    int maxMoves;
    cout << "Enter the maximum number of turns: ";
    cin >> maxMoves;

    bool copWin = false;
    int turn = 0;
    while (turn < maxMoves && !copWin) {
        cout << "Turn " << turn + 1 << ":" << endl;
        moveRobber(grid, robX, robY, gridSize, copPositions);
        moveCops(grid, copPositions, robX, robY, gridSize, copWin);

        if (copWin) {
            printGrid(grid, gridSize);
            cout << "Cops win!" << endl;
            break;
        }

        printGrid(grid, gridSize);
        turn++;
    }

    if (!copWin) {
        cout << "Robber escapes!" << endl;
    }

    for (int i = 0; i < gridSize; i++) {
        delete[] grid[i];
    }
    delete[] grid;

    return 0;
}
