#ifndef POWERUP_H
#define POWERUP_H

#include "raylib.h"
#include <vector>
#include <deque>
#include <queue>

enum PowerUpType {
    SPEED_BOOST,
    SCORE_MULTIPLIER,
    INVINCIBILITY
};

struct ActivePowerUp {
    PowerUpType type;
    float remainingTime;
    
    bool operator<(const ActivePowerUp& other) const {
        return remainingTime > other.remainingTime;
    }
};

class PowerUp {
private:
    Vector2 position;
    PowerUpType type;
    int cellSize;
    Color powerUpColor;
    int gridWidth;
    int gridHeight;
    bool isActive;
    float spawnTimer;
    float spawnInterval;
    
    std::priority_queue<ActivePowerUp> activePowerUps;
    
    std::vector<Vector2> GetValidPositions(const std::deque<Vector2>& snakeBody);
    Color GetPowerUpColor(PowerUpType type) const;
    const char* GetPowerUpName(PowerUpType type) const;
    
public:
    PowerUp(int cellSize, int screenWidth, int screenHeight);
    
    void Update(float deltaTime);
    void Spawn(const std::deque<Vector2>& snakeBody);
    void Collect(PowerUpType type, float duration);
    
    Vector2 GetPosition() const { return position; }
    PowerUpType GetType() const { return type; }
    bool IsActive() const { return isActive; }
    
    bool HasActivePowerUp(PowerUpType type) const;
    float GetPowerUpTimeRemaining(PowerUpType type) const;
    
    void Draw() const;
    void DrawActivePowerUps(int screenHeight) const;
};

#endif
