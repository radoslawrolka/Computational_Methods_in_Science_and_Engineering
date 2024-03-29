#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

// Global 
const int GRID_SIZE = 10;                 // Number of cells in each row and column
const int DELAY = 1;                       // Delay between each frame in milliseconds
bool grid[GRID_SIZE][GRID_SIZE] = {false}; // Initialize grid with all cells set to false

// Function prototypes
struct Points {int x1, y1, x2, y2;};
int energyDifference(Points points);
Points RandomPoints();
int swapPoints(Points);
int countEnergy();
void annealing(int& energy);
void drawGrid(sf::RenderWindow& window);
void initializeGrid();


// Energy models (if grid[i][j] == grid[i+k][j+l] then energy += surround_by_same[k+1][l+1])
const int surround_by_others[3][3] = {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
const int surround_by_same[3][3]   = {{0, -1, 0}, {-1, 0, -1}, {0, -1, 0}};
// TODO


// Parameters
const float density = 0.5;                 // Density of the grid (black cells)
double temperature = 1;                    // Initial temperature
const double cooling_rate = 0.98;          // Cooling rate
const float acceptance = 50;              // Acceptance probability
const int iterations = 10000;              // Number of iterations
const int* model = surround_by_others[0];    // Energy model
const int nrows = 3;                       // Number of rows in the energy model
const int ncols = 3;                       // Number of columns in the energy model

int main() {
    srand(time(NULL));
    int iterations = 0;
    initializeGrid();
    int energy = countEnergy();
    sf::RenderWindow window(sf::VideoMode(GRID_SIZE, GRID_SIZE), "Bitmap annealing");
    while (window.isOpen()) {
        sf::Event event;
        if (window.pollEvent(event) && event.type == sf::Event::Closed) {
            window.close();
        }
        annealing(energy);
        drawGrid(window);
        sf::sleep(sf::milliseconds(DELAY));
        std::cout << "Iter: " << iterations << " Temp: " << temperature << " Energy: " << energy << std::endl;
        ++iterations;
    }
    return 0;
}


int energyDifference(Points points) {
    int energy = 0;
    for (int offset_x = -1; offset_x <= 1; ++offset_x) {
        for (int offset_y = -1; offset_y <= 1; ++offset_y) {
            int x1 = points.x1 + offset_x;
            int y1 = points.y1 + offset_y;
            int x2 = points.x2 + offset_x;
            int y2 = points.y2 + offset_y;
            if (x1 >= 0 && x1 < GRID_SIZE && y1 >= 0 && y1 < GRID_SIZE) {
                // Calculate index for model array
                int index1 = (offset_x + 1) * 3 + (offset_y + 1);
                energy += model[index1] * (grid[points.x1][points.y1] == grid[x1][y1] ? 1 : -1);
            }
            if (x2 >= 0 && x2 < GRID_SIZE && y2 >= 0 && y2 < GRID_SIZE) {
                // Calculate index for model array
                int index2 = (offset_x + 1) * 3 + (offset_y + 1);
                energy += model[index2] * (grid[points.x2][points.y2] == grid[x2][y2] ? 1 : -1);
            }
        }
    }
    return energy;
}

std::vector<std::pair<int, int>> generatePermutations(int nrows, int ncols) {
    std::vector<std::pair<int, int>> permutations;
    for (int i = 0; i < nrows; ++i) {
        for (int j = 0; j < ncols; ++j) {
            permutations.emplace_back(i, j);
        }
    }
    return permutations;
}

void shufflePermutations(std::vector<std::pair<int, int>>& permutations) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(permutations.begin(), permutations.end(), g);
}

void initializeGrid() {
    std::vector<std::pair<int, int>> permutations = generatePermutations(GRID_SIZE, GRID_SIZE);
    shufflePermutations(permutations);
    for (int i = 0; i < int(GRID_SIZE*GRID_SIZE*density); ++i) {
        grid[permutations[i].first][permutations[i].second] = true;
    }
}

Points RandomPoints() {
    return Points{rand() % GRID_SIZE, rand() % GRID_SIZE, rand() % GRID_SIZE, rand() % GRID_SIZE};
}

int swapPoints(Points points) {
    int previous_energy = energyDifference(points);
    bool temp = grid[points.x1][points.y1];
    grid[points.x1][points.y1] = grid[points.x2][points.y2];
    grid[points.x2][points.y2] = temp;
    return energyDifference(points) - previous_energy;
}

int countEnergy() {
    int energy = 0;
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            for (int offset_x = -1; offset_x <= 1; ++offset_x) {
                for (int offset_y = -1; offset_y <= 1; ++offset_y) {
                    int x = i + offset_x;
                    int y = j + offset_y;
                    if (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE) {
                        energy += surround_by_others[offset_x + 1][offset_y + 1] * (grid[i][j] == grid[x][y] ? 1 : -1);
                    }
                }
            }
        }
    }
    return energy;
}
void annealing(int& energy) {
    temperature *= cooling_rate;
    Points points = RandomPoints();
    int delta_energy = swapPoints(points);
    if (delta_energy < 0) {
        energy += delta_energy;
    } else {
        if ( (rand() / RAND_MAX) < exp(-delta_energy / temperature)) {
            energy += delta_energy;
        } else {
            bool temp = grid[points.x1][points.y1];
            grid[points.x1][points.y1] = grid[points.x2][points.y2];
            grid[points.x2][points.y2] = temp;
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
    window.clear();
    window.draw(sprite);
    window.display();
}
