#pragma once

#include "MainMenuState.h"

class Game
{
    private:
        //variables
        sf::RenderWindow *window;
        sf::Event sfEvent;

        //gonna keep track of how long it took for us for a game to render for up for to do one update call and render call
        sf::Clock dtClock;
        float dt;

        //put * because state is abstract class, can't create object of state on;y create pointer of state
        std::stack<State*> states;

        //initialization
        void initWindow();
        void initStates();

    public: 
        //constructors/destructors
        Game();
        virtual ~Game();

        // function end application
        void endApplication();
        
        // functions update
        void updateDt();
        void updateSFMLEvents();
        void update();

        //function render
        void render();

        //function core
        void run();
};