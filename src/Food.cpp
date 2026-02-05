#include "Food.h"
#include <cstdlib>
#include <ctime>

Food::Food(int cellSize, int screenWidth, int screenHeight) 
    : cellSize(cellSize), foodColor(RED) {
    
    gridWidth = screenWidth / cellSize;
    gridHeight = screenHeight / cellSize;
    
    // Seed random
    srand(time(nullptr));
    
    // Initial position
    position = {(float)(rand() % gridWidth * cellSize), 
                (float)(rand() % gridHeight * cellSize)};
}

// DATA STRUCTURE: Vector to store all valid spawn positions
// WHY: Allows us to filter out snake positions and randomly select from remaining
std::vector<Vector2> Food::GetValidPositions(const std::deque<Vector2>& snakeBody) {
    std::vector<Vector2> validPositions;
    
    // Generate all possible positions
    for (int x = 0; x < gridWidth; x++) {
        for (int y = 0; y < gridHeight; y++) {
            Vector2 pos = {(float)(x * cellSize), (float)(y * cellSize)};
            
            // Check if position is occupied by snake
            bool occupied = false;
            for (const auto& segment : snakeBody) {
                if (segment.x == pos.x && segment.y == pos.y) {
                    occupied = true;
                    break;
                }
            }
            
            if (!occupied) {
                validPositions.push_back(pos);
            }
        }
    }
    
    return validPositions;
}

void Food::Spawn(const std::deque<Vector2>& snakeBody) {
    std::vector<Vector2> validPositions = GetValidPositions(snakeBody);
    
    if (!validPositions.empty()) {
        int randomIndex = rand() % validPositions.size();
        position = validPositions[randomIndex];
    }
}

void Food::Draw() const {
    DrawRectangle(position.x, position.y, cellSize, cellSize, foodColor);
    DrawRectangleLines(position.x, position.y, cellSize, cellSize, DARKGRAY);
}
