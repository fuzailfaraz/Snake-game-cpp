#!/bin/bash

echo "=== Compiling Snake Game ==="

# Compile all .cpp files in src/
g++ -std=c++17 -Wall -Wextra -O2 -Iinclude src/*.cpp -o snake.exe -lraylib -lopengl32 -lgdi32 -lwinmm

if [ $? -eq 0 ]; then
    echo "✅ Build successful!"
    echo "Run with: ./snake.exe"
else
    echo "❌ Build failed!"
    exit 1
fi
