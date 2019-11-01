#pragma once

#include "Entity.h"

class Player : public Entity
{
    private:
    //variables

    
    //initializer functions
    void initVariable();
    void initComponent();

    public:
        Player(float x, float y, sf::Texture& texture_sheet);
        virtual ~Player();

        //functions
        virtual void update(const float& dt);
};