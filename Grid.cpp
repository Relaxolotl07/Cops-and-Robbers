#include "Grid.h"

using namespace std;

Grid::Grid(Grid* parent) {
    this->gridSize = parent->gridSize;
    this->copNum = parent->copNum;

    // Create the grid

    grid = new Node*[gridSize];
    for (int i = 0; i < gridSize; i++) {
        grid[i] = new Node[gridSize];
    }

    // Initialize the grid
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            grid[i][j] = Node(i, j);
        }
    }

    cops = new Node[copNum];
    // Place the cops
    for (int i = 0; i < copNum; i++) {
        int col, row;
        col = parent->cops[i].getX();
        row = parent->cops[i].getY();
        grid[col][row].setCop();

        for (int i = 0; i < copNum; i++) {
            cops[i] = grid[row][col];
        }
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

    // Create the grid
    grid = new Node*[gridSize];
    for (int i = 0; i < gridSize; i++) {
        grid[i] = new Node[gridSize];
    }

    // Initialize the grid
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            grid[i][j] = Node(i, j);
        }
    }

    cops = new Node[copNum];
    // Place the cops
    for (int i = 0; i < copNum; i++) {
        int col, row;
        cout << "Enter the coordinates of cop " << i + 1 << ": ";
        cin >> row >> col;
        grid[--row][--col].setCop();

        for (int i = 0; i < copNum; i++) {
            cops[i] = grid[row][col];
        }
    }


    // Place the robber
    int col, row;
    cout << "Enter the coordinates of the robber: ";
    cin >> col >> row;
    cout << row << " " << col << endl;
    grid[--row][--col].setRobber();
    cout << col << " " << row << endl;
    robber = &grid[row][col]; 

    pastPos = vector<list<Grid>>(gridSize * gridSize);

    cout << "Grid initialized" << endl;
}

int Grid::pastPosHash() {
    int hash = 0;
    hash = robber->col * gridSize + robber->row;
    return hash % (gridSize * gridSize);
}

void Grid::insertGridPos() {
    int hash = pastPosHash();

    Grid tempGrid(*this);   
    pastPos[hash].push_back(*this);
}


bool Grid::robberWinCheck() {
    //hash search
    int hash = pastPosHash();

    for (auto& grid : pastPos[hash]) {
        if (grid.robber->col == robber->col && grid.robber->row == robber->row) {
            return true;
        }
    }
    return false;
}

int Grid::getMoves() {
    return moves;
}


void Grid::print() {
    int copCount = 1;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (grid[i][j].hasCop()) {
                cout << " C" << copCount << " ";
                copCount++;
            }
            else
                grid[i][j].print();
        }
        cout << endl;
    }
}

void Grid::RobberFriendlyMove(char direction) {
    if (direction == 'w') {


        cout << "Robber moves north" << endl;
        cout << robber->col << " " << robber->row << endl;
        cout << robber->col << " " << robber -> row - 1 << endl;


        move(robber->col, robber->row, robber->col, robber->row - 1);
    } else if (direction == 'd') {
        move(robber->col, robber->row, robber->col + 1, robber->row);
    } else if (direction == 's') {
        move(robber->col, robber->row, robber->col, robber->row + 1);
    } else if (direction == 'a') {
        move(robber->col, robber->row, robber->col - 1, robber->row);
    } else if (direction == 'e' ) {
        move(robber->col, robber->row, robber->col, robber->row);
    }
    else {
        cout << "Invalid direction" << endl;
    }
}

void Grid::CopFriendlyMove(vector<char> directions) {
    for (int i = 0; i < copNum; i++) {
        if (directions[i] == 'w') {
            move(cops[i].getX(), cops[i].getY(), cops[i].getX(), cops[i].getY() - 1);
        } else if (directions[i] == 'd') {
            move(cops[i].getX(), cops[i].getY(), cops[i].getX() + 1, cops[i].getY());
        } else if (directions[i] == 's') {
            move(cops[i].getX(), cops[i].getY(), cops[i].getX(), cops[i].getY() + 1);
        } else if (directions[i] == 'a') {
            move(cops[i].getX(), cops[i].getY(), cops[i].getX() - 1, cops[i].getY());
        } else if (directions[i] == 'e' ) {
        move(cops[i].getX(), cops[i].getY(), cops[i].getX(), cops[i].getY());
        }
        else {
            cout << "Invalid direction" << endl;
        }
    }
}

void Grid::move(int col, int row, int newX, int newY) {
    if (checkMovement(col, row, newX, newY)) {
        if (grid[row][col].hasCop()) {
            grid[newY][newX].setCop();
            grid[row][col].removeCop();
            
            for (int i = 0; i < copNum; i++) {
                if (&cops[i] == &grid[row][col]) {
                    cops[i] = grid[newY][newX];
                }
            }

            //check if the cop wins

        } else if (grid[row][col].hasRobber()) {
            grid[newY][newX].setRobber();
            grid[row][col].removeRobber();

            robber = &grid[newY][newX];

            if (moves % 5 == 4) 
                if (robberWinCheck()) {
                    cout << "Robber wins!" << endl;
                    exit(0);
                }
        }
    }
    moves++;
}

bool Grid::checkMovement(int col, int row, int newX, int newY) {

    cout << col << " " << row << " | " << newX << " " << newY << endl;

    //check if the new position is within the grid
    if (newX < 0 || newX >= gridSize || newY < 0 || newY >= gridSize) {
        cout << "Invalid move: out of bounds" << endl;
        return false;
    }
    //check if the movement is adjacent
    if (abs(newX - col) > 1 || abs(newY - row) > 1) {
        cout << "Invalid move: not adjacent" << endl;
        return false;
    }
    // //check if the new position is empty
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
    int north = calculateBestDirection(robber->col, robber->row, robber->col, robber->row - 1, 0); 
    // east
    int east = calculateBestDirection(robber->col, robber->row, robber->col + 1, robber->row, 0);
    // south
    int south = calculateBestDirection(robber->col, robber->row, robber->col, robber->row + 1, 0);
    // west
    int west = calculateBestDirection(robber->col, robber->row, robber->col - 1, robber->row, 0);

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

int Grid::calculateBestDirection(int col, int row, int newX, int newY, int time) {
    //base case: if the robber is caught
    if (grid[newY][newX].hasCop()) { // replace .hasCop with whatever implementation used later
        return time;
    }

    //check if intersect with cop ROC (make function for separate gridstate using COP ROCs)
    //code


    return 0;
    //optimization theory: run each iteration by timestep (to conserve cop ROC)
    //use pattern searching with last e steps to predict next step and find a robberWin
}

