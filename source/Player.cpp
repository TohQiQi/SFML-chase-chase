#include "Player.h"

//initializer function
void Player::initVariable()
{

}

void Player::initComponent()
{
    //call movement
    this->createMovementComponent(300.0f, 15.0f, 5.0f);
}

//constructors
Player::Player(float x, float y, sf::Texture& texture)
{
    this->initVariable();
    this->initComponent();
    
    this->setTexture(texture);
    this->setPosition(x, y);
}


//destructors
Player::~Player()
{

}