#include "Node.cpp"

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

        Node** grid;

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

        bool checkMovement(int x, int y, int newX, int newY) {
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

        int calculateBestDirection() {
            
        }


};  