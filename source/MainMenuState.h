#pragma once

#include "GameState.h"
#include "Button.h"

class MainMenuState : public State
{   
    private:
        //variables
        sf::Texture bgTexture;
        sf::RectangleShape background;

        sf::Font font;

        std::map<std::string, Button*> buttons;

        //function
        void initVariable();
        void initBackground();
        void initFonts();
        void initButtons();

    public:
        MainMenuState(sf::RenderWindow *window, std::stack<State*>* states);
        virtual ~MainMenuState();

        // functions 
        void updateInput(const float& dt);
        void updateButtons();
        void update(const float& dt);
        void renderButtons(sf::RenderTarget& target);
        void render(sf::RenderTarget* target = NULL);
};