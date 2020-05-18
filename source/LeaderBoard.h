#pragma once

#include "RequiredHeaders.h"

class LeaderBoard
{
    private:
        sf::Font font;

    public:
        void Init()
        {
            font.loadFromFile("res/Fonts/score.ttf");
        }

        //add player
        void AddPlayer(std::string name, int score)
        {
            std::ofstream scoreRecords;
            scoreRecords.open("records.txt", std::ios::app);
            scoreRecords << name << "\t\t\t" << score << std::endl;
        }

        //check player name
        bool Search(std::string name)
        {
            std::ifstream scoreRecords;
            std::string score;
            std::vector<std::string> scores;
            scoreRecords.open("records.txt", std::ios::app);

            while(!scoreRecords.eof())
            {
                std::getline(scoreRecords, score);
                if (score.size() > 4)
				    score.erase(score.size() - 4, score.size());
                scores.push_back(score);
                if (name == score) {
                    return 1;
                }
            }
            
            for (int i = 0; i < scores.size(); ++i) 
            {
			    if (scores[i] == name)return 1;
		    }
		    
            return 0;
        }

        int convert(std::string str)
        {
            int score = 0;
		    
            for (int i = 0; i <str.size(); ++i) 
            {
                int digit = str[i] - '0';
                score *= 10;
                score += digit;
            }
            return score;
        }

        //get score text
        void getScore(sf::RenderWindow& window, int score)
        {
            sf::RectangleShape textbox;
            sf::RectangleShape button;

            //textbox
            textbox.setSize(sf::Vector2f(250.0f, 50.0f));
            textbox.setPosition(window.getSize().x / 2 - 120, window.getSize().y / 2 - 50);
            textbox.setFillColor(sf::Color::Transparent);
            textbox.setOutlineColor(sf::Color::Blue);
            textbox.setOutlineThickness(5);

            //button
            button.setSize(sf::Vector2f(100.0f, 50.0f));
            button.setPosition(textbox.getPosition().x + 75, textbox.getPosition().y + 100);
            button.setFillColor(sf::Color::Transparent);

            //texts
            sf::Texture titleTx, addButtonTx;
            sf::Sprite title, addButton;
            
            titleTx.loadFromFile("res/Textures/AddPlayer.png");
            title.setTexture(titleTx);
            title.setPosition(250, 50);
            
            addButtonTx.loadFromFile("res/Textures/Add.png");
            addButton.setTexture(addButtonTx);
            addButton.setPosition(button.getPosition().x + 30, button.getPosition().y + 10);
            
            sf::Text label;
            label.setFont(font);
            label.setPosition(textbox.getPosition().x, textbox.getPosition().y - 40);
            label.setString("Type Your Name :");
            label.setCharacterSize(20);

            //variables
            std::string name;
            std::vector<sf::Text> playerName;
            sf::Text letter;
            letter.setFont(font);

            sf::Event event;

            while(window.isOpen())
            {
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed) 
                    {
					    window.close();
				    }
                    
                    //get text
                    if(event.type == sf::Event::TextEntered && event.text.unicode > 0 && name.size() < 15 )
                    {
                        if (static_cast<char>(event.text.unicode) != '\r') 
                        {
                            letter.setString(static_cast<char>(event.text.unicode));
                            playerName.push_back(letter);
                            name += static_cast<char>(event.text.unicode);
					    }
                    }

                    //edit text
				    sf::Keyboard key;
				    if (key.isKeyPressed(sf::Keyboard::BackSpace) && !playerName.empty()) 
                    {
					    name.erase(name.size() - 1, name.size());
					    playerName.pop_back();
				    }
				
                    //Button activaion
				    sf::Mouse mouse;
				    if (mouse.isButtonPressed(sf::Mouse::Left) && (mouse.getPosition().x >= 667.0 && mouse.getPosition().x <= 764.0) && (mouse.getPosition().y >= 465.0 && mouse.getPosition().y <= 513.0) && !playerName.empty() || (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Return)) 
                    {
					    if (!Search(name) && name != "")
						    AddPlayer(name, score);
                        
                        playerName.clear();
                        name = "";
                        return;
				    }
                }

                //display
                window.clear();

                //output username
                int space = 0;
                for(int i = 0; i < playerName.size(); i++)
                {
                    playerName[i].setPosition(textbox.getPosition().x + space, textbox.getPosition().y);
                    window.draw(playerName[i]);
                    space += playerName[i].getGlobalBounds().width + 3;
                }
                
