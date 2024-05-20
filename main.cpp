#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include "Grid.cpp"
using namespace std;

// Function to move the cops and the robber
void move(Node** grid, int x, int y, int newX, int newY) {
    if (grid[newX][newY].isEmpty()) {
        if (grid[x][y].hasCop()) {
            grid[newX][newY].setCop();
            grid[x][y].removeCop();
        } else if (grid[x][y].hasRobber()) {
            grid[newX][newY].setRobber();
            grid[x][y].removeRobber();
        }
    }
}
//test


// Function to check if the movement is valid
bool checkMovement(Node** grid, int x, int y, int newX, int newY) {
    int gridSize = sizeof(grid) / sizeof(grid[0]);
    //check if the new position is within the grid
    if (newX < 0 || newX >= gridSize || newY < 0 || newY >= gridSize) {
        return false;
    }
    //check if the movement is adjacent
    if (abs(newX - x) > 1 || abs(newY - y) > 1) {
        return false;
    }
    return true;
}

int main() {
    int gridSize, copNum, robberSpeed, maxMoves;
    char simType;
    // Read the input
    cout << "Enter the dimensions of the square grid: ";
    cin >> gridSize;
    cout << "Enter the number of cops: ";
    cin >> copNum;
    cout << "Enter the speed of the robber: ";
    cin >> robberSpeed;
    cout << "Enter the simulation type (t for turn-based, c for continuous): ";
    cin >> simType;
    cout << "Enter the maximum number of moves: ";
    cin >> maxMoves;

    Grid grid(gridSize, copNum, robberSpeed, simType, maxMoves);
    grid.print();

    // Run the simulation
    // do {
    //     if (simType == 't'){    
    //     }
    //     else if (simType == 'c') {
    //     }
    // }
    // while (!copWin && moves < maxMoves);
    return 0;
}