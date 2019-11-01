#include "Player.h"

//initializer function
void Player::initVariable()
{

}

void Player::initComponent()
{

}

//constructors
Player::Player(float x, float y, sf::Texture& texture_sheet)
{
    this->initVariable();
    
    this->setPosition(x, y);

    //call hitbox
    this->createHitboxComponent(this->sprite, 0.0f, 0.0f, 144.0f, 144.0f);

    //call movement
    this->createMovementComponent(300.0f, 15.0f, 5.0f);

    //call animation
    this->createAnimationComponent(texture_sheet);

    this->animationComponent->addAnimation("IDLE", 10.0f, 0, 0, 9, 0, 144, 144); //1440/10=144, 576/4=144
    this->animationComponent->addAnimation("WALK", 10.0f, 0, 1, 9, 1, 144, 144); //1440/10=144, 576/4=144
    this->animationComponent->addAnimation("JUMP", 10.0f, 0, 2, 9, 2, 144, 144); //1440/10=144, 576/4=144

    // this->initComponent();
}


//destructors
Player::~Player()
{

}

//functions
void Player::update(const float& dt)
{
    this->movementComponent->update(dt);

    if(this->movementComponent->getState(IDLE))
    {
        this->animationComponent->play("IDLE", dt);
    }
    else if(this->movementComponent->getState(MOVING_RIGHT))
    {
        this->sprite.setOrigin(0.0f, 0.0f);
        this->sprite.setScale(1.0f, 1.0f);
        this->animationComponent->play("WALK", dt);
    }
    else if(this->movementComponent->getState(MOVING_LEFT))
    {
        this->sprite.setOrigin(145.0f, 0.0f);
        this->sprite.setScale(-1.0f, 1.0f);
        this->animationComponent->play("WALK", dt);
    }
    else if(this->movementComponent->getState(MOVING_UP))
    {
        this->animationComponent->play("JUMP", dt);
    }

    this->hitBoxComponent->update();
}