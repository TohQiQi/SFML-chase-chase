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

class MovementComponent
{
    private:
        sf::Sprite& sprite;

        float maxVelocity;
        float acceleration;
        float deceleration;

        sf::Vector2f velocity;
        
        //initiliazer function


    public:
        MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration);
        virtual ~MovementComponent();

        //accessors
        const sf::Vector2f& getVelocity() const;

        //functions
        void move(const float x, const float y, const float& dt);
        void update(const float& dt);
};