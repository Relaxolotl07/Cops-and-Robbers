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
            cout << "m. Manual Movement" << endl;
            cout << "r. Robber Control Movement" << endl;
            cout << "a. Automatic Movement" << endl;
            cout << "q. Quit" << endl;
            cin >> selection;
            switch(selection){
                case 'm': //up
                    //code for robber moving
                    //robber is placed
                    //coordinates are set from grid print
                    // so update y coordinate by +2 
                    break;
                case 'r': //down
                    //code
                    break;
                case 'a':  //left
                    //code
                    break;
                case 'q':
                    tempFlag = false;
                    break;
                default:
                    cout << "Invalid selection" << endl;
                    break;
            }

        }
        else if (simType == 'c') {
            // do later
        }
    }
    while (grid.getMoves() < maxMoves && tempFlag);
    return 0;
}