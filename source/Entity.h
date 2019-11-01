#pragma once

#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "HitBoxComponent.h"

class Entity
{
    private:
        void initVariable();

    protected:
        sf::Sprite sprite;

        HitBoxComponent *hitBoxComponent;
        MovementComponent *movementComponent;
        AnimationComponent *animationComponent;

    public:
        Entity();
        virtual ~Entity();

        //component function
        void setTexture(sf::Texture& texture);
        void createHitboxComponent(sf::Sprite& sprite, 
            float offset_x, float offset_y, 
            float width, float height);
        void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
        void createAnimationComponent(sf::Texture& texture_sheet);

        // functions
        virtual void setPosition(const float x, const float y);
        virtual void move(const float x, const float y, const float& dt);
        virtual void update(const float& dt);
        virtual void render(sf::RenderTarget& target);
};