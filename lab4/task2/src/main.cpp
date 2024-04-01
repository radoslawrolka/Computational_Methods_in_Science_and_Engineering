#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>

// Global 
const int GRID_SIZE = 10;                 // Number of cells in each row and column
const int DELAY = 0;                       // Delay between each frame in milliseconds
bool grid[GRID_SIZE][GRID_SIZE] = {false}; // Initialize grid with all cells set to false
std::random_device rd;
std::mt19937 g(rd());

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
const int chess_board[3][3] = {{-1, 1, -1}, {1, 0, 1}, {-1, 1, -1}};
const int group[3][3]   = {{0, -1, 0}, {-1, 0, -1}, {0, -1, 0}};
const int away[3][3]    = {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
const int vertical[3][3] = {{1, -1, 1}, {1, 0, 1}, {1, -1, 1}};
const int horizontal[3][3] = {{1, 1, 1}, {-1, 0, -1}, {1, 1, 1}};
const int diagonal[3][3] = {{-10, 5, 10}, {-5, 0, -5}, {10, 5, -10}};
const int grid[5][5] = {{-1, 0, -1, 0, -1}, {0, 1, 0, 1, 0}, {-1, 0, -1, 0, -1}, {0, 1, 0, 1, 0}, {-1, 0, -1, 0, -1}};

// Parameters
const float density = 0.4;                 // Density of the grid (black cells)
double temperature = 1;                    // Initial temperature
const double cooling_rate = 0.999;         // Cooling rate
const float acceptance = 0.5;               // Acceptance probability
const int iterations = 10000;              // Number of iterations
const int* model = group[0];              // Energy model
const int nrows = 5;                       // Number of rows in the energy model
const int ncols = 5;                       // Number of columns in the energy model

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

int pointEnergy(int x, int y) {
    int energy = 0;
    for (int offset_x = -1; offset_x <= 1; ++offset_x) {
        for (int offset_y = -1; offset_y <= 1; ++offset_y) {
            int x1 = x + offset_x;
            int y1 = y + offset_y;
            if (x1 >= 0 && x1 < GRID_SIZE && y1 >= 0 && y1 < GRID_SIZE) {
                int index = (offset_x + 1) * ncols + (offset_y + 1);
                energy += model[index] * (grid[x][y] == grid[x1][y1] ? 1 : -1);
            }
        }
    }
    return energy;
}

int energyDifference(Points points) {
    int energy = 0;
    //count energy of the points and the points around them
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int x1 = points.x1 + i;
            int y1 = points.y1 + j;
            int x2 = points.x2 + i;
            int y2 = points.y2 + j;
            energy += pointEnergy(x1, y1);
            energy += pointEnergy(x2, y2);
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

void initializeGrid() {
    std::vector<std::pair<int, int>> permutations = generatePermutations(GRID_SIZE, GRID_SIZE);
    std::shuffle(permutations.begin(), permutations.end(), g);
    for (int i = 0; i < int(GRID_SIZE*GRID_SIZE*density); ++i) {
        grid[permutations[i].first][permutations[i].second] = true;
    }
}

Points RandomPoints() {
    // use random_device to get a random number
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
            energy += pointEnergy(i, j);
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
        if (delta_energy * (rand() / RAND_MAX) < acceptance * temperature) {
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
