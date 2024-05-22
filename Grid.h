#ifndef GRIDH
#define GRIDH

#include "Node.cpp"

using namespace std;

class Grid {
    private:
        int copNum;
        int robberSpeed;
        int gridSize;
        char simType; // simType is either 't' for turn-based cop control or 'c' for continuous 
        int moves = 0;
        int maxMoves;
        vector<list<Grid>> pastPos;

        

        Node** grid;
        Node* robber;
        Node** cops; // array of cops
        int pastPosHash();

    public:
        Grid(Grid* parent);

        Grid(int gridSize, int copNum, int robberSpeed, char simType, int maxMoves);

        void insertGridPos();

        Grid search();
        
        void print();

        int getMoves();

        bool RobberFriendlyMove(char direction);

        bool CopFriendlyMove(vector<char> directions);

        bool move(int row, int col, int newX, int newY, bool isCop);

        bool checkMovement(int row, int col, int newX, int newY);


        // Calculate the best direction for the robber to move, 1 = north, 2 = east, 3 = south, 4 = west
        int huntersAlg();

        int calculateBestDirection(int newCol, int newRow, int time);

        bool robberWinCheck();

        set<Node*> growCopROC(int timeStep);
};  

#endif
