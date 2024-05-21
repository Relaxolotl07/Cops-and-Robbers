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
    char directional;
    char var = ' ';
    do {
        if (simType == 't'){    
            //switch case in here
            cout << "m. Manual Movement" << endl;
            cout << "r. Robber Control Movement" << endl;
            cout << "a. Automatic Movement" << endl;
            cout << "q. Quit" << endl;
            cin >> selection;
            switch(selection){
                case 'm': 

                    while (var != 'q')
                    {
                        //robber moves 2 times
                        for (int i = 0; i < robberSpeed; ++i) {
                            cout << "What direction do you want the robber to move in?" << endl;
                            cin >> directional;
                            grid.RobberFriendlyMove(directional);
                        }

                        //Print grid
                        grid.print();

                        //Cop move
                        vector<char> copDirections;
                        for (int i = 0; i < copNum; ++i) {
                            cout << "What direction do you want cop " << i + 1 << " to move?" << endl;
                            cin >> directional;
                            copDirections.push_back(directional);
                        }
                        grid.CopFriendlyMove(copDirections);

                        //Print grid
                        grid.print();

                        cout << "Exit (q), press any other key to continue." << endl;
                        cin >> var;
                    }

                    break;
                case 'r': 
                    //robber move
                    cout << "What direction do you want the robber to move in?" << endl;
                    cin >> directional;
                    grid.RobberFriendlyMove(directional);
                    // call cop movement function

                    // print grid
                    grid.print();


                    break;
                case 'a':  
                    //call robber movement function
                    cout << "What direction do you want the robber to move in?" << endl;
                    cin >> directional;
                    grid.RobberFriendlyMove(directional);
                    //call cop movement function

                    // print grid
                    grid.print();
                    
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
    } while (grid.getMoves() < maxMoves && tempFlag);

    return 0;
}