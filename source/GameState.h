#pragma once

#include "State.h"
#include "PauseMenu.h"

class GameState : public State
{
    private:
        sf::Font font;
        PauseMenu* pmenu;
        Player* player;

        //function
        void initTexture();
        void initFonts();
        void initPauseMenu();
        void initPlayers();
    
    public:
        GameState(sf::RenderWindow *window, std::stack<State*>* states);
        virtual ~GameState();

        // functions 
        void updateInput(const float& dt);
        void updatePlayerInput(const float& dt);
        void updatePauseMenuButtons();
        void update(const float& dt);
        void render(sf::RenderTarget* target = NULL);
};