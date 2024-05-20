#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <climits>
#include <cmath>

using namespace std;

// Structure to represent a player (cop or robber)
struct Player {
    string name;
    int x, y;
};

// Class to represent the game
class Game {
private:
    int numCops, numRobbers, gridSize, copNumMoves, robberNumMoves;
    vector<Player> cops, robbers;

public:
    Game(int nc, int nr, int gs, int cnm, int rnm) : numCops(nc), numRobbers(nr), gridSize(gs), copNumMoves(cnm), robberNumMoves(rnm) {}

    // Initialize players' positions based on user input
    void initializePlayers() {
        // Initialize cops' positions
        for (int i = 0; i < numCops; ++i) {
            int x, y;
            cout << "Enter starting position for cop " << i + 1 << " (x y): ";
            cin >> x >> y;
            x = max(0, min(gridSize, x));
            y = max(0, min(gridSize, y));
            cops.push_back({"Cop", x, y});
        }

        // Initialize robbers' positions
        for (int i = 0; i < numRobbers; ++i) {
            int x, y;
            cout << "Enter starting position for robber " << i + 1 << " (x y): ";
            cin >> x >> y;
            x = max(0, min(gridSize, x));
            y = max(0, min(gridSize, y));
            robbers.push_back({"Robber", x, y});
        }
    }

    // Check if a cop caught a robber
    bool isCaught(const Player& cop, const Player& robber) {
        return (cop.x == robber.x) && (cop.y == robber.y);
    }

    // Move players
// Move players
void movePlayers() {
    // Move cops
    for (auto& cop : cops) {
        // Calculate the direction towards the nearest robber, if any
        int dx = 0, dy = 0;
        int minDistance = INT_MAX;
        for (const auto& robber : robbers) {
            int distanceX = robber.x - cop.x;
            int distanceY = robber.y - cop.y;
            int absDistanceX = abs(distanceX);
            int absDistanceY = abs(distanceY);
            if (absDistanceX + absDistanceY < minDistance) {
                minDistance = absDistanceX + absDistanceY;
                dx = (distanceX > 0) ? 1 : (distanceX < 0) ? -1 : 0;
                dy = (distanceY > 0) ? 1 : (distanceY < 0) ? -1 : 0;
            }
        }
        // Move the cop
        if (copNumMoves >= 2) {
            // If cop has at least 2 moves per turn, move towards the nearest robber
            cop.x = cop.x + dx;
            cop.y = cop.y + dy;
        } else {
            // Otherwise, move only in one direction based on the nearest robber
            if (abs(dx) > abs(dy)) {
                cop.x = cop.x + dx;
            } else {
                cop.y = cop.y + dy;
            }
        }
        // Adjust cop's position if it's in a corner
        if (cop.x == 0 && cop.y == 0) {
            cop.x = 1; // Move right
            cop.y = 1; // Move down
        } else if (cop.x == 0 && cop.y == gridSize) {
            cop.x = 1; // Move right
            cop.y = gridSize - 1; // Move up
        } else if (cop.x == gridSize && cop.y == 0) {
            cop.x = gridSize - 1; // Move left
            cop.y = 1; // Move down
        } else if (cop.x == gridSize && cop.y == gridSize) {
            cop.x = gridSize - 1; // Move left
            cop.y = gridSize - 1; // Move up
        }
    }

    // Move robbers
    for (auto& robber : robbers) {
        // Calculate the direction away from the nearest cop, if any
        int dx = 0, dy = 0;
        bool speedPastCop = false; // Flag to indicate if the robber should speed past the cop
        for (const auto& cop : cops) {
            int distanceX = cop.x - robber.x;
            int distanceY = cop.y - robber.y;
            int absDistanceX = abs(distanceX);
            int absDistanceY = abs(distanceY);
            if (absDistanceX + absDistanceY <= copNumMoves) {
                // Robber is within the range of cop's moves
                dx = (distanceX > 0) ? 1 : (distanceX < 0) ? -1 : 0;
                dy = (distanceY > 0) ? 1 : (distanceY < 0) ? -1 : 0;
                // Check if robber can speed past the cop
                if (absDistanceX + absDistanceY <= robberNumMoves) {
                    // Robber can move past the cop within its own move limit
                    speedPastCop = true;
                }
            }
        }
        // Adjust movement options if robber is in a corner
        if (robber.x == 0 && robber.y == 0) {
            dx = 1; // Move right
            dy = 1; // Move down
        } else if (robber.x == 0 && robber.y == gridSize) {
            dx = 1; // Move right
            dy = -1; // Move up
        } else if (robber.x == gridSize && robber.y == 0) {
            dx = -1; // Move left
            dy = 1; // Move down
        } else if (robber.x == gridSize && robber.y == gridSize) {
            dx = -1; // Move left
            dy = -1; // Move up
        }
        // Move the robber
        if (robberNumMoves >= 2) {
            // If robber has at least 2 moves per turn, move away from the nearest cop or speed past it
            robber.x = robber.x + dx;
            robber.y = robber.y + dy;
        } else {
            // Otherwise, move only in one direction based on the nearest cop
            if (abs(dx) > abs(dy)) {
                robber.x = robber.x - dx;
            } else {
                robber.y = robber.y - dy;
            }
        }
    }
}


