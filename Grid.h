#ifndef GRIDH
#define GRIDH

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
        vector<list<Grid>> pastPos;

        

        Node** grid;
        Node* robber;
        Node* cops; // array of cops
        int pastPosHash();

    public:
        Grid(Grid* parent);

        Grid(int gridSize, int copNum, int robberSpeed, char simType, int maxMoves);

        void insertGridPos();

        Grid search();
        
        void print();

        int getMoves();

        void friendlyMove(char direction);

        void move(int x, int y, int newX, int newY);

        bool checkMovement(int x, int y, int newX, int newY);


        // Calculate the best direction for the robber to move, 1 = north, 2 = east, 3 = south, 4 = west
        int huntersAlg();

        int calculateBestDirection(int x, int y, int newX, int newY, int time);

        bool robberWinCheck();
};  

#endif
