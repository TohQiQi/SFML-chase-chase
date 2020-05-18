#pragma once

#include "RequiredHeaders.h"

class Background
{
    private:
        //background
        sf::Texture BackgroundTexture[3];
        sf::Sprite Background[2];
        sf::Sprite Tracks[2];
        
        bool ParallexBool[4] = { 1,0,1,0 };
        float InitialBackgroundSpeed = 5;
        float InitialTrackSpeed = 5;

    public:
        float BackgroundSpeed = InitialBackgroundSpeed;
        float TracksSpeed = InitialTrackSpeed;

        void Intialize(sf::RenderWindow& GameWindow)
        {
            for(int i = 0; i < 3; i++)
            {
                BackgroundTexture[i].loadFromFile("res/Textures/Background" + std::to_string(i + 1) + ".png");
            }

            //track
            for(int i = 0; i < 2; i++)
            {
                Tracks[i].setTexture(BackgroundTexture[2]);
                if(i == 0)
                {
                    Tracks[i].setPosition(0, 0);
                }
                else
                {
                    Tracks[i].setPosition(GameWindow.getSize().x, 0);
                }
            }

            // background
           for(int i = 0; i < 2; i++)
           {
               Background[i].setTexture(BackgroundTexture[1]);
               if(i == 0)
               {
                   Background[i].setPosition(0,0);
               }
               else
               {
                   Background[i].setPosition(GameWindow.getSize().x, 0);
               }
           }
        }

    void ResetSpeed()
    {
        BackgroundSpeed = InitialBackgroundSpeed;
        TracksSpeed = InitialTrackSpeed;
    }

    void ZeroSpeed()
    {
        BackgroundSpeed = 0;
        TracksSpeed = 0;
    }

   void SubParallex(sf::Sprite Object[], bool& Move0, bool& Move1, float& Speed, sf::RenderWindow& GameWindow)
	{
		if (Move0)
		{
			Object[0].move(-Speed, 0);
		}
		if (Move1)
		{
			Object[1].move(-Speed, 0);
		}
		if (Object[0].getPosition().x <= GameWindow.getSize().x - Object[0].getGlobalBounds().width + 5)
		{
			Move1 = true;
		}
		if (Object[1].getPosition().x <= GameWindow.getSize().x - Object[1].getGlobalBounds().width + 5)
		{
			Move0 = true;
		}
		if (Object[0].getPosition().x <= -Object[0].getGlobalBounds().width)
		{
			Move0 = false;
			Object[0].setPosition(GameWindow.getSize().x, 0);
		}
		if (Object[1].getPosition().x <= -Object[1].getGlobalBounds().width)
		{
			Move1 = false;
			Object[1].setPosition(GameWindow.getSize().x, 0);
		}
	} 

    void Parallex(sf::RenderWindow& GameWindow)
	{
		SubParallex(Tracks, ParallexBool[0], ParallexBool[1], TracksSpeed, GameWindow);
		SubParallex(Background, ParallexBool[2], ParallexBool[3], BackgroundSpeed, GameWindow);
	}

    void Draw(sf::RenderWindow& GameWindow)
    {
        for(int i = 0; i < 2; i++)
        {
            GameWindow.draw(Background[i]);
            GameWindow.draw(Tracks[i]);
        }
    }
};