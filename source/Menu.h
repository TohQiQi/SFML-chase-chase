#pragma once

#include"RequiredHeaders.h"
#include"LeaderBoard.h"

class Menus
{
    private:
        //PlayButton
        sf::Texture PlayButtonTex;
        sf::Sprite PlayButton;

        //LeaderBoardButton
        sf::Texture LeaderBoardButtonTex;
        sf::Sprite LeaderBoardButton;

        //Controls Button
        sf::Texture ControlsButtonTex;
        sf::Sprite ControlsButton;
        sf::Texture ControlsBackground;
        sf::Sprite ControlsBack;

        //story Button
        sf::Texture StoryButtonTex;
        sf::Sprite StoryButton;
        sf::Texture StoryBackground;
        sf::Sprite StoryBack;

        //CreditsButton
        sf::Texture CreditsButtonTex;
        sf::Sprite CreditsButton;
        sf::Texture CreditsBackground;
        sf::Sprite CreditsBack;

        //Exit Button
        sf::Texture ExitButtonTex;
        sf::Sprite ExitButton; 

        // Cursor
	    sf::CircleShape Cursor; 

    public:
        //Navigation System
        bool Start = false;
        bool Menu = true;
        bool Controls = false;
        bool Story = false;
        bool Credits = false;
        bool CharacterSelect = false;
        bool InGame = false;
        bool IsGameMode = false;

        // Controls Menu
        sf::Sprite Buttons[6];
        sf::Texture ButtonsTexture[12];

       
        sf::Sprite SelectPlayer;
        sf::Texture SelectPlayerTexture;

        sf::Text Intructions;
        sf::Text BackgroundStory;
        sf::Text Choose;
        sf::Text CreditsText;

        //Menu
        sf::Clock PressTimer;


        void Intialize(sf::Font& font, sf::RenderWindow& window)
        {
            PlayButtonTex.loadFromFile("res/Textures/play button.png");
            PlayButton.setTexture(PlayButtonTex);
            PlayButton.setPosition(200.f, 150.f);
            PlayButton.setScale(1.0f, 1.0f);

            LeaderBoardButtonTex.loadFromFile("res/Textures/leaderboard button.png");
            LeaderBoardButton.setTexture(LeaderBoardButtonTex);
            LeaderBoardButton.setPosition(200.f, 250.f);
            LeaderBoardButton.setScale(1.0f, 1.0f);

            ControlsButtonTex.loadFromFile("res/Textures/Controls button.png");
            ControlsButton.setTexture(ControlsButtonTex);
            ControlsButton.setPosition(200.f, 350.f);
            ControlsButton.setScale(1.0f, 1.0f);

            StoryButtonTex.loadFromFile("res/Textures/story button.png");
            StoryButton.setTexture(StoryButtonTex);
            StoryButton.setPosition(200.f, 450.f);
            StoryButton.setScale(1.0f, 1.0f);

            CreditsButtonTex.loadFromFile("res/Textures/Credits button.png");
            CreditsButton.setTexture(CreditsButtonTex);
            CreditsButton.setPosition(200.f, 550.f);
            CreditsButton.scale(1.0f, 1.0f);

            ExitButtonTex.loadFromFile("res/Textures/Exit button.png");
            ExitButton.setTexture(ExitButtonTex);
            ExitButton.setPosition(200.f, 650.f);
            ExitButton.setScale(1.0f, 1.0f);

            Cursor.setPosition(210.f, 160.f);
            Cursor.setRadius(5.f);
            Cursor.setFillColor(sf::Color::Transparent);

            CreditsText.setFont(font);
            CreditsText.scale(1.5f, 1.5f);
            CreditsText.setPosition(100, 400);
            CreditsText.setString("Credits by: Toh Qi Qi \nMatric No: B031810095 \nSupervisor Name: Shahril Bin Parumo");

            Intructions.setFont(font);
            Intructions.scale(0.9f, 0.9f);
            Intructions.setString(" Press the A button key to move left \n Press D button key to Move right \n Press W button key or SPACE to Jump \n Press P button key to Pause the game \n Press M button key to Change the music \n Press SPACE to select the CHARACTER \n Press ARROW KEY to chase the Dr Shuzak");

            Intructions.setPosition(window.getSize().x / 4.4, window.getSize().x / 9.5);

            BackgroundStory.setFont(font);
            BackgroundStory.scale(0.9f, 0.9f);
            BackgroundStory.setString(" This game take place in a park where the family (four characters)\n go to have a picnic and enjoy their family little time.\n Out of nowhere, John spotted a villain\n Dr Shuzak and all of them chased after him. ");

            BackgroundStory.setPosition(window.getSize().x / 4.4, window.getSize().x / 9.5);

            ControlsBackground.loadFromFile("res/Textures/mainBackground.png");
            ControlsBack.setTexture(ControlsBackground);

            SelectPlayerTexture.loadFromFile("res/Textures/player select button highlighted.png");
            SelectPlayer.setTexture(SelectPlayerTexture);
            SelectPlayer.setScale(1.2, 1.2);
            SelectPlayer.setPosition(window.getSize().x / 3.2, window.getSize().y / 5.9);
            Choose.setString("Press Spacebar to select CHARACTER");
            Choose.setFont(font);
            Choose.setScale(1, 1);
            Choose.setPosition(window.getSize().x / 3.2, window.getSize().y / 1.3);
        } 

