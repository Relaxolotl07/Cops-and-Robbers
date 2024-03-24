#include <iostream>
using namespace std;

struct Node{

    bool isCop;
    bool isRobber;
    Node() {
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