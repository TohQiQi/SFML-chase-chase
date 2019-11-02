#pragma once

#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stack>
#include <map>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"

#include "Button.h"

class PauseMenu
{
    private:
        sf::Font& font;
        sf::Text menuText;

        sf::RectangleShape background;
        sf::RectangleShape container;

        std::map<std::string, Button*> buttons;

        //private function

    public:
        PauseMenu(sf::RenderWindow& window, sf::Font& font);
        virtual ~PauseMenu();

        //accessor
        std::map<std::string, Button*>& getButtons();

        //functions
        const bool isButtonPressed(const std::string key);
        void addButton(const std::string key, float y, const std::string text);
        void update(const sf::Vector2f& mousePos);
        void render(sf::RenderTarget& target);
};