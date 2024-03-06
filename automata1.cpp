
//This version is to see the automata in action in the terminal

#include <iostream>
#include <vector>
#include <string>
#include <unistd.h> // needed for sleep()

using namespace std;

// this function is to print the current generation of cells
void printGeneration(const vector<int>& cells) {
    for(int cell : cells) {
        cout << (cell ? "█" : " ") << " ";
    }
    cout << endl;
}

// this function is to update the generation based on Rule 30
void updateGeneration(vector<int>& cells) {
    vector<int> temp = cells;
    for(size_t i = 1; i < cells.size() - 1; ++i) {
        int left = temp[i - 1];
        int self = temp[i];
        int right = temp[i + 1];
        cells[i] = left ^ (self || right);
    }
}

int main() {
    const size_t width = 80; // the cell row width
    const int generations = 25; // numbers of generations to simulate

    vector<int> cells(width, 0);
    cells[width / 2] = 1; // initialising the middle cell

    // simulating cellular automata
    for(int i = 0; i < generations; ++i) {
        printGeneration(cells);
        updateGeneration(cells);
        usleep(100000); // slowing down output for visibility
    }

    return 0;
}
