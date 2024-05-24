#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include "Grid.cpp"
using namespace std;

Grid newGrid() {
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
    return grid;
}

int main() {
    Grid grid = newGrid();
    char simType = grid.getSimType();
    int copNum = grid.getCopNum();
    int robberSpeed = grid.getRobberSpeed();
    int maxMoves = grid.getMaxMoves();

    
    cout << endl;
    grid.print();
    cout << endl;

    char selection;
    char directional;
    char var = ' ';
    int direction;
    do {
        if (simType == 't'){
            // cops move (for each cop) // ** first cop should allow user to press q to quit
            cout << "What direction do you want cop 1 to move? (wasd, e to skip turn, f to automate moves, q to quit)" << endl;
            cin >> selection;
            if (selection == 'q') {
                break;
            }
            else if (selection == 'f') {
                // automatic cop movement
                list<char> copDirections = grid.findBezierCopMoves();
                grid.CopFriendlyMove(copDirections);
            }
            else {
                // manual cop movement
                list<char> copDirections;
                int i = 1;
                bool first = true;
                do {
                    copDirections.clear();

                    for (i; i < copNum; ++i) {
                        cout << "What direction do you want cop " << i + 1 << " to move? (wasd, e to skip turn)" << endl;
                        cin >> directional;
                        copDirections.push_back(directional);
                    }
                    i = 0;
                    if (first)
                        copDirections.push_front(selection);
                } while (!grid.CopFriendlyMove(copDirections));
            }

            //Print grid
            grid.print();
            cout << endl;

            // robber moves (for robberspeed)
            for (int i = 0; i < robberSpeed; ++i) {
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

        
        // ** OLD MAIN FUNCTION **
        //{
        //     cout << "m. Manual Movement" << endl;
        //     cout << "r. Control the robber" << endl;
        //     cout << "c. Control the cops" << endl;
        //     cout << "a. Automatic Movement" << endl;
        //     cout << "n. New Grid" << endl;
        //     cout << "p. Print Past Grids" << endl;
        //     cout << "q. Quit" << endl;
        //     cout << endl;
        //     cin >> selection;
        //     cout << endl;

        //     switch(selection){
        //         case 'm': 

        //             while (directional != 'q') {                   
        //                 //Cops move first
        //                 vector<char> copDirections;
        //                 do {
        //                     copDirections.clear();
        //                     for (int i = 0; i < copNum; ++i) {
        //                         cout << "What direction do you want cop " << i + 1 << " to move? (wasd, e to skip)" << endl;
        //                         cin >> directional;
        //                         copDirections.push_back(directional);
        //                     }
        //                 } while (!grid.CopFriendlyMove(copDirections));

        //                 //Print grid
        //                 grid.print();
        //                 cout << endl;

        //                 //Robber then moves 2 times
        //                 for (int i = 0; i < robberSpeed - 1; ++i) {
        //                     cout << "Enter robber move " << i + 1 << " (wasd, e to skip): " << endl;
        //                     cin >> directional;
        //                     cout << endl;
        //                     while (!grid.RobberFriendlyMove(directional)) {
        //                         cout << "Invalid move. Please enter a valid move." << endl;
        //                         cin >> directional;
        //                     }
        //                     grid.print();
        //                     cout << endl;
        //                 }
        //                 cout << "Enter robber last move " << " (wasd, e to skip, q to quit): " << endl;
        //                 cin >> directional;
        //                 cout << endl;
        //                 while (!grid.RobberFriendlyMove(directional)) {
        //                     cout << "Invalid move. Please enter a valid move." << endl;
        //                     cin >> directional;
        //                 }
        //                 grid.print();
        //                 cout << endl;
        //             }

        //             break;

        //         case 'r': 
        //             //robber move
        //             cout << "Enter robber move (wasd, e to skip): " << endl;
        //             cin >> directional;
        //             grid.RobberFriendlyMove(directional);
        //             // call cop movement function

        //             // print grid
        //             grid.print();

        //             break;
        //         case 'c':

        //             cout << "Enter the robber evasion strategy: " << endl;
        //             cout << "1. Greedy" << endl;
        //             cout << "2. Tree Brute Force" << endl;
        //             cout << "3. Distance Evasion" << endl;

        //             int strategy;
        //             cin >> strategy;
        //             //Cops move first
                    
        //             cout << endl;
        //             grid.print();
        //             cout << endl;
                    
        //             while (var != 'q') {
        //                 vector<char> copDirections;
        //                 for (int i = 0; i < copNum; ++i) {
        //                     cout << "What direction do you want cop " << i + 1 << " to move? (wasd, e to skip)" << endl;
        //                     cin >> directional;
        //                     copDirections.push_back(directional);
        //                 }
        //                 grid.CopFriendlyMove(copDirections);

        //                 //Print grid
        //                 cout << endl;
        //                 grid.print();
        //                 cout << endl;

        //                 if (strategy == 3) {
        //                     //Robber first move
        //                     directional = grid.abelEvasionMoves().first;
        //                     cout << "The robber will move " << (directional == 'w' ? "north" : directional == 'd' ? "east" : directional == 's' ? "south" : directional == 'a' ? "west" : "none") << endl;
        //                     grid.RobberFriendlyMove(directional);
        //                     //Robber second move
        //                     directional = grid.abelEvasionMoves().second;
        //                     cout << "The robber will move " << (directional == 'w' ? "north" : directional == 'd' ? "east" : directional == 's' ? "south" : directional == 'a' ? "west" : "none") << endl;
        //                     grid.RobberFriendlyMove(directional);

        //                     cout << endl;
        //                     grid.print();
        //                     cout << endl;
        //                 } else if (strategy == 2) {
        //                     //Robber then moves 2 times
        //                     for (int i = 0; i < robberSpeed; ++i) {
        //                         direction = grid.huntersAlg();
        //                         cout << "The robber will move " << (direction == 1 ? "north" : direction == 2 ? "east" : direction == 3 ? "south" : "west") << endl;
        //                         directional = (direction == 1 ? 'w' : direction == 2 ? 'd' : direction == 3 ? 's' : 'a');
        //                         grid.RobberFriendlyMove(directional);

        //                         cout << endl;
        //                         grid.print();
        //                         cout << endl;
        //                     }
        //                 } else if (strategy == 1) {
        //                     //Robber then moves 2 times
        //                     for (int i = 0; i < robberSpeed; ++i) {
        //                         directional = grid.greedyDirectionAlg();
        //                         cout << "The robber will move " << (directional == 'w' ? "north" : directional == 'd' ? "east" : directional == 's' ? "south" : "west") << endl;
        //                         grid.RobberFriendlyMove(directional);
        //                         grid.print();
        //                         cout << endl;
        //                     }
        //                 } else {
        //                     cout << "Invalid strategy. " << endl;
        //                     break;
        //                 }
                        
        //                 cout << "Press 'q' to exit, press any other key to continue." << endl;
        //                 cin >> var;
        //             }
        //             break;
        //         case 'a':  
        //             //call robber movement function
        //             cout << "What direction do you want the robber to move in? (wasd)" << endl;
        //             cin >> directional;
        //             grid.RobberFriendlyMove(directional);
        //             //call cop movement function

        //             // print grid
        //             grid.print();
                    
        //             break;
        //         case 'n':
        //             grid = newGrid();
        //             simType = grid.getSimType();
        //             copNum = grid.getCopNum();
        //             robberSpeed = grid.getRobberSpeed();
        //             maxMoves = grid.getMaxMoves();
        //             break;
        //         case 'p':
        //             grid.printPastGrids();
        //             break;
        //         case 'q':
        //             tempFlag = false;
        //             break;

        //         default:
        //             cout << "Invalid selection" << endl;
        //             break;
        //     }
        // }
        }

        else if (simType == 'c') {
            // do later
        }
    } while (grid.getMoves() <= maxMoves && selection != 'q');
    cout << "Game Terminated. Restart? (y/n)" << endl;
    char restart;
    cin >> restart;
    if (restart == 'y') {
        main();
    }

    return 0;
}