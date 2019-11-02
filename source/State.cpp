#include "State.h"


State::State(sf::RenderWindow* window, std::stack<State*>* states)
{
    this->window = window;
    this->states = states;
    this->quit = false;
    this->paused = false;
    this->Keytime = 0.0f;
    this->KeytimeMax = 10.0f;
}

State::~State()
{

}


//accessors
const bool& State::getQuit() const
{
    //insert return statement here
    return this->quit;
}

const bool State::getKeyTime()
{
    if(this->Keytime >= this->KeytimeMax)
    {
        this->Keytime = 0.0f;
        return true;
    }

    return false;
}


//functions
void State::endState()
{
    this->quit = true;
}

void State::pauseState()
{
    this->paused = true;
}

void State::unPauseState()
{
    this->paused = false;
}

void State::updateMousePosition()
{
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

void State::updateKeytime(const float& dt)
{
    if(this->Keytime < this->KeytimeMax)
        this->Keytime += 20.0f * dt;
}