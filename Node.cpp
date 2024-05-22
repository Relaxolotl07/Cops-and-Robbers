#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <list>
using namespace std;

struct Node{
    bool isCop;
    bool isRobber;
    int col;
    int row;

    Node() {
        isCop = false;
        isRobber = false;
    }

    Node(int x, int y) {
        this->col = x;
        this->row = y;
        isCop = false;
        isRobber = false;
    }
    
    void setCop() {
        isCop = true;
    }
    void setRobber() {
        isRobber = true;
    }
    void removeCop() {
        isCop = false;
    }
    void removeRobber() {
        isRobber = false;
    }
    bool hasCop() {
        return isCop;
    }
    bool hasRobber() {
        return isRobber;
    }
    bool isEmpty() {
        return !isCop && !isRobber;
    }
    bool copWin() {
        return isCop && isRobber;
    }
    int getX() {
        return col;
    }
    int getY() {
        return row;
    }
    void print() {
        if (isCop) {
            cout << "C";
        } else if (isRobber) {
            cout << "R";
        } else {
            cout << "0";
        }
    }
};