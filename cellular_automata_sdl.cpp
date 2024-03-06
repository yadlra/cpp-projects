#include <SDL.h>
#include <iostream>
#include <vector>

// Initialize SDL and create a window
bool initSDL(SDL_Window** window, SDL_Renderer** renderer, int screenWidth, int screenHeight) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    *window = SDL_CreateWindow("Cellular Automaton", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    if (!(*window)) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (!(*renderer)) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetRenderDrawColor(*renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    return true;
}

// Close SDL and destroy window
void closeSDL(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// Update the generation based on Rule 30
void updateGeneration(std::vector<int>& cells) {
    std::vector<int> temp = cells;
    for (size_t i = 1; i < cells.size() - 1; ++i) {
        int left = temp[i - 1];
        int right = temp[i + 1];
        cells[i] = left ^ right;
    }
}

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if (!initSDL(&window, &renderer, screenWidth, screenHeight)) {
        std::cerr << "Failed to initialize SDL." << std::endl;
        return -1;
    }

    const size_t width = 80; // Width of the cell row
    std::vector<int> cells(width, 0);
    cells[width / 2] = 1; // Initialize the middle cell

    // Main loop flag
    bool quit = false;
    // Event handler
    SDL_Event e;

    // While application is running
    while (!quit) {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        // Draw cells
        for (size_t i = 0; i < cells.size(); ++i) {
            SDL_Rect fillRect = {static_cast<int>(i * screenWidth / width), screenHeight / 2, screenWidth / width, screenHeight / width};
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF * cells[i]); // Cells are black
            SDL_RenderFillRect(renderer, &fillRect);
        }

        // Update screen
        SDL_RenderPresent(renderer);

        // Update generation
        updateGeneration(cells);

        SDL_Delay(100); // Wait a short period
    }

    // Free resources and close SDL
    closeSDL(window, renderer);

    return 0;
}
