#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

struct Node{
    bool isCop;
    bool isRobber;
    int x;
    int y;

    Node() {
        isCop = false;
        isRobber = false;
    }

    Node(int x, int y) {
        this->x = x;
        this->y = y;
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
        return x;
    }
    int getY() {
        return y;
    }
    void print() {
        if (isCop) {
            cout << " C ";
        } else if (isRobber) {
            cout << " R ";
        } else {
            cout << " 0 ";
        }
    }
};