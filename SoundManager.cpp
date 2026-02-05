#include "SoundManager.h"
#include <cmath>
#include <cstdlib>

SoundManager::SoundManager() : isMuted(false), volume(0.5f) {
}

SoundManager::~SoundManager() {
    UnloadSound(eatSound);
    UnloadSound(gameOverSound);
    UnloadSound(powerUpSound);
    UnloadMusicStream(backgroundMusic);
    CloseAudioDevice();
}

void SoundManager::Initialize() {
    InitAudioDevice();
    
    GenerateEatSound();
    GenerateGameOverSound();
    GeneratePowerUpSound();
    GenerateBackgroundMusic();
}

void SoundManager::GenerateEatSound() {
    Wave wave = {};
    wave.frameCount = 4800;
    wave.sampleRate = 48000;
    wave.sampleSize = 16;
    wave.channels = 1;
    
    short* data = (short*)malloc(wave.frameCount * sizeof(short));
    
    for (unsigned int i = 0; i < wave.frameCount; i++) {
        float t = (float)i / wave.sampleRate;
        float frequency = 800.0f - (t * 2000.0f);
        float amplitude = 15000.0f * (1.0f - t * 10.0f);
        
        data[i] = (short)(std::sin(2.0f * PI * frequency * t) * amplitude);
    }
    
    wave.data = data;
    eatSound = LoadSoundFromWave(wave);
    UnloadWave(wave);
    
    SetSoundVolume(eatSound, volume);
}

void SoundManager::GenerateGameOverSound() {
    Wave wave = {};
    wave.frameCount = 24000;
    wave.sampleRate = 48000;
    wave.sampleSize = 16;
    wave.channels = 1;
    
    short* data = (short*)malloc(wave.frameCount * sizeof(short));
    
    for (unsigned int i = 0; i < wave.frameCount; i++) {
        float t = (float)i / wave.sampleRate;
        float frequency = 400.0f * (1.0f - t);
        float amplitude = 20000.0f * (1.0f - t * 2.0f);
        
        data[i] = (short)(std::sin(2.0f * PI * frequency * t) * amplitude);
    }
    
    wave.data = data;
    gameOverSound = LoadSoundFromWave(wave);
    UnloadWave(wave);
    
    SetSoundVolume(gameOverSound, volume);
}

void SoundManager::GeneratePowerUpSound() {
    Wave wave = {};
    wave.frameCount = 9600;
    wave.sampleRate = 48000;
    wave.sampleSize = 16;
    wave.channels = 1;
    
    short* data = (short*)malloc(wave.frameCount * sizeof(short));
    
    for (unsigned int i = 0; i < wave.frameCount; i++) {
        float t = (float)i / wave.sampleRate;
        float frequency = 400.0f + (t * 1000.0f);
        float amplitude = 18000.0f * (1.0f - t * 5.0f);
        
        data[i] = (short)(std::sin(2.0f * PI * frequency * t) * amplitude);
    }
    
    wave.data = data;
    powerUpSound = LoadSoundFromWave(wave);
    UnloadWave(wave);
    
    SetSoundVolume(powerUpSound, volume);
}

void SoundManager::GenerateBackgroundMusic() {
    Wave wave = {};
    wave.frameCount = 96000;
    wave.sampleRate = 48000;
    wave.sampleSize = 16;
    wave.channels = 2;
    
    short* data = (short*)malloc(wave.frameCount * 2 * sizeof(short));
    
    float notes[] = {220.0f, 247.0f, 262.0f, 294.0f};
    
    for (unsigned int i = 0; i < wave.frameCount; i++) {
        float t = (float)i / wave.sampleRate;
        int noteIndex = (int)(t * 2) % 4;
        
        float value = std::sin(2.0f * PI * notes[noteIndex] * t) * 8000.0f;
        
        data[i * 2] = (short)value;
        data[i * 2 + 1] = (short)value;
    }
    
    wave.data = data;
    
    ExportWave(wave, "temp_music.wav");
    backgroundMusic = LoadMusicStream("temp_music.wav");
    
    UnloadWave(wave);
    
    SetMusicVolume(backgroundMusic, volume * 0.3f);
}

void SoundManager::PlayEatSound() {
    if (!isMuted) {
        PlaySound(eatSound);
    }
}

void SoundManager::PlayGameOverSound() {
    if (!isMuted) {
        PlaySound(gameOverSound);
    }
}

void SoundManager::PlayPowerUpSound() {
    if (!isMuted) {
        PlaySound(powerUpSound);
    }
}

void SoundManager::PlayBackgroundMusic() {
    if (!isMuted) {
        PlayMusicStream(backgroundMusic);
    }
}

void SoundManager::StopBackgroundMusic() {
    StopMusicStream(backgroundMusic);
}

void SoundManager::UpdateMusic() {
    if (!isMuted) {
        UpdateMusicStream(backgroundMusic);
        
        if (!IsMusicStreamPlaying(backgroundMusic)) {
            PlayMusicStream(backgroundMusic);
        }
    }
}

void SoundManager::ToggleMute() {
    isMuted = !isMuted;
    
    if (isMuted) {
        StopMusicStream(backgroundMusic);
    } else {
        PlayMusicStream(backgroundMusic);
    }
}

void SoundManager::SetVolume(float vol) {
    volume = vol;
    SetSoundVolume(eatSound, volume);
    SetSoundVolume(gameOverSound, volume);
    SetSoundVolume(powerUpSound, volume);
    SetMusicVolume(backgroundMusic, volume * 0.3f);
}
