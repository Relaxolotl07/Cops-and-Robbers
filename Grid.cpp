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


};  