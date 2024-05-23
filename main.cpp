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
    
    cout << endl;
    grid.print();
    cout << endl;

    bool tempFlag = true;
    char selection;
    char directional;
    char var = ' ';
    int direction;
    do {
        if (simType == 't'){
            cout << "m. Manual Movement" << endl;
            cout << "r. Control the robber" << endl;
            cout << "c. Control the cops" << endl;
            cout << "a. Automatic Movement" << endl;
            cout << "q. Quit" << endl;
            cout << endl;
            cin >> selection;
            cout << endl;

            switch(selection){
                case 'm': 

                    while (directional != 'q') {                   
                        //Cops move first
                        vector<char> copDirections;
                        do {
                            copDirections.clear();
                            for (int i = 0; i < copNum; ++i) {
                                cout << "What direction do you want cop " << i + 1 << " to move? (wasd, e to skip)" << endl;
                                cin >> directional;
                                copDirections.push_back(directional);
                            }
                        } while (!grid.CopFriendlyMove(copDirections));

                        //Print grid
                        grid.print();
                        cout << endl;

                        //Robber then moves 2 times
                        for (int i = 0; i < robberSpeed - 1; ++i) {
                            cout << "Enter robber move " << i + 1 << " (wasd, e to skip): " << endl;
                            cin >> directional;
                            cout << endl;
                            while (!grid.RobberFriendlyMove(directional)) {
                                cout << "Invalid move. Please enter a valid move." << endl;
                                cin >> directional;
                            }
                            grid.print();
                            cout << endl;
                        }
                        cout << "Enter robber last move " << " (wasd, e to skip, q to quit): " << endl;
                        cin >> directional;
                        cout << endl;
                        while (!grid.RobberFriendlyMove(directional)) {
                            cout << "Invalid move. Please enter a valid move." << endl;
                            cin >> directional;
                        }
                        grid.print();
                        cout << endl;
                    }

                    break;

                case 'r': 
                    //robber move
                    cout << "Enter robber move (wasd, e to skip): " << endl;
                    cin >> directional;
                    grid.RobberFriendlyMove(directional);
                    // call cop movement function

                    // print grid
                    grid.print();

                    break;
                case 'c':
                    //Cops move first
                    while (var != 'q') {
                        vector<char> copDirections;
                        for (int i = 0; i < copNum; ++i) {
                            cout << "What direction do you want cop " << i + 1 << " to move? (wasd, e to skip)" << endl;
                            cin >> directional;
                            copDirections.push_back(directional);
                        }
                        grid.CopFriendlyMove(copDirections);

                        //Print grid
                        grid.print();
                        cout << endl;

                         //Robber then moves 2 times
                        for (int i = 0; i < robberSpeed; ++i) {
                            direction = grid.huntersAlg();
                            cout << "The robber will move " << (direction == 1 ? "north" : direction == 2 ? "east" : direction == 3 ? "south" : "west");
                            directional = (direction == 1 ? 'w' : direction == 2 ? 'd' : direction == 3 ? 's' : 'a');
                            grid.RobberFriendlyMove(directional);
                            grid.print();
                            cout << endl;
                        }
                        
                        cout << "Press 'q' to exit, press any other key to continue." << endl;
                        cin >> var;
                    }
                    break;
                case 'a':  
                    //call robber movement function
                    cout << "What direction do you want the robber to move in? (wasd)" << endl;
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

    } while (grid.getMoves() <= maxMoves && tempFlag);

    return 0;
}