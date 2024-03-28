#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

const int GRID_SIZE = 10; // Number of cells in each row and column
const int CELL_SIZE = 50; // Size of each cell in pixels

bool grid[GRID_SIZE][GRID_SIZE] = {false}; // Initialize grid with all cells set to false

void toggleCellState(int x, int y) {
    grid[x][y] = !grid[x][y];
}

void updateGrid() {
    // Randomly toggle cell states
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            if (rand() % 2 == 0) {
                toggleCellState(i, j);
            }
        }
    }
}

void drawGrid(sf::RenderWindow& window) {
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
            cell.setPosition(i * CELL_SIZE, j * CELL_SIZE);
            cell.setOutlineThickness(1);
            cell.setOutlineColor(sf::Color::Black);
            if (grid[i][j])
                cell.setFillColor(sf::Color::White);
            else
                cell.setFillColor(sf::Color::Black);
            window.draw(cell);
        }
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(GRID_SIZE * CELL_SIZE, GRID_SIZE * CELL_SIZE), "Grid");

    // Seed random number generator
    std::srand(std::time(nullptr));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        updateGrid();

        window.clear();
        drawGrid(window);
        window.display();
        sf::sleep(sf::milliseconds(1000)); // Delay to observe changes (1 second)
    }

    return 0;
}
