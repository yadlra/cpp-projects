#include <iostream>
#include <vector>
#include <string>
#include <unistd.h> // for sleep()

using namespace std;

// printing the current generation of cells
void printGeneration(const vector<int>& cells) {
    for(int cell : cells) {
        cout << (cell ? "█" : " ") << " ";
    }
    cout << endl;
}

// updatin the generation based on Rule 30
void updateGeneration(vector<int>& cells) {
    vector<int> temp = cells;
    for(size_t i = 1; i < cells.size() - 1; ++i) {
        int left = temp[i - 1];
        // int self = temp[i];
        int right = temp[i + 1];
        cells[i] = left ^ right;
    }
}

int main() {
    const size_t width = 80; // width of the cell row
    const int generations = 25; // number of generations to simulate

    vector<int> cells(width, 0);
    cells[width / 2] = 1; // initializing the middle cell

    // simulating cellular automata
    for(int i = 0; i < generations; ++i) {
        printGeneration(cells);
        updateGeneration(cells);
        usleep(100000); // slowing down output for visibility
    }

    return 0;
}
