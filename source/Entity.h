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

class Entity
{
    private:
        void initVariable();

    protected:
        sf::Texture *texture;
        sf::Sprite *sprite;

        float movementSpeed;

    public:
        Entity();
        virtual ~Entity();

        //component function
        void createSprite(sf::Texture* texture);

        // functions
        virtual void setPosition(const float x, const float y);
        virtual void move(const float& dt, const float x, const float y);
        virtual void update(const float& dt);
        virtual void render(sf::RenderTarget* target);
};