                window.draw(title);
                window.draw(label);
                window.draw(textbox);
                window.draw(button);
                window.draw(addButton);
                window.display();
            }
        }

        bool LeaderBoards(std::vector<std::pair<sf::Text, sf::Text>> vec, sf::RenderWindow& leaderBoardsWindow)
        {
            sf::Text title;
            sf::Text Names;
            sf::Text Scores;

            std::string NamesString;
            std::string ScoresString;

            int i = 0;
            Names.setFont(font);
            Names.setScale(1.5, 1.5);
            Names.setPosition(leaderBoardsWindow.getSize().x / 3.8, 140);
            Scores.setFont(font);
            Scores.setScale(1.5, 1.5);
            Scores.setPosition(leaderBoardsWindow.getSize().x / 1.6, 140);

            sf::Sprite Up;
            sf::Sprite Down;
            sf::Texture UpHit;
            sf::Texture UpMiss;
            sf::Texture DownHit;
            sf::Texture DownMiss;

            UpHit.loadFromFile("res/Textures/0.png");
            UpMiss.loadFromFile("res/Textures/up arrow miss.png");
            DownHit.loadFromFile("res/Textures/2.png");
            DownMiss.loadFromFile("res/Textures/down arrow  miss.png");

            Up.setTexture(UpMiss);
            Up.setScale(3, 3);
            Down.setScale(3, 3);
            Down.setTexture(DownMiss);
            Up.setPosition(leaderBoardsWindow.getSize().x / 1.2, leaderBoardsWindow.getSize().y / 3);
            Down.setPosition(leaderBoardsWindow.getSize().x / 1.2, (leaderBoardsWindow.getSize().y / 2) + 30);
            
            title.setString("Player Name        Score");
            title.setFont(font);
            title.setPosition(leaderBoardsWindow.getSize().x / 4, 50);
            title.setScale(2.f, 2.f);
            title.setFillColor(sf::Color::Magenta);

            while (leaderBoardsWindow.isOpen()) 
            {
			    sf::Event event;
			    while (leaderBoardsWindow.pollEvent(event))
			    {
				    if(event.type == sf::Event::Closed) 
                    {
					    leaderBoardsWindow.close();
				    }
				    
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && Names.getPosition().y >- Names.getGlobalBounds().height + leaderBoardsWindow.getSize().y)
                    {
                        title.move(0, -8);
                        Names.move(0, -8);
                        Scores.move(0, -8);
                        Down.setTexture(DownHit);
                    }
                    else
                    {
                        Down.setTexture(DownMiss);
                    }
				
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && title.getPosition().y < 50)
                    {
                        title.move(0, 8);
                        Names.move(0, 8);
                        Scores.move(0, 8);
                        Up.setTexture(UpHit);
                    }
                    else
                    {
                        Up.setTexture(UpMiss);
                    }
				
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    {
                        title.setPosition(leaderBoardsWindow.getSize().x / 4, 50);
                        Names.setPosition(leaderBoardsWindow.getSize().x / 3.8, 140);
                        Scores.setPosition(leaderBoardsWindow.getSize().x / 1.6, 140);
                        return true;
                    }
				    leaderBoardsWindow.clear(sf::Color::Black);
				
                    for (i; i < vec.size(); ++i)
                    {

                        NamesString += std::to_string(i + 1) + "   " + vec[i].first.getString() + "\n";
                        ScoresString += vec[i].second.getString() + "\n";
                        Names.setString(NamesString);
                        Scores.setString(ScoresString);
                    }
				
                    leaderBoardsWindow.draw(title);
                    leaderBoardsWindow.draw(Names);
                    leaderBoardsWindow.draw(Scores);
                    leaderBoardsWindow.draw(Up);
                    leaderBoardsWindow.draw(Down);
                    leaderBoardsWindow.display();
			    }
		    }

	    } 

        // Retrieve Data
	    void Retrieve(sf::RenderWindow& window)
	    {
		    std::priority_queue<std::pair<int, std::string>> leads;
		    std::ifstream records;
		    std::string name, score;
		    std::vector <std::pair <sf::Text, sf::Text>> vec;
		    sf::Text txtName, txtString;
		    
            txtName.setFont(font);
		    txtString.setFont(font);
		    records.open("records.txt", std::ios::app);
		    
            while (!records.eof()) 
            {
			    std::getline(records, name);
			    if (name.size() > 4) 
                {
				    score = name;
				    int num_place = name.find_first_of("0123456789");
				    int letter_place = name.find_first_of('\t');
                    name.erase(letter_place, name.size());
                    score.erase(0, num_place);
                    int num_score = convert(score);
				    leads.push(std::pair<int, std::string>(num_score, name));
			    }
            }
            while (!leads.empty()) 
            {
                std::string ss = std::to_string(leads.top().first);
                txtName.setString(ss);
                txtString.setString(leads.top().second);
                vec.push_back(std::pair<sf::Text, sf::Text>(txtString, txtName));
                leads.pop();
            }
		    
            LeaderBoards(vec, window);
           
            if (LeaderBoards(vec, window))
            {
                return;
            }
	}
};