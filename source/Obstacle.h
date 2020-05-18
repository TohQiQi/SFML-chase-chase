#pragma once
#include"RequiredHeaders.h"


class Obstacle
{
    private:
        sf::Texture SpikeTexture;
        sf::Texture ShipTexture;
    
    public:
        //Obstacles
        sf::Sprite Obstacles[2];
        bool Permission[2];
        float IntialSpeed = 6;
        float Speed = IntialSpeed;

        void Intialize(sf::RenderWindow& window)
        {
            SpikeTexture.loadFromFile("res/Textures/spikes.PNG");
            ShipTexture.loadFromFile("res/Textures/Coin.PNG");
            Obstacles[1].setTexture(ShipTexture);
            Obstacles[0].setTexture(SpikeTexture);
            Obstacles[1].setPosition(window.getSize().x + 50, 447);
            Obstacles[0].setPosition(window.getSize().x + 50, 630);
            for (int i = 0; i < 2; i++)
            {
                Obstacles[i].scale(2.5f, 2.5f);
                Permission[i] = false;
            }
        }
        void Reset(sf::RenderWindow& window)
        {
            Speed = IntialSpeed;
            Obstacles[1].setPosition(window.getSize().x + 50, 447);
            Obstacles[0].setPosition(window.getSize().x + 50, 630);
        }
        void SubGenerateObstacle(sf::Sprite& Object, float Speed, bool& Permission, bool& IsGameover, bool& IsWin, int i, bool& Gamemode, sf::RenderWindow& window)
        {
            static int RandomGenerator = 0;
            static int RandomPosition = 0;
            RandomGenerator = rand() % 75 + 1;
            RandomPosition = rand() % 130 + 1;
            //Gives Random Permission if the GameMode is off
            if (RandomGenerator == 1 && !Gamemode && !IsGameover && !IsWin)
            {
                Permission = true;
            }

            //Move the Object if the permition is on
            if (Permission)
            {
                if (Object.getPosition().x > -160)
                {
                    Object.move(Speed, 0);
                }
                else
                {
                    // checks if the object is a spike or a plane
                    if (i == 0)
                    {
                        Object.setPosition(window.getSize().x + 50, 630);

                    }
                    else
                    {
                        Object.setPosition(window.getSize().x + 50, 500 - RandomPosition);  // sets Random y postion for the plane
                    }
                    Permission = false;
                }
            }
        }

        void GenerateObstacles(sf::RenderWindow& window, bool& IsGameOver, bool& IsWin, bool& GameMode)
        {
            for (int i = 0; i < 2; i++)
            {
                SubGenerateObstacle(Obstacles[i], -Speed, Permission[i], IsGameOver, IsWin, i, GameMode, window);
            }
        }

        void Draw(sf::RenderWindow& window)
        {
            for (int i = 0; i < 2; i++)
            {
                window.draw(Obstacles[i]);
            }
        }
};
