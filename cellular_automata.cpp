#include <iostream>
#include <vector>
#include <fstream> // necessary for file operations

using namespace std;

void updateGeneration(vector<int>& cells) {
    vector<int> temp = cells;
    for(size_t i = 1; i < cells.size() - 1; ++i) {
        int left = temp[i - 1];
        int right = temp[i + 1];
        cells[i] = left ^ right; // Rule 30
    }
}

// function to save the automaton as a PPM image
void saveToPPM(const vector<vector<int>>& generations, const string& filename) {
    int width = generations[0].size();
    int height = generations.size();

    ofstream ppmFile(filename);
    // P3 format header for PPM, width, height, and max color value (1 in this case for binary black/white)
    ppmFile << "P3\n" << width << " " << height << "\n1\n";
    for (const auto& row : generations) {
        for (int cell : row) {
            // Output color as black or white based on cell state
            ppmFile << cell << " " << cell << " " << cell << "  ";
        }
        ppmFile << "\n";
    }
    ppmFile.close();
}

int main() {
    const size_t width = 80; // cell row width
    const int generations = 25; // # generations to simulate

    vector<int> cells(width, 0);
    cells[width / 2] = 1; // initializing the middle cell with a single active state

    vector<vector<int>> allGenerations; // to store all generations for the PPM output

    // simulating cellular automata
    for(int i = 0; i < generations; ++i) {
        allGenerations.push_back(cells); // adding the current generation to allGenerations
        updateGeneration(cells);
    }

    // Save the automaton to a PPM file in the current working directory
    saveToPPM(allGenerations, "cellular_automata.ppm");

    return 0;
}
