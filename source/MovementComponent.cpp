#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite, 
    float maxVelocity, float acceleration, float deceleration) 
    : sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{

}

MovementComponent::~MovementComponent()
{

}

//accessors
const sf::Vector2f& MovementComponent::getVelocity() const
{
    //return statement here
    return this->velocity;
}

//functions
const bool MovementComponent::getState(const short unsigned state) const
{
    switch (state)
    {
        case IDLE:
            if(this->velocity.x == 0.0f && this->velocity.y == 0.0f)
                return true;
            break;
        case MOVING:
            if(this->velocity.x != 0.0f || this->velocity.y != 0.0f)
                return true;
            break;
        case MOVING_LEFT:
            if(this->velocity.x < 0.0f)
                return true;
            break;
        case MOVING_RIGHT:
            if(this->velocity.x > 0.0f)
                return true;
            break;
        case MOVING_UP:
            if(this->velocity.y < 0.0f)
                return true;
            break;
        case MOVING_DOWN:
            if(this->velocity.y > 0.0f)
                return true;
            break;
    }

    return false;
}

void::MovementComponent::move(const float dir_x, const float dir_y, const float& dt)
{
    // accelerating a sprite until it reaches the max velocity
    this->velocity.x += this->acceleration * dir_x; // this->velocity.x = this->maxVelocity * dir_x;
    this->velocity.y += this->acceleration * dir_y; // this->velocity.y = this->maxVelocity * dir_y;

}

void MovementComponent::update(const float& dt)
{
    /*
        decelerates the sprite and control the maximum velocity.
        move the sprite
     */

    // deceleration x
    if(this->velocity.x > 0.0f) //check for positive x
    {
        //max velocity check
         if(this->velocity.x > this->maxVelocity)
            this->velocity.x = this->maxVelocity;

        //deceleration x positive
        this->velocity.x -= deceleration;
        if(velocity.x < 0.0f)
            this->velocity.x = 0.0f;
    }
    else if(this->velocity.x < 0.0f) // check for negative x
    {
        // max velocity check 
        if(this->velocity.x < -this->maxVelocity)
            this->velocity.x = -this->maxVelocity;

        //deceleration x negative
        this->velocity.x += deceleration;
        if(velocity.x > 0.0f)
            this->velocity.x = 0.0f;
    }

    // deceleration y
    if(this->velocity.y > 0.0f) //check for positive y
    {
        //max velocity check
         if(this->velocity.y > this->maxVelocity)
            this->velocity.y = this->maxVelocity;

        //deceleration y positive
        this->velocity.y -= deceleration;
        if(velocity.y < 0.0f)
            this->velocity.y = 0.0f;
    }
    else if(this->velocity.y < 0.0f) // check for negative y
    {
        // max velocity check 
        if(this->velocity.y < -this->maxVelocity)
            this->velocity.y = -this->maxVelocity;

        //deceleration y negative
        this->velocity.y += deceleration;
        if(velocity.y > 0.0f)
            this->velocity.y = 0.0f;
    }

    //final move
    this->sprite.move(this->velocity * dt); //uses velocity
}