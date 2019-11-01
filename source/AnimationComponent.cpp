#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet)
    : sprite(sprite), textureSheet(texture_sheet), lastAnimation(NULL)
{

}

AnimationComponent::~AnimationComponent()
{
    for (auto &i : this->animations)
    {
        delete i.second;
    }
}

//functions
void AnimationComponent::addAnimation(
    const std::string key, 
    float animation_timer, 
    int start_frame_x, int start_frame_y, int frame_x, int frame_y, int width, int height)
{
    this->animations[key] = new Animation(
        this->sprite, this->textureSheet,
        animation_timer,
        start_frame_x, start_frame_y, frame_x, frame_y, width, height
    );
}

void AnimationComponent::play(const std::string key, const float& dt)
{
    if(this->lastAnimation != this->animations[key])
    {
        if(this->lastAnimation == NULL)
        {
            this->lastAnimation = this->animations[key];
        }
        else
        {
          this->lastAnimation->reset();
        this->lastAnimation = this->animations[key];
        }     
    }
    
    this->animations[key]->play(dt);
}