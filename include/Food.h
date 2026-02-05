#ifndef FOOD_H
#define FOOD_H

#include "raylib.h"
#include <vector>
#include <deque>

class Food {
private:
    Vector2 position;
    int cellSize;
    Color foodColor;
    int gridWidth;
    int gridHeight;
    
public:
    Food(int cellSize, int screenWidth, int screenHeight);
    
    void Spawn(const std::deque<Vector2>& snakeBody);
    Vector2 GetPosition() const { return position; }
    void Draw() const;
    
private:
    std::vector<Vector2> GetValidPositions(const std::deque<Vector2>& snakeBody);
};

#endif
