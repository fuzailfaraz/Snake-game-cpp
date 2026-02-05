#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "Snake.h"
#include "Food.h"
#include "PowerUp.h"
#include "SoundManager.h"

class Game {
private:
    int screenWidth;
    int screenHeight;
    int cellSize;
    bool isRunning;
    bool gameOver;
    
    Snake* snake;
    Food* food;
    PowerUp* powerUp;
    SoundManager* soundManager;
    
    float moveTimer;
    float baseMoveInterval;
    float currentMoveInterval;
    
    int score;
    int highScore;
    
public:
    Game(int width, int height, const char* title);
    ~Game();
    void Run();
    void Update();
    void Draw();
    void HandleInput();
    void CheckCollisions();
    void Reset();
    bool IsRunning() const { return isRunning; }
    
private:
    void UpdatePowerUpEffects();
    void DrawGrid() const;
    void DrawHUD() const;
    void DrawGameOver() const;
};

#endif
