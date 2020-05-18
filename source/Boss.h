#pragma once
#include"RequiredHeaders.h"

class Mode
{
    public:
        //Game Mode Objects
        sf::Sprite SpikeWall;
        sf::Texture SpikeWallTexture;
        
        sf::Sprite Enemy;
        sf::Texture Eggman;
        

        //Arrows
        sf::Texture ArrowTexture[8];
        
        sf::Sprite Arrow;
        
        int RandomArrow = 0;
        int RandomArrowTimer = 0;
        bool IsPressed[4] = { 0,0,0,0 };
        sf::Clock CanPressTimer;
        int PerviousArrow = 0;
        sf::Clock ArrowTimer;
        sf::Clock MoveTime;
        sf::Clock MoveBackTime;
        float Interval = 1;

        // Movement if Arrow is Hit
        bool Move = false;
        bool InPosition = false;
        bool MoveBack = false;
        bool StartMovement = false;

        //Turn off GameMode if Enemy is Destroyed
        bool Destroyed = false;

        void Intialize(sf::RenderWindow& GameWindow)
        {
            SpikeWallTexture.loadFromFile("res/Textures/Mace.png");
            SpikeWall.setTexture(SpikeWallTexture);
            SpikeWall.setPosition(-135, 600);
            SpikeWall.setScale(0.3f, 0.3f);

            Eggman.loadFromFile("res/Textures/eggman.png");
            Enemy.setTexture(Eggman);
            Enemy.scale(0.3f, 0.3f);
            Enemy.setPosition(1000, 350);

            ArrowTexture[0].loadFromFile("res/Textures/up arrow miss.png");
            ArrowTexture[1].loadFromFile("res/Textures/right arrow miss.png");
            ArrowTexture[2].loadFromFile("res/Textures/down arrow  miss.png");
            ArrowTexture[3].loadFromFile("res/Textures/left arrow miss.png");
            for (int i = 4; i < 8; i++)
            {
                ArrowTexture[i].loadFromFile("res/Textures/" + std::to_string(i - 4) + ".png");
            }

            Arrow.setPosition(GameWindow.getSize().x / 2.2, 25.f);
            Arrow.setScale(4.f, 4.f);

        }
        void Draw(sf::RenderWindow& window)
        {
            window.draw(Arrow);
            window.draw(Enemy);
            window.draw(SpikeWall);
        }
        void Reset(sf::RenderWindow& window)
        {
            SpikeWall.setPosition(-140, 600);
            Enemy.setPosition(1000, 350);
        }
};
