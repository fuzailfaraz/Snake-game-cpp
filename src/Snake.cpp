#include "Snake.h"

Snake::Snake(Vector2 startPosition, int size) 
    : currentDirection(RIGHT), nextDirection(RIGHT), cellSize(size), snakeColor(GREEN) {
    body.push_back(startPosition);
    body.push_back({startPosition.x - cellSize, startPosition.y});
    body.push_back({startPosition.x - 2 * cellSize, startPosition.y});
}

void Snake::SetDirection(Direction dir) {
    if ((currentDirection == UP && dir == DOWN) ||
        (currentDirection == DOWN && dir == UP) ||
        (currentDirection == LEFT && dir == RIGHT) ||
        (currentDirection == RIGHT && dir == LEFT)) {
        return;
    }
    nextDirection = dir;
}

void Snake::Move() {
    currentDirection = nextDirection;
    Vector2 newHead = body.front();
    
    switch (currentDirection) {
        case UP:    newHead.y -= cellSize; break;
        case DOWN:  newHead.y += cellSize; break;
        case LEFT:  newHead.x -= cellSize; break;
        case RIGHT: newHead.x += cellSize; break;
    }
    
    body.push_front(newHead);
    body.pop_back();
}

void Snake::Grow() {
    Vector2 tail = body.back();
    body.push_back(tail);
}

bool Snake::CheckSelfCollision() const {
    Vector2 head = body.front();
    for (size_t i = 1; i < body.size(); i++) {
        if (head.x == body[i].x && head.y == body[i].y) {
            return true;
        }
    }
    return false;
}

Vector2 Snake::GetHeadPosition() const {
    return body.front();
}

void Snake::Draw() const {
    for (size_t i = 0; i < body.size(); i++) {
        Color segmentColor = (i == 0) ? DARKGREEN : snakeColor;
        DrawRectangle(body[i].x, body[i].y, cellSize, cellSize, segmentColor);
        DrawRectangleLines(body[i].x, body[i].y, cellSize, cellSize, DARKGRAY);
    }
}