    // Display the grid with players and their movement
    void displayGridWithMovement() {
    vector<vector<char>> grid(gridSize + 1, vector<char>(gridSize + 1, '.')); // Initialize grid with dots

    // Place cops on the grid
    for (const auto& cop : cops) {
        grid[cop.x][cop.y] = 'C';
    }

    // Place robbers on the grid
    for (const auto& robber : robbers) {
        grid[robber.x][robber.y] = 'R';
    }

    // Display the grid with player positions
    for (int i = 0; i <= gridSize; ++i) {
        for (int j = 0; j <= gridSize; ++j) {
            cout << grid[i][j] << ' ';
        }
        cout << endl;
    }

    // Display positions of cops
    cout << "Cops: ";
    for (const auto& cop : cops) {
        cout << "(" << cop.x << "," << cop.y << ") ";
    }
    cout << endl;

    // Display positions of robbers
    cout << "Robbers: ";
    for (const auto& robber : robbers) {
        cout << "(" << robber.x << "," << robber.y << ") ";
    }
    cout << endl;
}

    // Play the game and display all moves
    void playAndDisplayMoves() {
        initializePlayers();

        cout << "Initial Grid:\n";
        displayGridWithMovement();

        while (true) {
            movePlayers();
            cout << "\nAfter Moving:\n";
            displayGridWithMovement();

            for (auto it = robbers.begin(); it != robbers.end();) {
                bool caught = false;
                for (auto& cop : cops) {
                    if (isCaught(cop, *it)) {
                        it = robbers.erase(it);
                        caught = true;
                        break;
                    }
                }
                if (!caught) ++it;
            }

            if (robbers.empty()) {
                cout << "All robbers are caught!\n";
                break;
            }
        }
    }
};

int main() {
    srand(time(nullptr));

    cout << "Welcome to Cops and Robbers Game!\n";
    cout << "Enter the number of cops: ";
    int numCops;
    cin >> numCops;
    cout << "Enter the number of robbers: ";
    int numRobbers;
    cin >> numRobbers;
    cout << "Enter the n x n size of the grid: ";
    int gridSize;
    cin >> gridSize;
    gridSize--; // Adjust

    if (gridSize < 1) {
        cout << "Grid size must be at least 1.\n";
        return 1;
    }

    cout << "Enter the number of moves for each turn for cops: ";
    int copNumMoves;
    cin >> copNumMoves;
    cout << "Enter the number of moves for each turn for robbers: ";
    int robberNumMoves;
    cin >> robberNumMoves;

    Game game(numCops, numRobbers, gridSize, copNumMoves, robberNumMoves);
    game.playAndDisplayMoves();

    return 0;
}





