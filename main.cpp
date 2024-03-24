#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include "Node.cpp"
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
    int copNum;
    int robberSpeed;
    int gridSize;
    // simType is either 't' for turn-based cop control or 'c' for continuous 
    char simType; 
    int moves = 0;

    // Read the input
    cout << "Enter the dimensions of the square grid: ";
    cin >> gridSize;
    cout << "Enter the number of cops: ";
    cin >> copNum;
    cout << "Enter the speed of the robber: ";
    cin >> robberSpeed;
    cout << "Enter the simulation type (t for turn-based, c for continuous): ";
    cin >> simType;

    // Create the grid
    Node** grid = new Node*[gridSize];
    for (int i = 0; i < gridSize; i++) {
        grid[i] = new Node[gridSize];
    }

    // Initialize the grid
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            grid[i][j] = Node();
        }
    }

    // Place the cops
    for (int i = 0; i < copNum; i++) {
        int x, y;
        cout << "Enter the coordinates of cop " << i + 1 << ": ";
        cin >> x >> y;
        grid[x][y].setCop();
    }

    // Place the robber
    int x, y;
    cout << "Enter the coordinates of the robber: ";
    cin >> x >> y;
    grid[x][y].setRobber();

    // Print the grid
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            grid[i][j].print();
        }
        cout << endl;
    }


    return 0;
}