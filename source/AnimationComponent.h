#pragma once

#include <map>
#include <string>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"

class AnimationComponent
{
    private:
        class Animation
        {
            //variables
            sf::Sprite& sprite;
            sf::Texture& textureSheet;
            float animationTimer;
            float timer;
            int width;
            int height;
            sf::IntRect startRect;
            sf::IntRect currentRect;
            sf::IntRect endRect;

            public:
                Animation(sf::Sprite& sprite, sf::Texture& texture_sheet, 
                    float animation_timer, 
                    int start_frame_x, int start_frame_y, int frame_x, int frame_y, int width, int height)
                    : sprite(sprite), textureSheet(texture_sheet), 
                      animationTimer(animation_timer), width(width), height(height)
                {
                    this->timer = 0.0f;
                    this->startRect = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
                    this->currentRect = this->startRect;
                    this->endRect = sf::IntRect(frame_x * width, frame_y * height, width, height);

                    this->sprite.setTexture(this->textureSheet, true);
                    this->sprite.setTextureRect(this->startRect);
                }   

                //functions
                void play(const float &dt)
                {
                    //update timer
                    this->timer += 100.0f * dt;
                    if(this->timer >= this->animationTimer)
                    {
                        //reset timer
                        this->timer = 0.0f;

                        //animate
                        if(this->currentRect != this->endRect)
                        {
                            this->currentRect.left += this->width;
                        }
                        else //reset
                        {
                            this->currentRect.left = this->startRect.left;
                        }

                        this->sprite.setTextureRect(this->currentRect);
                    }
                }

                // void pause();
                void reset()
                {
                    this->timer = 0.0f;
                    this->currentRect = this->startRect;
                }
        };

        sf::Sprite& sprite;
        sf::Texture& textureSheet;
        std::map<std::string, Animation*> animations;
        Animation* lastAnimation;
        
    public:
        AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet);
        virtual ~AnimationComponent();

        //functions
        void addAnimation(const std::string key,  
            float animation_timer, 
            int start_frame_x, int start_frame_y, int frame_x, int frame_y, int width, int height);

        // void startAnimation(const std::string animation);
        // void pauseAnimation(const std::string animation);
        // void resetAnimation(const std::string animation);

        void play(const std::string key, const float& dt);
};