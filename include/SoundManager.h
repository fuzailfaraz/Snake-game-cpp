#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "raylib.h"

class SoundManager {
private:
    Sound eatSound;
    Sound gameOverSound;
    Sound powerUpSound;
    Music backgroundMusic;
    
    bool isMuted;
    float volume;
    
public:
    SoundManager();
    ~SoundManager();
    
    void Initialize();
    void PlayEatSound();
    void PlayGameOverSound();
    void PlayPowerUpSound();
    void PlayBackgroundMusic();
    void StopBackgroundMusic();
    
    void ToggleMute();
    void SetVolume(float vol);
    void UpdateMusic();  // Call every frame to stream music
    
    bool IsMuted() const { return isMuted; }
    float GetVolume() const { return volume; }
    
private:
    // Procedural sound generation - no external files needed!
    void GenerateEatSound();
    void GenerateGameOverSound();
    void GeneratePowerUpSound();
    void GenerateBackgroundMusic();
};

#endif
