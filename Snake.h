#ifndef SNAKE_H
#define SNAKE_H

#include "raylib.h"
#include <deque>

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Snake {
private:
    std::deque<Vector2> body;
    Direction currentDirection;
    Direction nextDirection;
    int cellSize;
    Color snakeColor;
    
public:
    Snake(Vector2 startPosition, int size);
    void SetDirection(Direction dir);
    void Move();
    void Grow();
    bool CheckSelfCollision() const;
    Vector2 GetHeadPosition() const;
    void Draw() const;
    const std::deque<Vector2>& GetBody() const { return body; }
};

#endif
