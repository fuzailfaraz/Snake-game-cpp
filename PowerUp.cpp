#include "PowerUp.h"
#include <cstdlib>
#include <cmath>

PowerUp::PowerUp(int cellSize, int screenWidth, int screenHeight) 
    : cellSize(cellSize), isActive(false), spawnTimer(0.0f), spawnInterval(10.0f) {
    
    gridWidth = screenWidth / cellSize;
    gridHeight = screenHeight / cellSize;
    
    position = {0, 0};
    type = SPEED_BOOST;
    powerUpColor = BLUE;
}

void PowerUp::Update(float deltaTime) {
    if (!isActive) {
        spawnTimer += deltaTime;
        return;
    }
    
    std::priority_queue<ActivePowerUp> updatedQueue;
    
    while (!activePowerUps.empty()) {
        ActivePowerUp current = activePowerUps.top();
        activePowerUps.pop();
        
        current.remainingTime -= deltaTime;
        
        if (current.remainingTime > 0) {
            updatedQueue.push(current);
        }
    }
    
    activePowerUps = updatedQueue;
}

std::vector<Vector2> PowerUp::GetValidPositions(const std::deque<Vector2>& snakeBody) {
    std::vector<Vector2> validPositions;
    
    for (int x = 0; x < gridWidth; x++) {
        for (int y = 0; y < gridHeight; y++) {
            Vector2 pos = {(float)(x * cellSize), (float)(y * cellSize)};
            
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

void PowerUp::Spawn(const std::deque<Vector2>& snakeBody) {
    if (spawnTimer < spawnInterval) return;
    
    std::vector<Vector2> validPositions = GetValidPositions(snakeBody);
    
    if (!validPositions.empty()) {
        int randomIndex = std::rand() % validPositions.size();
        position = validPositions[randomIndex];
        
        type = static_cast<PowerUpType>(std::rand() % 3);
        powerUpColor = GetPowerUpColor(type);
        
        isActive = true;
        spawnTimer = 0.0f;
    }
}

void PowerUp::Collect(PowerUpType type, float duration) {
    isActive = false;
    spawnTimer = 0.0f;
    
    ActivePowerUp newPowerUp;
    newPowerUp.type = type;
    newPowerUp.remainingTime = duration;
    
    activePowerUps.push(newPowerUp);
}

bool PowerUp::HasActivePowerUp(PowerUpType type) const {
    std::priority_queue<ActivePowerUp> tempQueue = activePowerUps;
    
    while (!tempQueue.empty()) {
        if (tempQueue.top().type == type) {
            return true;
        }
        tempQueue.pop();
    }
    
    return false;
}

float PowerUp::GetPowerUpTimeRemaining(PowerUpType type) const {
    std::priority_queue<ActivePowerUp> tempQueue = activePowerUps;
    
    while (!tempQueue.empty()) {
        if (tempQueue.top().type == type) {
            return tempQueue.top().remainingTime;
        }
        tempQueue.pop();
    }
    
    return 0.0f;
}

Color PowerUp::GetPowerUpColor(PowerUpType type) const {
    switch (type) {
        case SPEED_BOOST: return BLUE;
        case SCORE_MULTIPLIER: return GOLD;
        case INVINCIBILITY: return PURPLE;
        default: return WHITE;
    }
}

const char* PowerUp::GetPowerUpName(PowerUpType type) const {
    switch (type) {
        case SPEED_BOOST: return "SPEED BOOST";
        case SCORE_MULTIPLIER: return "SCORE x2";
        case INVINCIBILITY: return "INVINCIBLE";
        default: return "UNKNOWN";
    }
}

void PowerUp::Draw() const {
    if (!isActive) return;
    
    static float pulse = 0.0f;
    pulse += 0.1f;
    int offset = (int)(std::sin(pulse) * 3);
    
    DrawRectangle(position.x + offset, position.y + offset, 
                  cellSize - offset*2, cellSize - offset*2, powerUpColor);
    DrawRectangleLines(position.x, position.y, cellSize, cellSize, WHITE);
    
    const char* symbol = "";
    switch (type) {
        case SPEED_BOOST: symbol = "S"; break;
        case SCORE_MULTIPLIER: symbol = "x2"; break;
        case INVINCIBILITY: symbol = "I"; break;
    }
    
    int textWidth = MeasureText(symbol, 15);
    DrawText(symbol, position.x + cellSize/2 - textWidth/2, 
             position.y + cellSize/2 - 7, 15, BLACK);
}

void PowerUp::DrawActivePowerUps(int screenHeight) const {
    std::priority_queue<ActivePowerUp> tempQueue = activePowerUps;
    
    int yOffset = screenHeight - 80;
    int index = 0;
    
    while (!tempQueue.empty()) {
        ActivePowerUp current = tempQueue.top();
        tempQueue.pop();
        
        Color color = GetPowerUpColor(current.type);
        const char* name = GetPowerUpName(current.type);
        
        DrawRectangle(10, yOffset + (index * 25), 200, 20, Fade(color, 0.3f));
        
        float timePercent = current.remainingTime / 5.0f;
        DrawRectangle(10, yOffset + (index * 25), (int)(200 * timePercent), 20, color);
        
        DrawText(TextFormat("%s: %.1fs", name, current.remainingTime), 
                 15, yOffset + (index * 25) + 2, 15, WHITE);
        
        index++;
    }
}
