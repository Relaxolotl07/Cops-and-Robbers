#include "Grid.h"

using namespace std;

Grid::Grid(Grid* parent) {
    this->gridSize = parent->gridSize;
    this->copNum = parent->copNum;
    this->robberSpeed = parent->robberSpeed;

    // Create the grid

    grid = new Node*[gridSize];
    for (int i = 0; i < gridSize; i++) {
        grid[i] = new Node[gridSize];
    }

    // Initialize the grid
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            grid[i][j] = Node(j, i);
        }
    }

    cops = new Node*[copNum];
    // Place the cops
    for (int i = 0; i < copNum; i++) {
        int col, row;
        col = parent->cops[i]->getX();
        row = parent->cops[i]->getY();
        grid[col][row].setCop();

        cops[i] = &grid[row][col];
    }


    // Place the robber
    int col, row;
    col = parent->robber->getX();
    row = parent->robber->getY();
    grid[row][col].setRobber();

    robber = &grid[row][col]; 
}

Grid::Grid(int gridSize, int copNum, int robberSpeed, char simType, int maxMoves) {
    this->gridSize = gridSize;
    this->copNum = copNum;
    this->robberSpeed = robberSpeed;
    this->simType = simType;
    this->maxMoves = maxMoves;

    //Create the grid
    grid = new Node*[gridSize];
    for (int i = 0; i < gridSize; i++) {
        grid[i] = new Node[gridSize];
    }

    //Initialize the grid
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            grid[i][j] = Node(j, i);
        }
    }

    cops = new Node*[copNum];

    //Place the cops
    for (int i = 0; i < copNum; i++) {
        int col, row;
        cout << "Enter the coordinates of cop " << i + 1 << " (row col, top left is 1 1): ";
        cin >> row >> col;

        grid[--row][--col].setCop();

        cops[i] = &grid[row][col];
    }

    // Place the robber
    int col, row;
    cout << "Enter the coordinates of the robber (row col): ";
    cin >> row >> col;
    // cout << row << " " << col << endl; (testing)
    grid[--row][--col].setRobber();
    // cout << col << " " << row << endl; (testing)
    robber = &grid[row][col]; 

    pastPos = vector<list<Grid>>(gridSize * gridSize);

    cout << "Grid initialized: " << endl;
}

int Grid::pastPosHash() {
    int hash = 0;
    // Hash the robber's position
    hash = robber->col * gridSize + robber->row;
    
    // Hash each cop's position and combine it into the hash
    for (int i = 0; i < copNum; i++) {
        hash = (hash * 31 + (cops[i]->col * gridSize + cops[i]->row)) % (gridSize * gridSize);
    }
    return hash % (gridSize * gridSize);
}

bool Grid::isSimilarPosition() {
    int hash = pastPosHash();
    
    // Check if there's a list in the vector for the given hash
    if (hash < pastPos.size() && !pastPos[hash].empty()) {
        for (const auto& pastGrid : pastPos[hash]) {
            // Compare the positions of the robber and all cops
            if (robber->col == pastGrid.robber->col && robber->row == pastGrid.robber->row) {
                bool allCopsMatch = true;
                for (size_t i = 0; i < copNum; ++i) {
                    if (cops[i]->col != pastGrid.cops[i]->col || cops[i]->row != pastGrid.cops[i]->row) {
                        allCopsMatch = false;
                        break;
                    }
                }
                if (allCopsMatch) {
                    return true;
                }
            }
        }
    }
    return false;
}


void Grid::insertGridPos() {
    if (isSimilarPosition()) {
        cout << "Robber wins!" << endl;
        exit(0);
    }

    int hash = pastPosHash();
    if (hash >= pastPos.size()) {
        pastPos.resize(hash + 1);  // Ensure the vector is large enough
    }
    pastPos[hash].push_back(*this);  // Insert the current grid state into the pastPos vector
}

/*
(temp disabled)
bool Grid::robberWinCheck() {
    //hash search
    int hash = pastPosHash();

    for (auto& grid : pastPos[hash]) {
        if (grid.robber->col == robber->col && grid.robber->row == robber->row) {
            for (int i = 0; i < copNum; i++)
            return true;
        }
    }
    return false;
}

*/

int Grid::getMoves() {
    return moves;
}

