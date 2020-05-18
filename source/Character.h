#pragma once

#include"SFML\Graphics.hpp"
#include"SFML\Window.hpp"
#include"SFML\System.hpp"
#include<SFML\Audio.hpp>
#include"Obstacle.h"
#include"Background.h"
#include"OurMusic.h"
#include"Boss.h"
#include"Menu.h"
#include"LeaderBoard.h"

class Character
{
    private:
        sf::Texture RunTexture[30];
        sf::Texture JumpTexture[30];
		sf::Texture WalkTexture[30];

        //character
        float JumpHeight = 287;


        //Character Jump
        bool Gravity = false;
        int JumpIndex = 0;
        int JumpIndexLimit = 0;
        int JumpFramesPassed = 0;
        float JumpVelocityY = 20;
        float JumpVelocityX = 20;
        float JumpDecceleration = 1.f;
        float GravitionalAcc = 1.7f;
        bool CanMove;
        bool Reset = false;

        //Character Run
        int RunIndex = 0;
        int RunIndexLimit = 0;
        int RunFramesPassed = 0;
        float RunVelocity = 0;
        float RunAcceleration = 1;

		//Character Walk
		int WalkFramesPassed = 0;
		int WalkIndex = 0;
		int WalkIndexLimit = 0;
		float WalkVelocity = 0;
		float WalkAcceleration = 1;

    public:
        //Character
	    sf::Sprite sprite;
	    sf::Vector2f IntialPosition;
	    sf::Sprite Preview;
	    sf::Texture PreviewTexture;
	    sf::Texture DieTexture;
		sf::Texture WinTexture;

        bool IsJump = false;
		bool IsWalk = false;
        bool IsRuning = true;
        bool IsGameOver = false;
		bool IsWin = false;
        bool GameMode = false;
        bool IsFast = false;
        float Ground = 555;
	    sf::Clock GameOverTime;
		sf::Clock WinTime;
	
        //Score
        sf::Clock ScoreTimer;
        sf::Text ScoreText;
        int Score = 0;
        float IntialScore = 0;
        sf::Clock SpeedTimer;

        //GameOver
        float GameOverVelocity = 25;
        float GameOverAcceleration = 1.f;
        sf::Text Game, Over;
        sf::Font font;

		//Win
        float WinVelocity = 25;
        float WinAcceleration = 1.f;
        sf::Text You, Win;

        void Intialize(sf::RenderWindow& window, std::string CharacterName)
        {
            if (CharacterName == "man")
            {
                JumpIndexLimit = 11;
                RunIndexLimit = 15;
				WalkIndexLimit = 15;
                Preview.setPosition(window.getSize().x / 2.6, window.getSize().y / 3);
            }
            if(CharacterName == "girl")
            {
                JumpIndexLimit = 10;
                RunIndexLimit = 8;
				WalkIndexLimit = 8;
                Preview.setPosition(window.getSize().x / 2.6, window.getSize().y / 3);
            }
            if(CharacterName == "boy")
            {
                JumpIndexLimit = 15;
                RunIndexLimit = 15;
				WalkIndexLimit = 15;
                Preview.setPosition(window.getSize().x / 2.6, window.getSize().y / 3);
            }
            if(CharacterName == "cuteGirl")
            {
                JumpIndexLimit = 30;
                RunIndexLimit = 20;
				WalkIndexLimit = 20;
                Preview.setPosition(window.getSize().x / 2.6, window.getSize().y / 3);
            }

            font.loadFromFile("res/Fonts/arial.ttf");
            ScoreText.setFont(font);
			ScoreText.setFillColor(sf::Color::Black);
            ScoreText.setPosition(window.getSize().x / 1.15, 25);

            Game.setString("Game");
            Game.setFont(font);
            Game.scale(2.5f, 2.5f);
            Game.setPosition(-(Game.getGlobalBounds().width + 5), window.getSize().y / 2);

            Over.setPosition(window.getSize().x, window.getSize().y / 2);
            Over.setString("Over");
            Over.setFont(font);
            Over.scale(2.5f, 2.5f);

			You.setString("You");
            You.setFont(font);
            You.scale(2.5f, 2.5f);
            You.setPosition(-(You.getGlobalBounds().width + 5), window.getSize().y / 2);

            Win.setPosition(window.getSize().x, window.getSize().y / 2);
            Win.setString("Win");
            Win.setFont(font);
            Win.scale(2.5f, 2.5f);

            IntialPosition.x = 110;
            IntialPosition.y = Ground;

            for (int i = 0; i < JumpIndexLimit; i++)
            {
                JumpTexture[i].loadFromFile("res/Textures/"+ CharacterName +"Jump" + std::to_string(i + 1) + ".png");
            }
            for (int i = 0; i < RunIndexLimit; i++)
            {
                RunTexture[i].loadFromFile("res/Textures/" + CharacterName + "Run" + std::to_string(i + 1) + ".png");
            }
			for (int i = 0; i < WalkIndexLimit; i++)
            {
                WalkTexture[i].loadFromFile("res/Textures/" + CharacterName + "Run" + std::to_string(i + 1) + ".png");
            }
            
            DieTexture.loadFromFile("res/Textures/" + CharacterName +"Die.png");
			WinTexture.loadFromFile("res/Textures/" + CharacterName +"Win.png");
            PreviewTexture.loadFromFile("res/Textures/" + CharacterName + ".png");
            Preview.setTexture(PreviewTexture);
            Preview.setScale(3, 3);
			sprite.setPosition(IntialPosition);
            sprite.setScale(0.3,0.3);
        }

