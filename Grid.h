#ifndef GRIDH
#define GRIDH

#include <algorithm>
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
        Grid(const Grid & parent);

        Grid(int gridSize, int copNum, int robberSpeed, char simType, int maxMoves);

        void insertGridPos();

        bool isSimilarPosition();

        void printPastGrids();

        //what is this function bro
        Grid search();
        
        void print();

        int getMoves();

        int getCopNum();

        int getRobberSpeed();

        int getGridSize();

        char getSimType();

        int getMaxMoves();

        bool RobberFriendlyMove(char direction);

        bool CopFriendlyMove(list<char> directions);

        bool move(int row, int col, int newX, int newY, bool isCop);

        bool checkMovement(int row, int col, int newX, int newY);


        // Calculate the best direction for the robber to move, 1 = north, 2 = east, 3 = south, 4 = west
        int huntersAlg();   

        int calculateBestDirection(int newCol, int newRow, int time);

        //bool robberWinCheck();

        set<Node*> growCopROC(int timeStep);

        char greedyDirectionAlg(); // converts the greedy algorithm vector to a direction.

        vector<double> greedyVectorizationAlg(); // uses the greedy algorithm to find the best direction to move in.


        //abel evasion alg

        vector<pair<int, int>> getPossibleMoves(int row, int col);

        double evaluatePosition(int row, int col);

        pair<char, char> abelEvasionMoves();

        int findRobberQuadrant();

        void reorderCops(); // for a given robber position

        list<char> findBezierCopMoves();

        char bezierCopMove(int copNumber);

        pair<double, double> calculateCopBezier(int copNumber);

        int factorial(int n) {return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;};
};  

#endif
