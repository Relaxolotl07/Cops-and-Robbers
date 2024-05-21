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
    // cout << "Enter the speed of the robber: ";
    // cin >> robberSpeed;
    robberSpeed = 2;
    cout << "Enter the simulation type (t for turn-based, c for continuous): ";
    cin >> simType;
    cout << "Enter the maximum number of moves: ";
    cin >> maxMoves;

    Grid grid(gridSize, copNum, robberSpeed, simType, maxMoves);
    
    grid.print();

    bool tempFlag = true;
    char selection;
    do {
        if (simType == 't'){    
            //switch case in here
            cout << "1. 2. 3. 4."
            cin >> selection;
            switch(selection){
                case 1: //up
                    //code for robber moving
                    //robber is placed
                    //coordinates are set from grid print
                    // so update y coordinate by +2 
                    break;
                case 2: //down
                    //code
                    break;
                case 3:  //left
                    //code
                    break;
                case 4:  //right
                    //code
                    break;
                default:
                    //code
                    break;
            }

        }
        else if (simType == 'c') {
            // do later
        }
    }
    while (true);
    return 0;
}