#include "Game.h"
#include <algorithm>

Game::Game(int width, int height, const char* title) 
    : screenWidth(width), screenHeight(height), cellSize(20), 
      isRunning(true), gameOver(false), moveTimer(0.0f), 
      baseMoveInterval(0.15f), currentMoveInterval(0.15f),
      score(0), highScore(0) {
    
    InitWindow(screenWidth, screenHeight, title);
    SetTargetFPS(60);
    
    Vector2 startPos = {(float)(screenWidth/2), (float)(screenHeight/2)};
    snake = new Snake(startPos, cellSize);
    food = new Food(cellSize, screenWidth, screenHeight);
    powerUp = new PowerUp(cellSize, screenWidth, screenHeight);
    soundManager = new SoundManager();
    
    soundManager->Initialize();
    soundManager->PlayBackgroundMusic();
    
    food->Spawn(snake->GetBody());
}

Game::~Game() {
    delete snake;
    delete food;
    delete powerUp;
    delete soundManager;
    CloseWindow();
}

void Game::Run() {
    while (!WindowShouldClose() && isRunning) {
        HandleInput();
        Update();
        Draw();
    }
}

void Game::HandleInput() {
    if (IsKeyPressed(KEY_M)) {
        soundManager->ToggleMute();
    }
    
    if (gameOver && IsKeyPressed(KEY_SPACE)) {
        Reset();
    }
    
    if (!gameOver) {
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
            snake->SetDirection(UP);
        }
        if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
            snake->SetDirection(DOWN);
        }
        if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
            snake->SetDirection(LEFT);
        }
        if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) {
            snake->SetDirection(RIGHT);
        }
    }
}

void Game::Update() {
    if (gameOver) return;
    
    float deltaTime = GetFrameTime();
    
    soundManager->UpdateMusic();
    
    powerUp->Update(deltaTime);
    powerUp->Spawn(snake->GetBody());
    
    UpdatePowerUpEffects();
    
    moveTimer += deltaTime;
    
    if (moveTimer >= currentMoveInterval) {
        moveTimer = 0.0f;
        snake->Move();
        CheckCollisions();
    }
}

void Game::UpdatePowerUpEffects() {
    if (powerUp->HasActivePowerUp(SPEED_BOOST)) {
        currentMoveInterval = baseMoveInterval * 0.5f;
    } else {
        currentMoveInterval = baseMoveInterval;
    }
}

void Game::CheckCollisions() {
    Vector2 head = snake->GetHeadPosition();
    
    if (!powerUp->HasActivePowerUp(INVINCIBILITY)) {
        if (head.x < 0 || head.x >= screenWidth || 
            head.y < 0 || head.y >= screenHeight) {
            gameOver = true;
            soundManager->PlayGameOverSound();
            soundManager->StopBackgroundMusic();
            return;
        }
        
        if (snake->CheckSelfCollision()) {
            gameOver = true;
            soundManager->PlayGameOverSound();
            soundManager->StopBackgroundMusic();
            return;
        }
    }
    
    if (head.x == food->GetPosition().x && 
        head.y == food->GetPosition().y) {
        
        snake->Grow();
        food->Spawn(snake->GetBody());
        
        int points = 10;
        if (powerUp->HasActivePowerUp(SCORE_MULTIPLIER)) {
            points *= 2;
        }
        score += points;
        
        soundManager->PlayEatSound();
    }
    
    if (powerUp->IsActive() && 
        head.x == powerUp->GetPosition().x && 
        head.y == powerUp->GetPosition().y) {
        
        powerUp->Collect(powerUp->GetType(), 5.0f);
        soundManager->PlayPowerUpSound();
    }
}

void Game::Reset() {
    gameOver = false;
    
    if (score > highScore) {
        highScore = score;
    }
    
    score = 0;
    
    delete snake;
    delete food;
    delete powerUp;
    
    Vector2 startPos = {(float)(screenWidth/2), (float)(screenHeight/2)};
    snake = new Snake(startPos, cellSize);
    food = new Food(cellSize, screenWidth, screenHeight);
    powerUp = new PowerUp(cellSize, screenWidth, screenHeight);
    
    food->Spawn(snake->GetBody());
    
    soundManager->PlayBackgroundMusic();
}

void Game::DrawGrid() const {
    for (int i = 0; i < screenWidth; i += cellSize) {
        DrawLine(i, 0, i, screenHeight, Fade(DARKGRAY, 0.3f));
    }
    for (int i = 0; i < screenHeight; i += cellSize) {
        DrawLine(0, i, screenWidth, i, Fade(DARKGRAY, 0.3f));
    }
}

void Game::DrawHUD() const {
    DrawText(TextFormat("Score: %d", score), 10, 10, 20, YELLOW);
    DrawText(TextFormat("High Score: %d", highScore), 10, 35, 20, GOLD);
    
    DrawText("WASD/Arrows: Move", screenWidth - 200, 10, 16, LIGHTGRAY);
    DrawText("M: Mute", screenWidth - 200, 30, 16, LIGHTGRAY);
    
    if (soundManager->IsMuted()) {
        DrawText("[MUTED]", screenWidth - 90, 50, 16, RED);
    }
    
    // Developer credit
    DrawText("Developed by Fuzail Faraz", 10, screenHeight - 25, 16, Fade(WHITE, 0.5f));
}

void Game::DrawGameOver() const {
    DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.7f));
    
    const char* gameOverText = "GAME OVER!";
    int textWidth = MeasureText(gameOverText, 60);
    DrawText(gameOverText, 
             screenWidth/2 - textWidth/2, 
             screenHeight/2 - 80, 60, RED);
    
    const char* scoreText = TextFormat("Final Score: %d", score);
    textWidth = MeasureText(scoreText, 30);
    DrawText(scoreText, 
             screenWidth/2 - textWidth/2, 
             screenHeight/2, 30, WHITE);
    
    if (score >= highScore) {
        const char* newHighText = "NEW HIGH SCORE!";
        textWidth = MeasureText(newHighText, 25);
        DrawText(newHighText, 
                 screenWidth/2 - textWidth/2, 
                 screenHeight/2 + 40, 25, GOLD);
    } else {
        const char* highScoreText = TextFormat("High Score: %d", highScore);
        textWidth = MeasureText(highScoreText, 20);
        DrawText(highScoreText, 
                 screenWidth/2 - textWidth/2, 
                 screenHeight/2 + 40, 20, LIGHTGRAY);
    }
    
    const char* restartText = "Press SPACE to Restart";
    textWidth = MeasureText(restartText, 25);
    DrawText(restartText, 
             screenWidth/2 - textWidth/2, 
             screenHeight/2 + 100, 25, LIGHTGRAY);
    
    // Developer credit on game over screen
    const char* devText = "Developed by Fuzail Faraz";
    textWidth = MeasureText(devText, 18);
    DrawText(devText, 
             screenWidth/2 - textWidth/2, 
             screenHeight - 40, 18, Fade(GOLD, 0.7f));
}
    

void Game::Draw() {
    BeginDrawing();
    ClearBackground(BLACK);
    
    if (!gameOver) {
        DrawGrid();
        
        snake->Draw();
        food->Draw();
        powerUp->Draw();
        
        powerUp->DrawActivePowerUps(screenHeight);
        
        DrawHUD();
        
    } else {
        DrawGrid();
        snake->Draw();
        food->Draw();
        
        DrawGameOver();
    }
    
    EndDrawing();
}