void Grid::print() {
    int copCount = 1;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (grid[i][j].hasCop()) {
                for (int k = 0; k < copNum; k++) {
                    if (cops[k]->getX() == j && cops[k]->getY() == i) {
                        cout << "C" << k + 1;
                    }
                }        
            }
            else {
                grid[i][j].print();
                cout << " ";
            }
            cout << " ";
        }
        cout << endl;
    }
}

bool Grid::RobberFriendlyMove(char direction) {
    if (direction == 'w') {

        /*
        (testing)
        cout << "Robber moves north" << endl;
        cout << robber->col << " " << robber->row << endl;
        cout << robber->col << " " << robber -> row - 1 << endl;
        */

        return move(robber->col, robber->row, robber->col, robber->row - 1, false);
    } else if (direction == 'd') {
        return move(robber->col, robber->row, robber->col + 1, robber->row, false);
    } else if (direction == 's') {
        return move(robber->col, robber->row, robber->col, robber->row + 1, false);
    } else if (direction == 'a') {
        return move(robber->col, robber->row, robber->col - 1, robber->row, false);
    } else if (direction == 'e' ) {
        return move(robber->col, robber->row, robber->col, robber->row, false);
    }
    else {
        cout << "Invalid direction" << endl;
        return false;
    }
}

bool Grid::CopFriendlyMove(vector<char> directions) {
    for (int i = 0; i < copNum; i++) {
        if (directions[i] == 'w') {
            if (!checkMovement(cops[i]->getX(), cops[i]->getY(), cops[i]->getX(), cops[i]->getY() - 1)) {
                cout << "Cop " << i + 1 << " is out of bounds." << endl;
                return false;
            }
        } else if (directions[i] == 'd') {
            if (!checkMovement(cops[i]->getX(), cops[i]->getY(), cops[i]->getX() + 1, cops[i]->getY())) {
                cout << "Cop " << i + 1 << " is out of bounds." << endl;
                return false;
            }
        } else if (directions[i] == 's') {
            if (!checkMovement(cops[i]->getX(), cops[i]->getY(), cops[i]->getX(), cops[i]->getY() + 1)) {
                cout << "Cop " << i + 1 << " is out of bounds." << endl;
                return false;
            }
        } else if (directions[i] == 'a') {
            if (!checkMovement(cops[i]->getX(), cops[i]->getY(), cops[i]->getX() - 1, cops[i]->getY())) {
                cout << "Cop " << i + 1 << " is out of bounds." << endl;
                return false;
            }
        } else if (directions[i] != 'e' ) {
            cout << "Invalid direction" << endl;
            return false;
        }
    }
    for (int i = 0; i < copNum; i++) {
        if (directions[i] == 'w') {
            move(cops[i]->getX(), cops[i]->getY(), cops[i]->getX(), cops[i]->getY() - 1, true);
        } else if (directions[i] == 'd') {
            move(cops[i]->getX(), cops[i]->getY(), cops[i]->getX() + 1, cops[i]->getY(), true);
        } else if (directions[i] == 's') {
            move(cops[i]->getX(), cops[i]->getY(), cops[i]->getX(), cops[i]->getY() + 1, true);
        } else if (directions[i] == 'a') {
            move(cops[i]->getX(), cops[i]->getY(), cops[i]->getX() - 1, cops[i]->getY(), true);
        } else if (directions[i] == 'e' ) {
            move(cops[i]->getX(), cops[i]->getY(), cops[i]->getX(), cops[i]->getY(), true);
        }
    }
    return true;
}

bool Grid::move(int col, int row, int newCol, int newRow, bool isCop) {
    if (checkMovement(col, row, newCol, newRow)) {
        moves++;
        if (isCop) {
            
            for (int i = 0; i < copNum; i++) {
                if (cops[i] == &grid[row][col]) {
                    cops[i] = &grid[newRow][newCol];
                }
            }
            

            // ** fix the cops being able to move to the same spot and get moved together (*cops array edit)
            grid[row][col].removeCop();
            grid[newRow][newCol].setCop();
            
            //check if the cop wins
            if (grid[newRow][newCol].hasRobber()) {
                cout << "Cop wins!" << endl;
                exit(0);
            }

            return true;

        } else if (grid[row][col].hasRobber()) {
            grid[row][col].removeRobber();
            grid[newRow][newCol].setRobber();
            

            robber = &grid[newRow][newCol];
            /*
            if (moves % 5 == 4) {
                if (robberWinCheck()) {
                    cout << "Robber wins!" << endl;
                    exit(0);
                }
            }
            */

            insertGridPos();

            return true;
        }
    }
    return false;
}