        void Jump(sf::RenderWindow& window, OurMusic& CharacterMusic)
        {
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))  && sprite.getPosition().y >= Ground && !IsGameOver &&!IsWin && !GameMode) 
			{
				IsJump = true;
				IsRuning = false;
				CharacterMusic.SoundEffects("res/Audio/Jump.WAV");
			}

			if (Reset)
			{
				JumpVelocityY = 20;
				JumpDecceleration = 1.f;
				GravitionalAcc = 1.7f;
				Reset = false;
			}

			//Moves the Character forward if his x postion is less than 700
			if (sprite.getPosition().x <  window.getSize().x - 200 && sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !IsGameOver && !IsWin)
			{
				CanMove = true;
			}
			else 
			{ 
				CanMove = false; 
			}
		
			if (IsJump)
			{
				sprite.move(0.0f, -JumpVelocityY);
				JumpVelocityY -= JumpDecceleration;
				JumpVelocityX -= JumpDecceleration;
				
				if (CanMove && JumpVelocityX > 0)
				{
					sprite.move(JumpVelocityX, 0.f);
				}

				if (JumpVelocityY < 0)
				{
					IsJump = false;
					Gravity = true;
					JumpVelocityY = 0;
				}

				// //if the S key is pressed the gravity is turned on by force before reaching maximun height
				// if ((sprite.getPosition().y <= JumpHeight) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) 
				// {
				// 	IsJump = false;
				// 	Gravity = true;
				// 	JumpVelocityY = 0;
				// }
			}
			if ((Gravity || IsJump))
			{
				JumpFramesPassed++;
				if (JumpFramesPassed == 3)
				{
					sprite.setTexture(JumpTexture[JumpIndex]);
					JumpIndex++;
					if (JumpIndex >= JumpIndexLimit)
					{
						JumpIndex = 0;
					}
					JumpFramesPassed = 0;
				}
			}
			if (Gravity && IsJump == false)
			{
				sprite.move(0.0f, JumpVelocityY);
				JumpVelocityY += GravitionalAcc;
				// increases Gravity if S is being held
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					JumpVelocityY += JumpDecceleration * 2;
				}
				if (CanMove)
				{
					sprite.move(10, 0);
				}
				// turns off gravity and resets intial velocity an position
				if (sprite.getPosition().y >= Ground) 
				{
					Gravity = false;
					JumpVelocityY = 20;
					JumpVelocityX = 20;
					sprite.setPosition(sprite.getPosition().x, Ground);
				}
			}
		}

		void Run(sf::RenderWindow& window)
		{

			// Resets the velocity if D is not pressed or the character is walking or jumping (Not Running)
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D) || !IsRuning)
			{
				RunVelocity = 0;
			}
			if (sprite.getPosition().y >= Ground && IsRuning)
			{
				//Move Forward if D is pressed and the GameMode is off
				if (sprite.getPosition().x <= window.getSize().x - 200 && sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !GameMode)
				{
					sprite.move(RunVelocity, 0);
					RunVelocity += RunAcceleration;
				}

				RunFramesPassed++;
				if (RunFramesPassed == 1)
				{
					sprite.setTexture(RunTexture[RunIndex]);
					RunIndex++;
					if (RunIndex >= RunIndexLimit)
					{
						RunIndex = 0;
					}
					RunFramesPassed = 0;
				}
			}
		}

		void Walk()
		{
			//Character Walk
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && !IsGameOver && !IsWin)
			{
				IsWalk = true;
				IsRuning = false;
			}
			else
			{
				IsWalk = false;
				IsRuning = true;
			}

			if (sprite.getPosition().y >= Ground && IsWalk && !GameMode)
			{
				// Moves Backwards
				if (sprite.getPosition().x > 112.5 && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					sprite.move(-WalkVelocity, 0);
					WalkVelocity += WalkAcceleration;
				}
				WalkFramesPassed++;
				if (WalkFramesPassed == 3)
				{
					sprite.setTexture(WalkTexture[WalkIndex]);
					WalkIndex++;
					if (WalkIndex >= WalkIndexLimit)
					{
						WalkIndex = 0;
					}
					WalkFramesPassed = 0;
				}
			}
			// resets velocity if the character is not walking or it has reached the far left of the screen
			if (!IsWalk || sprite.getPosition().x <= 112.5 || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				WalkVelocity = 0;
			}
		}

		void CheckIfGameOver(sf::RenderWindow& window, OurMusic& GameMusic, Background& GameBackground, Obstacle& GameObstacles, Menus& GameState,LeaderBoard& GameLeaderBoards)
		{
			if (IsGameOver)
			{
				sprite.setTexture(DieTexture);
				sprite.move(0, -GameOverVelocity);
				GameOverVelocity -= GameOverAcceleration;
				JumpVelocityY = 0;
				GravitionalAcc = 0;
				JumpDecceleration = 0;
				IsJump = false;
				Reset = true;
			}
			else
			{
				GameOverVelocity = 25;
				GameOverAcceleration = 1.f;
			}

			if (!IsGameOver)
			{
				GameOverTime.restart();
			}
			else if (GameOverTime.getElapsedTime().asSeconds() > 4.2 || sf::Keyboard::isKeyPressed(sf::Keyboard::R) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				GameBackground.ResetSpeed();
				GameObstacles.Reset(window);
				Game.setPosition(-(Game.getGlobalBounds().width + 5), window.getSize().y / 2);
				Over.setPosition(window.getSize().x, window.getSize().y / 2);
				IsGameOver = false;
				GameMusic.CreditsMusic = false;
				IsFast = false;
				IsRuning = false;
				sprite.setPosition(IntialPosition);
				if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::R)))
				{
					GameLeaderBoards.getScore(window, Score);
					GameState.Start = false;
					GameState.Menu = true;
					GameMusic.MusicChanged = true;
					GameState.InGame = false;
				}
				if ((sf::Keyboard::isKeyPressed(sf::Keyboard::R)))
				{
					GameMusic.BackgroundMusic("Audio/" + std::to_string(GameMusic.CurrentMusic) + ".wav");
				}
				Score = 0;
				IntialScore = 0;
			}
			else if (Game.getPosition().x<(window.getSize().x / 2) - Game.getGlobalBounds().width - 15)
			{
				Over.move(-6, 0);
				Game.move(6, 0);
			}
		}

		void CheckIfWin(sf::RenderWindow& window, OurMusic& GameMusic, Background& GameBackground, Obstacle& GameObstacles, Menus& GameState,LeaderBoard& GameLeaderBoards)
		{
			if (IsWin)
			{
				sprite.setTexture(WinTexture);
				sprite.move(0, -WinVelocity);
				WinVelocity -= WinAcceleration;
				JumpVelocityY = 0;
				GravitionalAcc = 0;
				JumpDecceleration = 0;
				IsJump = false;
				Reset = true;
			}
			else
			{
				WinVelocity = 25;
				WinAcceleration = 1.f;
			}

			if (!IsWin)
			{
				WinTime.restart();
			}
			else if (WinTime.getElapsedTime().asSeconds() > 4.2 || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				GameBackground.ResetSpeed();
				GameObstacles.Reset(window);
				You.setPosition(-(You.getGlobalBounds().width + 5), window.getSize().y / 2);
				Win.setPosition(window.getSize().x, window.getSize().y / 2);
				IsWin = false;
				GameMusic.CreditsMusic = false;
				IsFast = false;
				IsRuning = false;
				sprite.setPosition(IntialPosition);
				if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::R)))
				{
					GameLeaderBoards.getScore(window, Score);
					GameState.Start = false;
					GameState.Menu = true;
					GameMusic.MusicChanged = true;
					GameState.InGame = false;
				}
				if ((sf::Keyboard::isKeyPressed(sf::Keyboard::R)))
				{
					GameMusic.BackgroundMusic("Audio/" + std::to_string(GameMusic.CurrentMusic) + ".wav");
				}
				Score = 0;
				IntialScore = 0;
			}
			else if (You.getPosition().x<(window.getSize().x / 2) - You.getGlobalBounds().width - 15)
			{
				Win.move(-6, 0);
				You.move(6, 0);
			}
		}

		// void CheckIfBossOver(OurMusic&GameMusic, sf::RenderWindow& window, Background& GameBackground, Obstacle& GameObstacles, Menus& GameState, LeaderBoard& GameLeaderBoards)
		// {
		// 	if (IsGameOver)
		// 	{
		// 		sprite.setTexture(DieTexture);
		// 		sprite.move(0, -GameOverVelocity);
		// 		GameOverVelocity -= GameOverAcceleration;
		// 		JumpVelocityY = 0;
		// 		GravitionalAcc = 0;
		// 		JumpDecceleration = 0;
		// 		IsJump = false;
		// 		Reset = true;
		// 	}
		// 	else
		// 	{
		// 		GameOverVelocity = 25;
		// 		GameOverAcceleration = 1.f;
		// 	}

		// 	if (!IsGameOver)
		// 	{
		// 		GameOverTime.restart();
		// 	}
		// 	else if (GameOverTime.getElapsedTime().asSeconds()>4.2 || sf::Keyboard::isKeyPressed(sf::Keyboard::R) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		// 	{
		// 		GameObstacles.Reset(window);
		// 		GameBackground.ResetSpeed();
		// 		Game.setPosition(-(Game.getGlobalBounds().width + 5), window.getSize().y / 2);
		// 		Over.setPosition(window.getSize().x, window.getSize().y / 2);
		// 		IsGameOver = false;
		// 		GameMusic.CreditsMusic = false;
		// 		IsFast = false;
		// 		IsRuning = false;
		// 		sprite.setPosition(IntialPosition);
		// 		if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::R)))
		// 		{
		// 			GameLeaderBoards.getScore(window, Score);
		// 			GameState.Start = false;
		// 			GameState.Menu = true;
		// 			GameMusic.MusicChanged = true;
		// 			GameState.InGame = false;
		// 		}
		// 		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::R)))
		// 		{
		// 			GameMusic.BackgroundMusic("res/Audio/" + std::to_string(GameMusic.CurrentMusic) + ".wav");
		// 			GameState.Start = true;
		// 		}
		// 		Score = 0;
		// 		IntialScore = 0;
		// 	}
		// 	else if (Game.getPosition().x<(window.getSize().x / 2) - Game.getGlobalBounds().width - 15)
		// 	{
		// 		Over.move(-6, 0);
		// 		Game.move(6, 0);
		// 	}
		// }

		void CheckIfGameModeOver(Mode& EggManMode, sf::RenderWindow& window, OurMusic& GameMusic, Background& GameBackground, Obstacle& GameObstacles, Menus& GameState, LeaderBoard& GameLeaderBoards)
		{
			if (IsGameOver)
			{
				sprite.setTexture(DieTexture);
				sprite.move(0, -GameOverVelocity);
				GameOverVelocity -= GameOverAcceleration;
				JumpVelocityY = 0;
				GravitionalAcc = 0;
				JumpDecceleration = 0;
				IsJump = false;
				Reset = true;
			}
			else
			{
				GameOverVelocity = 25;
				GameOverAcceleration = 1.f;
			}

			if (!IsGameOver)
			{
				GameOverTime.restart();
			}
			else if (GameOverTime.getElapsedTime().asSeconds()>4.2 || sf::Keyboard::isKeyPressed(sf::Keyboard::R) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				GameMode = false;
				IsGameOver = false;
				EggManMode.Reset(window);
				GameObstacles.Reset(window);
				Game.setPosition(-(Game.getGlobalBounds().width + 5), window.getSize().y / 2);
				Over.setPosition(window.getSize().x, window.getSize().y / 2);
				GameBackground.ResetSpeed();
				GameMusic.CreditsMusic = false;
				IsFast = false;
				
				sprite.setPosition(IntialPosition);
				if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::R)))
				{
					GameLeaderBoards.getScore(window, Score);
					GameMusic.MusicChanged = true;
					GameState.Menu = true;
					GameState.InGame = false;
				}
				if ((sf::Keyboard::isKeyPressed(sf::Keyboard::R)))
				{
					GameMusic.BackgroundMusic("res/Audio/" + std::to_string(GameMusic.CurrentMusic) + ".wav");
					GameState.Start = true;
				}
				Score = 0;
				IntialScore = 0;
			}
			else if (Game.getPosition().x<(window.getSize().x / 2) - Game.getGlobalBounds().width - 15)
			{
				Over.move(-6, 0);
				Game.move(6, 0);
			}

			if (IsWin)
			{
				sprite.setTexture(WinTexture);
				sprite.move(0, -WinVelocity);
				WinVelocity -= WinAcceleration;
				JumpVelocityY = 0;
				GravitionalAcc = 0;
				JumpDecceleration = 0;
				IsJump = false;
				Reset = true;
			}
			else
			{
				WinVelocity = 25;
				WinAcceleration = 1.f;
			}

			if (!IsWin)
			{
				WinTime.restart();
			}
			else if (WinTime.getElapsedTime().asSeconds()>4.2 || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				GameMode = false;
				IsWin = false;
				EggManMode.Reset(window);
				GameObstacles.Reset(window);
				You.setPosition(-(You.getGlobalBounds().width + 5), window.getSize().y / 2);
				Win.setPosition(window.getSize().x, window.getSize().y / 2);
				GameBackground.ResetSpeed();
				GameMusic.CreditsMusic = false;
				IsFast = false;
				
				sprite.setPosition(IntialPosition);
				if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::R)))
				{
					GameLeaderBoards.getScore(window, Score);
					GameMusic.MusicChanged = true;
					GameState.Menu = true;
					GameState.InGame = false;
				}
				if ((sf::Keyboard::isKeyPressed(sf::Keyboard::R)))
				{
					GameMusic.BackgroundMusic("res/Audio/" + std::to_string(GameMusic.CurrentMusic) + ".wav");
					GameState.Start = true;
				}
				Score = 0;
				IntialScore = 0;
			}
			else if (You.getPosition().x<(window.getSize().x / 2) - You.getGlobalBounds().width - 15)
			{
				Win.move(-6, 0);
				You.move(6, 0);
			}
		}
};