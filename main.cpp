#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include "Grid.cpp"
using namespace std;


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