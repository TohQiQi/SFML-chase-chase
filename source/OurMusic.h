#pragma once

#include"RequiredHeaders.h"

class OurMusic
{
    private:

        sf::SoundBuffer Jump;
        sf::SoundBuffer Destroyed,Hit, Teleport;
        sf::Sound sound;
        std::string JumpPath = "res/Audio/Jump.WAV";
        std::string DestroyedPath = "res/Audio/Destroy.WAV";
        std::string HitPath = "res/Audio/Hit.wav";
        std::string TeleportPath = "res/Audio/Teleport.wav";
        sf::Music BacKgroundMusic;

    public:
        int CurrentMusic = 0;
        bool MusicChanged = false;
        bool CreditsMusic = false;
        void Intialize()
        {
            Jump.loadFromFile(JumpPath);
            Destroyed.loadFromFile(DestroyedPath);
            Hit.loadFromFile(HitPath);
            Teleport.loadFromFile(TeleportPath);
        }

        void BackgroundMusic(std::string Path)
        {

            BacKgroundMusic.openFromFile(Path);
            if (Path == "res/Audio/GameOver.wav")
            {
                BacKgroundMusic.setLoop(false);
                BacKgroundMusic.setVolume(100);
            }
            else if (Path == "res/Audio/Fist-Bump.wav")
            {
                BacKgroundMusic.setVolume(100);
                BacKgroundMusic.setLoop(true);
            }
            else
            {
                BacKgroundMusic.setLoop(true);
                BacKgroundMusic.setVolume(70);
            }
            BacKgroundMusic.play();
        }

        void SoundEffects(std::string Path)
        {
            if (Path == JumpPath)
            {
                sound.setBuffer(Jump);
            }
            else if (Path == DestroyedPath)
            {
                sound.setBuffer(Destroyed);
            }
            else if(Path==HitPath)
            {
                sound.setBuffer(Hit);
            }
            else if (Path == TeleportPath)
            {
                sound.setBuffer(Teleport);
            }
            sound.play();
        }
};
