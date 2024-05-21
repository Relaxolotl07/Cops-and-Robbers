#include "Grid.h"

using namespace std;

class Grid {
    private:
        int copNum;
        int robberSpeed;
        int gridSize;
        // simType is either 't' for turn-based cop control or 'c' for continuous 
        char simType; 
        int moves = 0;
        int maxMoves;
        vector<int> pastMoves;
        

        Node** grid;
        Node* robber;
        Node* cops; // array of cops

    public:
        Grid(int gridSize, int copNum, int robberSpeed, char simType, int maxMoves) {
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
                int x, y;
                cout << "Enter the coordinates of cop " << i + 1 << ": ";
                cin >> x >> y;
                grid[--x][--y].setCop();

                for (int i = 0; i < copNum; i++) {
                    cops[i] = grid[x][y];
                }
            }

        
            // Place the robber
            int x, y;
            cout << "Enter the coordinates of the robber: ";
            cin >> x >> y;
            grid[--x][--y].setRobber();

            robber = &grid[x][y]; 

            cout << "Grid initialized" << endl;
        }

        void print() {
            for (int i = 0; i < gridSize; i++) {
                for (int j = 0; j < gridSize; j++) {
                    grid[i][j].print();
                }
                cout << endl;
            }
        }

        void move(int x, int y, int newX, int newY) {
            if (checkMovement(x, y, newX, newY)) {
                if (grid[x][y].hasCop()) {
                    grid[newX][newY].setCop();
                    grid[x][y].removeCop();
                    
                    for (int i = 0; i < copNum; i++) {
                        if (&cops[i] == &grid[x][y]) {
                            cops[i] = grid[newX][newY];
                        }
                    }
                } else if (grid[x][y].hasRobber()) {
                    grid[newX][newY].setRobber();
                    grid[x][y].removeRobber();

                    robber = &grid[newX][newY];
                }
            }
        }

        bool checkMovement(int x, int y, int newX, int newY) {
            //check if the new position is within the grid
            if (newX < 0 || newX >= gridSize || newY < 0 || newY >= gridSize) {
                return false;
            }
            //check if the movement is adjacent
            if (abs(newX - x) > 1 || abs(newY - y) > 1) {
                return false;
            }
            //check if the new position is empty
            if (!grid[newX][newY].isEmpty()) {
                return false;
            }

            return true;
        }


        // Calculate the best direction for the robber to move, 1 = north, 2 = east, 3 = south, 4 = west
        int huntersAlg() {
            // Call recursive function:
            
            // north
            int north = calculateBestDirection(robber->x, robber->y, robber->x, robber->y - 1, 0); 
            // east
            int east = calculateBestDirection(robber->x, robber->y, robber->x + 1, robber->y, 0);
            // south
            int south = calculateBestDirection(robber->x, robber->y, robber->x, robber->y + 1, 0);
            // west
            int west = calculateBestDirection(robber->x, robber->y, robber->x - 1, robber->y, 0);

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

        int calculateBestDirection(int x, int y, int newX, int newY, int time) {
            //base case: if the robber is caught
            if (grid[newX][newY].hasCop()) { // replace .hasCop with whatever implementation used later
                return time;
            }

            //check if intersect with cop ROC (make function for separate gridstate using COP ROCs)
            //code



            //optimization theory: run each iteration by timestep (to conserve cop ROC)
            //use pattern searching with last e steps to predict next step and find a robberWin
        }

};  