        void MainMenu(bool& GameMode,sf::RenderWindow& window, OurMusic& GameMusic, Background& GameBackground, LeaderBoard& GameLeaderBoards)
	    {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && Cursor.getPosition().y > 160 && PressTimer.getElapsedTime().asSeconds() > 0.24)
            {
                Cursor.move(0.f, -100.f);
                PressTimer.restart();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && Cursor.getPosition().y < 650 && PressTimer.getElapsedTime().asSeconds()>0.24)
            {
                Cursor.move(0.f, 100.f);
                PressTimer.restart();
            }

            //PlayButton
		    if (Cursor.getGlobalBounds().intersects(PlayButton.getGlobalBounds())) 
            {
			    PlayButtonTex.loadFromFile("res/Textures/play button highlighted.png");
			    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			    {
                    if (!InGame)
                    {
                        CharacterSelect = true;
                    }
                    else if (IsGameMode)
                    {
                        GameMode = true;
                        IsGameMode = false;
                    }
                    else
                    {
                        Start = true;
                    }
                    Menu = false;
                    if (GameMusic.MusicChanged)
                    {
                        GameMusic.BackgroundMusic("res/Audio/" + std::to_string(GameMusic.CurrentMusic) + ".wav");
                        GameMusic.MusicChanged = false;
                        GameMusic.CreditsMusic = false;
                    }
			    }
            }
            else
            {
                PlayButtonTex.loadFromFile("res/Textures/play button.png");
            }

            //LeaderBoardButton
            if (Cursor.getGlobalBounds().intersects(LeaderBoardButton.getGlobalBounds())) {
                LeaderBoardButtonTex.loadFromFile("res/Textures/leaderboard button highlighted.png");
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                    GameLeaderBoards.Retrieve(window);
                }
            }
            else
            {
                LeaderBoardButtonTex.loadFromFile("res/Textures/leaderboard button.png");
            }

            //ControlsButton
            if (Cursor.getGlobalBounds().intersects(ControlsButton.getGlobalBounds())) {
                ControlsButtonTex.loadFromFile("res/Textures/Controls button highlighted.png");
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                    Controls = true;
                    Menu = false;
                }
            }
            else
            {
                ControlsButtonTex.loadFromFile("res/Textures/Controls button.png");
            }

            //StoryButton
            if (Cursor.getGlobalBounds().intersects(StoryButton.getGlobalBounds())) 
            {
                StoryButtonTex.loadFromFile("res/Textures/story button highlighted.png");
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                    Story = true;
                    Menu = false;
                }
            }
            else
            {
                StoryButtonTex.loadFromFile("res/Textures/story button.png");
            }

            //CreditsButton
            if (Cursor.getGlobalBounds().intersects(CreditsButton.getGlobalBounds())) 
            {
                CreditsButtonTex.loadFromFile("res/Textures/Credits button highlighted.png");
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                    Credits = true;
                    Menu = false;
                    
                    if (!GameMusic.CreditsMusic)
                    {
                        GameMusic.BackgroundMusic("res/Audio/Fist-Bump.wav");
                        GameMusic.CreditsMusic = true;
                        GameMusic.MusicChanged = true;
                    }
                }
            }
            else
            {
                CreditsButtonTex.loadFromFile("res/Textures/Credits button.png");
            }

            //ExitButton
            if (Cursor.getGlobalBounds().intersects(ExitButton.getGlobalBounds())) 
            {
                ExitButtonTex.loadFromFile("res/Textures/Exit button highlighted.png");
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                    window.close();
                }
            }
            else
            {
                ExitButtonTex.loadFromFile("res/Textures/Exit button.png");
            }

            GameBackground.Parallex(window);

            window.clear();

            // GameBackground.Draw(window);

            window.draw(ControlsBack);

            window.draw(PlayButton);
            window.draw(LeaderBoardButton);
            window.draw(ControlsButton);
            window.draw(StoryButton);
            window.draw(CreditsButton);
            window.draw(ExitButton);
            window.draw(Cursor);
            window.display();
        }

    void GameCredtis(sf::RenderWindow& window)
	{
		window.clear();
        CreditsBackground.loadFromFile("res/Textures/Splash.png");
        CreditsBack.setTexture(CreditsBackground);
        window.draw(CreditsBack);
		window.draw(CreditsText);
		window.display();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			Credits = false;
			Menu = true;
			if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
			{
				CreditsText.setPosition(100, 400);
			}
		}
	}
};