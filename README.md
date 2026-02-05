# 🐍 Snake Game - Modern C++ Implementation

A feature-rich implementation of the classic Snake game built with C++17 and Raylib, showcasing advanced data structures, object-oriented design, and procedural audio generation.

![Snake Game](screenshots/gameplay.png)

---

## 🎮 Features

### Core Gameplay
- **Smooth Controls**: Dual input support (WASD + Arrow keys)
- **Dynamic Food System**: Intelligent spawning that avoids snake collision
- **Collision Detection**: Wall and self-collision with visual feedback
- **Score Tracking**: Real-time score display with high score persistence

### Power-Up System
Three unique power-ups that spawn every 10 seconds:

| Power-Up | Symbol | Effect | Duration |
|----------|--------|--------|----------|
| **Speed Boost** | Blue "S" | 2x movement speed | 5 seconds |
| **Score Multiplier** | Gold "x2" | Double points (20 per food) | 5 seconds |
| **Invincibility** | Purple "I" | Pass through walls & self | 5 seconds |

![Power-Ups](screenshots/powerups.png)

- Multiple power-ups can be active simultaneously
- Visual timer bars show remaining time for each effect
- Priority queue-based expiry system for efficient management

### Audio System
- **Procedurally Generated Sounds**: No external audio files required
  - Eat sound: Satisfying descending tone
  - Power-up sound: Ascending victory chime
  - Game over sound: Dramatic descending effect
- **Background Music**: Simple 4-note bass line loop
- **Mute Toggle**: Press 'M' to toggle audio on/off

---

## 🏗️ Architecture & Data Structures

### Three Key Data Structures:

#### 1. **Deque (std::deque)** - Snake Body
```cpp
std::deque<Vector2> body;
```
- **Why**: O(1) insertion at head, O(1) deletion at tail
- **Usage**: Perfect for snake movement (add head, remove tail)
- **Benefit**: No element shifting, efficient memory usage

#### 2. **Vector (std::vector)** - Valid Positions
```cpp
std::vector<Vector2> GetValidPositions(const std::deque<Vector2>& snakeBody);
```
- **Why**: Dynamic size, random access
- **Usage**: Filter grid positions, exclude snake-occupied cells
- **Benefit**: Fast random position selection for spawning

#### 3. **Priority Queue (std::priority_queue)** - Power-Up Timers
```cpp
std::priority_queue<ActivePowerUp> activePowerUps;
```
- **Why**: Auto-sorted by expiry time
- **Usage**: Track multiple active power-ups
- **Benefit**: O(log n) insertion, automatic ordering

---

## 🛠️ Technical Stack

- **Language**: C++17
- **Graphics**: [Raylib](https://www.raylib.com/) 5.0
- **Build System**: g++ (MinGW-w64)
- **Platform**: Windows (MSYS2 environment)
- **Standard Library**: STL containers

---

## 📦 Installation & Setup

### Prerequisites
- MSYS2 (for Windows)
- MinGW-w64 GCC compiler
- Raylib library

### Install Dependencies (MSYS2)
```bash
# Open MSYS2 MINGW64 terminal
pacman -S mingw-w64-x86_64-gcc
pacman -S mingw-w64-x86_64-raylib
```

### Clone and Build
```bash
# Clone the repository
git clone https://github.com/yourusername/snake-game-cpp.git
cd snake-game-cpp

# Build the project
chmod +x build.sh
./build.sh

# Run the game
./snake.exe
```

---

## 🎯 How to Play

### Controls
| Key | Action |
|-----|--------|
| **Arrow Keys / WASD** | Move snake |
| **M** | Mute/unmute audio |
| **SPACE** | Restart (on game over) |
| **ESC** | Exit game |

### Gameplay Tips
1. Collect red food to grow and score points (+10, or +20 with multiplier)
2. Power-ups spawn every 10 seconds
3. Multiple power-up effects can stack!
4. Use invincibility to escape tight situations
5. Watch timer bars at bottom to plan your strategy

---

## 📂 Project Structure
```
SnakeGame/
├── include/
│   ├── Game.h              # Main game manager
│   ├── Snake.h             # Snake entity (deque-based)
│   ├── Food.h              # Food spawning (vector-based)
│   ├── PowerUp.h           # Power-up system (priority queue)
│   └── SoundManager.h      # Audio generation
├── src/
│   ├── Game.cpp
│   ├── Snake.cpp
│   ├── Food.cpp
│   ├── PowerUp.cpp
│   ├── SoundManager.cpp
│   └── main.cpp
├── build.sh                # Build script
└── README.md
```

---

## 🔬 Key Implementation Details

### Snake Movement (Deque Usage)
```cpp
void Snake::Move() {
    Vector2 newHead = calculateNewPosition();
    body.push_front(newHead);  // O(1) - Add new head
    body.pop_back();           // O(1) - Remove tail
}
```

### Power-Up Timer Management (Priority Queue)
```cpp
void PowerUp::Update(float deltaTime) {
    // Priority queue automatically keeps next-expiring power-up at top
    while (!activePowerUps.empty()) {
        ActivePowerUp current = activePowerUps.top();
        current.remainingTime -= deltaTime;
        
        if (current.remainingTime > 0) {
            updatedQueue.push(current);  // Auto-sorted!
        }
    }
}
```

### Procedural Audio Generation
```cpp
// Generate eat sound with descending frequency
for (unsigned int i = 0; i < frameCount; i++) {
    float frequency = 800.0f - (t * 2000.0f);  // 800Hz → 0Hz
    data[i] = (short)(sin(2.0f * PI * frequency * t) * amplitude);
}
```

---

## 🎓 Learning Outcomes

### Data Structures Mastery
- **Deque**: Queue operations with both-end access
- **Vector**: Dynamic arrays with efficient filtering
- **Priority Queue**: Automatic sorting for time-based events

### Game Development Concepts
- Game loop architecture and frame timing
- Collision detection algorithms
- State management patterns
- Audio synthesis basics

### C++ Best Practices
- RAII (Resource Acquisition Is Initialization)
- Separation of concerns
- Modern C++ features (auto, nullptr, range-based loops)

---

## 🚀 Future Enhancements

- [ ] Dynamic obstacles system
- [ ] Difficulty progression (speed increases with score)
- [ ] Particle effects (explosions, trails)
- [ ] Main menu and pause screen
- [ ] High score persistence (save to file)
- [ ] Different game modes

---

## 🤝 Contributing

Contributions welcome! Feel free to:
1. Fork the repository
2. Create a feature branch
3. Submit a pull request

---

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

## 👨‍💻 Developer

**Fuzail Faraz**

- GitHub: [@fuzailfaraz](https://github.com/fuzailfaraz)
- LinkedIn: [Fuzail Faraz](https://linkedin.com/in/fuzailfaraz)

---

## 🙏 Acknowledgments

- [Raylib](https://www.raylib.com/) - Fantastic graphics library
- Classic Snake game for timeless inspiration

---

## ⭐ Star This Repository

If you found this project helpful or educational, please consider giving it a star!

---

*Developed with ❤️ and C++*
