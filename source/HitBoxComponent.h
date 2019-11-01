#pragma once


#include <ctime>
#include <cstdlib>
#include <iostream>


#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"

class HitBoxComponent
{
    private:
        sf::Sprite& sprite;
        sf::RectangleShape hitbox;
        float offsetX;
        float offsetY;

    public:
        HitBoxComponent(sf::Sprite& sprite, 
        float offset_x, float offset_y, 
        float width, float height);
        virtual ~HitBoxComponent();

        //functions
        bool checkIntersect(const sf::FloatRect& frect); //collider
        
        void update();
        void render(sf::RenderTarget& target);
};