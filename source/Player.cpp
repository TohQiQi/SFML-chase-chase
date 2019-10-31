#include "Player.h"

//initializer function
void Player::initVariable()
{

}

void Player::initComponent()
{

}

//constructors
Player::Player(float x, float y, sf::Texture* texture)
{
    this->initVariable();
    this->initComponent();
    
    this->createSprite(texture);
    this->setPosition(x, y);
}


//destructors
Player::~Player()
{

}