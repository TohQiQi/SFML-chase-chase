#include"RequiredHeaders.h"

bool DetectCollision(sf::Sprite& Object1, sf::Sprite& Object2)
{
	if (Object1.getGlobalBounds().intersects(Object2.getGlobalBounds()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void main()
{
	
	sf::RenderWindow window(sf::VideoMode(1440,900), "WillPower", sf::Style::Fullscreen);
	//GameWindow.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	//Characters
	Character man;
	man.Intialize(window,"man");
	
    Character girl;
	girl.Intialize(window, "girl");

	Character boy;
	boy.Intialize(window, "boy");

    Character cuteGirl;
	cuteGirl.Intialize(window, "cuteGirl");

	Character* CharacterPointer = &man;

	//Music
	OurMusic GameMusic;
	GameMusic.Intialize();

	//Background
	Background GameBackground;
	GameBackground.Intialize(window);

	//Obstacles
	Obstacle GameObstacles;
	GameObstacles.Intialize(window);

	//Menus
	Menus GameState;
	GameState.Intialize((*CharacterPointer).font, window);

	//Controls Sonic
	Character ControlsMan;
	ControlsMan.Intialize(window,"man");

	//EggMan
	Mode EggManMode;
	EggManMode.Intialize(window);

	LeaderBoard GameLeaderBoards;
	GameLeaderBoards.Init();

	int CharcterSelect=0;

	GameMusic.BackgroundMusic("res/Audio/0.WAV");
	
	//character sprite
	sf::Texture John;
	sf::Sprite JohnSprite;
	sf::Texture Emily;
	sf::Sprite EmilySprite;
	sf::Texture Peter;
	sf::Sprite PeterSprite;
	sf::Texture May;
	sf::Sprite MaySprite;
	sf::Texture Shuzak;
	sf::Sprite ShuzakSprite;

	while (window.isOpen())
	{
		sf::Event GameEvent;
		while (window.pollEvent(GameEvent))
		{
			if (GameEvent.type == sf::Event::Closed)
				window.close();

			if (GameEvent.type == GameEvent.KeyReleased && GameEvent.key.code == sf::Keyboard::M)
			{
				GameMusic.CurrentMusic++;
				if (GameMusic.CurrentMusic > 9)
				{
					GameMusic.CurrentMusic = 0;
				}
				GameMusic.BackgroundMusic("res/Audio/" + std::to_string(GameMusic.CurrentMusic) + ".wav");
			}
			// eggman
			if (GameEvent.type == GameEvent.KeyReleased && GameEvent.key.code == sf::Keyboard::G && GameState.Start)
			{
				(*CharacterPointer).GameMode = true;
				GameState.Start = false;
				GameMusic.BackgroundMusic("res/Audio/RunEdited.wav");
			}
		}

		if (GameState.Menu)
		{
			GameState.MainMenu((*CharacterPointer).GameMode, window, GameMusic, GameBackground, GameLeaderBoards);
		}
		if (GameState.CharacterSelect)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				GameState.CharacterSelect = false;
				GameState.Menu = true;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && GameState.PressTimer.getElapsedTime().asSeconds() > 0.24)
			{
				CharcterSelect++;
				GameState.PressTimer.restart();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && GameState.PressTimer.getElapsedTime().asSeconds() > 0.24)
			{
				CharcterSelect--;
				GameState.PressTimer.restart();
			}

			if (CharcterSelect > 3)
			{
				CharcterSelect = 0;
			}
			if (CharcterSelect < 0)
			{
				CharcterSelect = 3;
			}

			switch (CharcterSelect)
			{
			case 0:
				CharacterPointer = &man;
				break;
			case 1:
				CharacterPointer = &girl;
				break;
			case 2:
				CharacterPointer = &boy;
				break;
            case 3:
				CharacterPointer = &cuteGirl;
				break;
			}

			if (GameEvent.type == GameEvent.KeyReleased && GameEvent.key.code == sf::Keyboard::Space)
			{
				GameState.CharacterSelect = false;
				GameState.InGame = true;
				GameState.Start = true;
			}

			window.clear();
			window.draw((*CharacterPointer).Preview);
			window.draw(GameState.SelectPlayer);
			window.draw(GameState.Choose);
			window.display();
		}
		if (GameState.Controls)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				GameState.Controls = false;
				GameState.Menu = true;
			}

			ControlsMan.Run(window);
			ControlsMan.Jump(window, GameMusic);
			ControlsMan.Walk();

			//John sprite
			John.loadFromFile("res/Textures/john.png");
            JohnSprite.setTexture(John);
			JohnSprite.setPosition(100, 500);
			JohnSprite.setScale(0.3f, 0.3f);

			//Emily sprite
			Emily.loadFromFile("res/Textures/emily.png");
            EmilySprite.setTexture(Emily);
			EmilySprite.setPosition(300, 500);
			EmilySprite.setScale(0.3f, 0.3f);

			//Peter sprite
			Peter.loadFromFile("res/Textures/peter.png");
            PeterSprite.setTexture(Peter);
			PeterSprite.setPosition(520, 500);
			PeterSprite.setScale(0.3f, 0.3f);

			//May sprite
			May.loadFromFile("res/Textures/may.png");
            MaySprite.setTexture(May);
			MaySprite.setPosition(700, 500);
			MaySprite.setScale(0.3f, 0.3f);

			//Shuzak sprite
			Shuzak.loadFromFile("res/Textures/shuzak.png");
            ShuzakSprite.setTexture(Shuzak);
			ShuzakSprite.setPosition(900, 450);
			ShuzakSprite.setScale(0.3f, 0.3f);

			//Character Walk
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					GameState.Buttons[0].setTexture(GameState.ButtonsTexture[1]);
				}
				else
				{
					GameState.Buttons[4].setTexture(GameState.ButtonsTexture[9]);
				}
			}
			else
			{
				GameState.Buttons[0].setTexture(GameState.ButtonsTexture[0]);
				GameState.Buttons[4].setTexture(GameState.ButtonsTexture[8]);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				GameState.Buttons[1].setTexture(GameState.ButtonsTexture[3]);
			}
			else
			{
				GameState.Buttons[1].setTexture(GameState.ButtonsTexture[2]);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				GameState.Buttons[5].setTexture(GameState.ButtonsTexture[11]);
			}
			else
			{
				GameState.Buttons[5].setTexture(GameState.ButtonsTexture[10]);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				GameState.Buttons[3].setTexture(GameState.ButtonsTexture[7]);
			}
			else
			{
				GameState.Buttons[3].setTexture(GameState.ButtonsTexture[6]);
			}

            //pause screen
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				GameState.Buttons[2].setTexture(GameState.ButtonsTexture[5]);
			}
			else
			{
				GameState.Buttons[2].setTexture(GameState.ButtonsTexture[4]);
			}

			window.clear();

			for (int i = 0; i < 6; i++)
			{
				window.draw(GameState.Buttons[i]);
			}
			window.draw(GameState.Intructions);
			// window.draw(ControlsMan.sprite);
			window.draw(JohnSprite);
			window.draw(EmilySprite);
			window.draw(PeterSprite);
			window.draw(MaySprite);
			window.draw(ShuzakSprite);
			window.display();
		}

		if (GameState.Story)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				GameState.Story = false;
				GameState.Menu = true;
			}

			ControlsMan.Run(window);
			ControlsMan.Jump(window, GameMusic);
			ControlsMan.Walk();

			//Character Walk
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					GameState.Buttons[0].setTexture(GameState.ButtonsTexture[1]);
				}
				else
				{
					GameState.Buttons[4].setTexture(GameState.ButtonsTexture[9]);
				}
			}
			else
			{
				GameState.Buttons[0].setTexture(GameState.ButtonsTexture[0]);
				GameState.Buttons[4].setTexture(GameState.ButtonsTexture[8]);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				GameState.Buttons[1].setTexture(GameState.ButtonsTexture[3]);
			}
			else
			{
				GameState.Buttons[1].setTexture(GameState.ButtonsTexture[2]);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				GameState.Buttons[5].setTexture(GameState.ButtonsTexture[11]);
			}
			else
			{
				GameState.Buttons[5].setTexture(GameState.ButtonsTexture[10]);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				GameState.Buttons[3].setTexture(GameState.ButtonsTexture[7]);
			}
			else
			{
				GameState.Buttons[3].setTexture(GameState.ButtonsTexture[6]);
			}

            //pause screen
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				GameState.Buttons[2].setTexture(GameState.ButtonsTexture[5]);
			}
			else
			{
				GameState.Buttons[2].setTexture(GameState.ButtonsTexture[4]);
			}

			window.clear();

			for (int i = 0; i < 6; i++)
			{
				window.draw(GameState.Buttons[i]);
			}
			window.draw(GameState.BackgroundStory);
			window.draw(ControlsMan.sprite);
			window.display();
		}

		if (GameState.Credits)
		{
			GameState.GameCredtis(window);
		}

		if ((*CharacterPointer).GameMode)
		{
            // pause
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				(*CharacterPointer).GameMode = false;
				GameState.IsGameMode = true;
				GameState.Menu = true;
			}

			if (DetectCollision((*CharacterPointer).sprite, GameObstacles.Obstacles[1]))
			{
				GameObstacles.Obstacles[1].setPosition(-150, 500);
				(*CharacterPointer).Score += 50;
				GameMusic.SoundEffects("res/Audio/Destroy.WAV");
			}

			// Continue the Following Actions if Active to prevent the Game from Hanging Up
			(*CharacterPointer).Jump(window, GameMusic);
			(*CharacterPointer).Walk();

			// Turn on Running and off Walking if it was Active
			(*CharacterPointer).IsRuning = true;
			(*CharacterPointer).IsWalk = false;

			// Run Animation and Moving Background
			(*CharacterPointer).Run(window);

			// Continue Moving the Obstacles until they get OffScreen 
			GameObstacles.GenerateObstacles(window, (*CharacterPointer).IsGameOver, (*CharacterPointer).IsWin, (*CharacterPointer).GameMode);

			// Check the Characters Position Before showing the Spikes and the Enemy
			if ((*CharacterPointer).sprite.getPosition().x <= 140 && !(*CharacterPointer).IsGameOver && !(*CharacterPointer).IsWin)
			{
				EggManMode.InPosition = true;
			}
			else if (!EggManMode.InPosition && !(*CharacterPointer).IsGameOver && !(*CharacterPointer).IsWin)
			{
				(*CharacterPointer).sprite.move(-2, 0);
			}

			// Checks if the Enemy is Destroyed for the GameMode to End
			if (EggManMode.Destroyed)
			{
				// Moves the Spikes out of the Screen and the character Backwards
				if (EggManMode.SpikeWall.getPosition().x > -160)
				{
					EggManMode.SpikeWall.move(-1, 0);
				}
				else
				{
					// turns off the GameMode
					(*CharacterPointer).GameMode = false;
					GameState.Start = true;
					EggManMode.Destroyed = false;
					if (!(*CharacterPointer).IsFast)
					{
						GameMusic.BackgroundMusic("res/Audio/" + std::to_string(GameMusic.CurrentMusic) + ".WAV");
					}
					else
					{
						GameMusic.BackgroundMusic("res/Audio/ContinueFast.WAV");
					}
				}
			}

			// Show the Spikes and the Enemy if the Charater is in postion (at the Back)
			if (EggManMode.InPosition)
			{
				//Moves the Enemy and the spikes into the screen
				if (EggManMode.Enemy.getPosition().x > window.getSize().x - 130)
				{
					EggManMode.Enemy.move(-3, 0);
				}

				if (EggManMode.SpikeWall.getPosition().x <= -5)
				{
					EggManMode.SpikeWall.move(1, 0);
				}

				//Jumps Automatically if Near the Enemy
				if ((*CharacterPointer).sprite.getPosition().x >= EggManMode.Enemy.getPosition().x - 50 && (*CharacterPointer).sprite.getPosition().y >= (*CharacterPointer).Ground)
				{
					(*CharacterPointer).IsJump = true;
					GameMusic.SoundEffects("res/Audio/Jump.WAV");
				}

				//Moves the character Backwards
				if (EggManMode.StartMovement && !(*CharacterPointer).IsGameOver && !(*CharacterPointer).IsWin)
				{
					(*CharacterPointer).sprite.move(-2, 0);
				}

				// Changes the Arrow Every (Interval) Currently set to 1 second
				if (EggManMode.ArrowTimer.getElapsedTime().asSeconds() >= EggManMode.Interval)
				{
					// prevents Arrow Repetition
					EggManMode.PerviousArrow = EggManMode.RandomArrow;
					EggManMode.RandomArrow = rand() % 4;
					while (EggManMode.PerviousArrow == EggManMode.RandomArrow)
					{
						EggManMode.RandomArrow = rand() % 4;
					}

					// sets the arrow texture Randomly
					switch (EggManMode.RandomArrow)
					{
					case 0:
						EggManMode.Arrow.setTexture(EggManMode.ArrowTexture[0]);
						break;
					case 1:
						EggManMode.Arrow.setTexture(EggManMode.ArrowTexture[1]);
						break;
					case 2:
						EggManMode.Arrow.setTexture(EggManMode.ArrowTexture[2]);
						break;
					case 3:
						EggManMode.Arrow.setTexture(EggManMode.ArrowTexture[3]);
						break;
					}

					for (int i = 0; i < 4; i++)
					{
						EggManMode.IsPressed[i] = false;
					}

					// Resets the interval to 1 and restarts the clock
					EggManMode.Interval = 1;
					EggManMode.ArrowTimer.restart();
				}

				// Moves the Character forward for 0.7 seconds (MoveTime) if the arrow is Hit
				if (EggManMode.Move && EggManMode.MoveTime.getElapsedTime().asSeconds()< 0.7)
				{
					(*CharacterPointer).sprite.move(4, 0);
				}
				else
				{
					EggManMode.MoveTime.restart();
					EggManMode.Move = false;
				}

				if (EggManMode.MoveBack && EggManMode.MoveBackTime.getElapsedTime().asSeconds()< 0.7 && !(*CharacterPointer).IsGameOver && !(*CharacterPointer).IsWin)
				{
					(*CharacterPointer).sprite.move(-4, 0);
					(*CharacterPointer).Score -= 7;
				}
				else
				{
					EggManMode.MoveBackTime.restart();
					EggManMode.MoveBack = false;
				}

				// Checks for arrow presses and turns on the corresponding boolean
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && EggManMode.CanPressTimer.getElapsedTime().asSeconds()>0.3) 
				{
					EggManMode.IsPressed[0] = true;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && EggManMode.CanPressTimer.getElapsedTime().asSeconds()>0.3) 
				{
					EggManMode.IsPressed[1] = true;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && EggManMode.CanPressTimer.getElapsedTime().asSeconds()>0.3) 
				{
					EggManMode.IsPressed[2] = true;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && EggManMode.CanPressTimer.getElapsedTime().asSeconds()>0.3) 
				{
					EggManMode.IsPressed[3] = true;
				}


				for (int i = 0; i<4; i++)
				{
					//Turns the bool (Move) on to move the character and arrow bool off
					if (EggManMode.IsPressed[i] && EggManMode.RandomArrow == i)
					{
						EggManMode.Arrow.setTexture(EggManMode.ArrowTexture[i + 4]);
						EggManMode.IsPressed[i] = false;
						EggManMode.Move = true;
						(*CharacterPointer).Score += 10;
						if ((*CharacterPointer).IsFast)
						{
							GameObstacles.Speed -= 0.5;
							GameBackground.TracksSpeed /= 1.15;
							GameBackground.BackgroundSpeed /= 1.15;
						}
						EggManMode.StartMovement = true;

						// the interval that the green arrow stays on screen
						EggManMode.Interval = 0.3;
						EggManMode.ArrowTimer.restart();
						EggManMode.CanPressTimer.restart();
					}
					else if (!EggManMode.Move && EggManMode.IsPressed[i] && EggManMode.RandomArrow != i)
					{
						EggManMode.MoveBack = true;
					}
				}


				//checks if the Enemy is destroyed to stop the Gamemode
				if (DetectCollision((*CharacterPointer).sprite, EggManMode.Enemy))
				{
					EggManMode.Enemy.setPosition(window.getSize().x + 50, 350);
					GameMusic.SoundEffects("res/Audio/Destroy.WAV");
					EggManMode.InPosition = false;
					EggManMode.StartMovement = false;
					EggManMode.Destroyed = true;
					(*CharacterPointer).IsWin = true;
				}
				if (DetectCollision(EggManMode.SpikeWall, (*CharacterPointer).sprite))
				{
					GameBackground.ZeroSpeed();
					EggManMode.StartMovement = false;
					EggManMode.InPosition = false;
					(*CharacterPointer).IsGameOver = true;
					GameMusic.BackgroundMusic("res/Audio/GameOver.wav");
				}
			}

			(*CharacterPointer).ScoreText.setString("Score: " + std::to_string((*CharacterPointer).Score));
			GameBackground.Parallex(window);
			

			// draw
			window.clear();
			GameBackground.Draw(window);

			GameObstacles.Draw(window);
			window.draw((*CharacterPointer).sprite);
			EggManMode.Draw(window);
			window.draw((*CharacterPointer).Game);
			window.draw((*CharacterPointer).Over);
			window.draw((*CharacterPointer).You);
			window.draw((*CharacterPointer).Win);
			window.draw((*CharacterPointer).ScoreText);

			//display
			window.display();

			(*CharacterPointer).CheckIfGameModeOver(EggManMode, window, GameMusic, GameBackground, GameObstacles, GameState, GameLeaderBoards);
			
		}

		if (GameState.Start)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				GameState.Start = false;
				GameState.Menu = true;
			}

			if (!(*CharacterPointer).IsGameOver && !(*CharacterPointer).IsWin)
			{
				//Character Run
				(*CharacterPointer).Run(window);
				//Character jump
				(*CharacterPointer).Jump(window,GameMusic);
				//character walk
				(*CharacterPointer).Walk();
			}

			
			for (int i = 0; i < 2; i++)
			{
				if (DetectCollision((*CharacterPointer).sprite, GameObstacles.Obstacles[i]))
				{
					if (i == 0 && !(*CharacterPointer).IsGameOver)
					{
						GameMusic.BackgroundMusic("res/Audio/GameOver.wav");
						GameBackground.ZeroSpeed();
						(*CharacterPointer).IsGameOver = true;
					}
					if (i == 1 && !(*CharacterPointer).IsGameOver)
					{
						GameObstacles.Obstacles[i].setPosition(-150, 500);
						(*CharacterPointer).Score += 50;
						GameMusic.SoundEffects("res/Audio/Destroy.WAV");
					}
				}
			}
			

			GameBackground.Parallex(window);
			GameObstacles.GenerateObstacles(window, (*CharacterPointer).IsGameOver, (*CharacterPointer).IsWin, (*CharacterPointer).GameMode);
			
			//draw
			window.clear();

			GameBackground.Draw(window);
			GameObstacles.Draw(window);

			window.draw((*CharacterPointer).ScoreText);
			window.draw((*CharacterPointer).Game);
			window.draw((*CharacterPointer).Over);
			window.draw((*CharacterPointer).sprite);

			if ((*CharacterPointer).ScoreTimer.getElapsedTime().asSeconds() > 0.1 && !(*CharacterPointer).IsGameOver && !(*CharacterPointer).IsWin)
			{
				(*CharacterPointer).ScoreTimer.restart();
				(*CharacterPointer).Score++;
			}
			(*CharacterPointer).ScoreText.setString("Score: " + std::to_string((*CharacterPointer).Score));
			if ((*CharacterPointer).Score % 300 == 0 && (*CharacterPointer).SpeedTimer.getElapsedTime().asSeconds() > 0.1)
			{
				GameObstacles.Speed += 4;
				if (!(*CharacterPointer).IsFast)
				{
					GameBackground.TracksSpeed *= 1.35;
					GameBackground.BackgroundSpeed *= 1.35;
				}
				(*CharacterPointer).SpeedTimer.restart();
				if (GameObstacles.Speed >= 34 && !(*CharacterPointer).IsFast)
				{
					GameMusic.BackgroundMusic("res/Audio/ContinueFast.wav");
					(*CharacterPointer).IsFast = true;
				}
			}

			if (GameObstacles.Speed <= 25 && (*CharacterPointer).IsFast)
			{
				GameMusic.BackgroundMusic("res/Audio/" + std::to_string(GameMusic.CurrentMusic) + ".wav");
				(*CharacterPointer).IsFast = false;
			}



			if ((*CharacterPointer).Score - (*CharacterPointer).IntialScore >= 1000)
			{
				GameObstacles.Speed += 0.02;
			}

			if ((*CharacterPointer).Score - (*CharacterPointer).IntialScore >= 1300 && GameObstacles.Obstacles[0].getPosition().x<-150)
			{
				(*CharacterPointer).IntialScore = (*CharacterPointer).Score * 1.2;
				GameState.Start = false;
				(*CharacterPointer).GameMode = true;
				GameMusic.BackgroundMusic("audio/5.wav");
			}

			// if ((*CharacterPointer).Score - (*CharacterPointer).IntialScore >= 2000 && GameObstacles.Obstacles[1].getPosition().x<-150)
			// {
			// 	GameState.Start = false;
			// 	(*CharacterPointer).GameMode = true;
			// 	GameMusic.BackgroundMusic("audio/5.wav");
			// }

			//display
			window.display();
			(*CharacterPointer).CheckIfGameOver(window, GameMusic, GameBackground, GameObstacles, GameState, GameLeaderBoards);
			(*CharacterPointer).CheckIfWin(window, GameMusic, GameBackground, GameObstacles, GameState, GameLeaderBoards);
		}
	}
}