bool Grid::checkMovement(int col, int row, int newX, int newY) {

    /*(testing purposes)
    cout << col << " " << row << " | " << newX << " " << newY << endl;\
    */

    //check if the new position is within the grid
    if (newX < 0 || newX >= gridSize || newY < 0 || newY >= gridSize) {
        cout << "Invalid move: out of bounds" << endl;
        return false;
    }
    //check if the movement is adjacent
    /*
    if (abs(newX - col) > 1 || abs(newY - row) > 1) {
        cout << "Invalid move: not adjacent" << endl;
        return false;
    }
    */

    // check if the new position is empty
    // if (!grid[newY][newX]) {
    //     cout << "Invalid move: position is not empty" << endl; // change later
    //     return false;
    // }

    return true;
}


    // Calculate the best direction for the robber to move, 1 = north, 2 = east, 3 = south, 4 = west
int Grid::huntersAlg() {
    // Call recursive function:
    
    // north
    int north = calculateBestDirection(robber->col, robber->row - 1, 0); 
    // east
    int east = calculateBestDirection(robber->col + 1, robber->row, 0);
    // south
    int south = calculateBestDirection(robber->col, robber->row + 1, 0);
    // west
    int west = calculateBestDirection(robber->col - 1, robber->row, 0);

    // return the best direction. 
    if (north > east && north > south && north > west) {
        return 1;
    } else if (east > north && east > south && east > west) {
        return 2;
    } else if (south > north && south > east && south > west) {
        return 3;
    } else {
        return 4;
    }
    return 0;
}


// ** OPTIMIZE THE SHIT OUT OF THIS FUNCTION **
int Grid::calculateBestDirection(int newCol, int newRow, int time) {

    set<Node*> copROC = growCopROC(time/robberSpeed); // truncates to lowest whole number

    //**TEST
    // Print grid
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (grid[i][j].hasCop()) {
                cout << "C ";
            } else if (grid[i][j].hasRobber()) {
                cout << "R ";
            } else if (copROC.find(&grid[i][j]) != copROC.end()){
                cout << "& ";
            } else if (i == newRow && j == newCol) {
                cout << time << " ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }

    // ** TEST
    // check if the new position is within the cop ROC // ** CHECK FOR TIMING: if this should be calculated after being added or before
    if (copROC.find(&grid[newRow][newCol]) != copROC.end()) {
        return time;
    }

    time++;
    int north, south, east, west = 0;
    // check for out of bounds for movements (nesw)
    if (newCol < 0 || newRow >= gridSize || newCol < 0 || newRow >= gridSize) {
        //north
        north = calculateBestDirection(newCol, newRow - 1, time);
        //east
        east = calculateBestDirection(newCol + 1, newRow, time);
        //south
        south = calculateBestDirection(newCol, newRow + 1, time);
        //west
        west = calculateBestDirection(newCol - 1, newRow, time);
    }


    // sum the nsew directions

    return north + east + south + west;
    //optimization theory: run each iteration by timestep (to conserve cop ROC)
    //use pattern searching with last e steps to predict next step and find a robberWin
}

// Grows the cop ROC. Not stored 
set<Node*> Grid::growCopROC(int timeStep) {
    set<Node*> copROC;
    for (int i = 0; i < copNum; i++) {
        copROC.insert(cops[i]);
    }
    
    //create temp cop roc to add adjacent vector porinters to
    // loop through the grid to find adjacent nodes to the cop ROC
    //repeat for timeStep
    for (int i = 0; i < timeStep; i++) {
        set<Node*> tempCopROC;
        for (auto& node : copROC) {
            //check if the node is within the grid
            if (node->col - 1 >= 0) {
                tempCopROC.insert(&grid[node->row][node->col - 1]);
            }
            if (node->col + 1 < gridSize) {
                tempCopROC.insert(&grid[node->row][node->col + 1]);
            }
            if (node->row - 1 >= 0) {
                tempCopROC.insert(&grid[node->row - 1][node->col]);
            }
            if (node->row + 1 < gridSize) {
                tempCopROC.insert(&grid[node->row + 1][node->col]);
            }
        }
        copROC = tempCopROC;
    }

    return copROC;
}