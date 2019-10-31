#pragma once

#include "State.h"

class GameState : public State
{
    private:
        Player* player;

        //function
        void initTexture();
        void initPlayers();
    
    public:
        GameState(sf::RenderWindow *window, std::stack<State*>* states);
        virtual ~GameState();

        // functions 
        void updateInput(const float& dt);
        void update(const float& dt);
        void render(sf::RenderTarget* target = NULL);
};