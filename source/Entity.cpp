#include "Entity.h"

void Entity::initVariable()
{
    this->texture = NULL;
    this->sprite = NULL;
    this->movementSpeed = 100.0f;
}

Entity::Entity()
{
    this->initVariable();
}

Entity::~Entity()
{
    delete this->sprite;
}

//component function
void Entity::createSprite(sf::Texture* texture)
{
    this->texture = texture;
    this->sprite = new sf::Sprite(*this->texture);
}

//function
void Entity::setPosition(const float x, const float y)
{
    if(this->sprite)
    {
        this->sprite->setPosition(x, y);
    }
}

void Entity::move(const float& dt, const float dir_x, const float dir_y)
{
    if(this->sprite)
    {
        this->sprite->move(dir_x * this->movementSpeed * dt, dir_y* this->movementSpeed * dt);
    }
}

void Entity::update(const float &dt)
{
    
}

void Entity::render(sf::RenderTarget *target)
{
    if(this->sprite)
    {
        target->draw(*this->sprite);
    }
}