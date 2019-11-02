#pragma once
#include "Player.h"

class State
{
    protected:
        std::stack<State*>* states;
        sf::RenderWindow* window;

        bool quit;
        bool paused;
        float Keytime;
        float KeytimeMax;

        sf::Vector2i mousePosScreen;
        sf::Vector2i mousePosWindow;
        sf::Vector2f mousePosView;

        //resources
        std::map<std::string, sf::Texture> textures;

    public:
        State(sf::RenderWindow* window, std::stack<State*>* states);
        virtual ~State();

        //accessors
        const bool& getQuit() const;
        const bool getKeyTime();

        //functions
        void endState();
        void pauseState();
        void unPauseState();

        // pure virtual function
        virtual void updateMousePosition(); 
        virtual void updateKeytime(const float& dt);
        virtual void updateInput(const float& dt) = 0;
        virtual void update(const float& dt) = 0;
        virtual void render(sf::RenderTarget* target = NULL) = 0;
};