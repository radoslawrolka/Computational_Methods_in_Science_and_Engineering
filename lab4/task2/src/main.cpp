#include <SFML/Graphics.hpp>

const int GRID_SIZE = 512;                 // Number of cells in each row and column
const int DELAY = 100;                      // Delay between each frame in milliseconds

bool grid[GRID_SIZE][GRID_SIZE] = {false}; // Initialize grid with all cells set to false


void annealing() {
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            if (i%2 == 0 && j%2 == 0) {
                grid[i][j] = !grid[i][j];
            }
        }
    }
}


void drawGrid(sf::RenderWindow& window) {
    uint8_t* pixels = new uint8_t[GRID_SIZE * GRID_SIZE * 4];
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            pixels[(i * GRID_SIZE + j) * 4]     = grid[i][j] ? 255 : 0;
            pixels[(i * GRID_SIZE + j) * 4 + 1] = grid[i][j] ? 255 : 0;
            pixels[(i * GRID_SIZE + j) * 4 + 2] = grid[i][j] ? 255 : 0;
            pixels[(i * GRID_SIZE + j) * 4 + 3] = 255;
        }
    }
    sf::Texture texture;
    texture.create(GRID_SIZE, GRID_SIZE);
    texture.update(pixels);
    delete[] pixels;

    sf::Sprite sprite(texture);
    window.draw(sprite);
}


int main() {
    sf::RenderWindow window(sf::VideoMode(GRID_SIZE, GRID_SIZE), "Bitmap annealing");
    while (window.isOpen()) {
        sf::Event event;
        if (window.pollEvent(event) && event.type == sf::Event::Closed) {
            window.close();
        }

        annealing();

        window.clear();
        drawGrid(window);
        window.display();
        sf::sleep(sf::milliseconds(DELAY));
    }

    return 0;
}

/*
cmake --build build --config Release
.\build\bin\Release\CMakeSFMLProject.exe
*/