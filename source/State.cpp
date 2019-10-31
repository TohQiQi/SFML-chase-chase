#include "State.h"


State::State(sf::RenderWindow* window, std::stack<State*>* states)
{
    this->window = window;
    this->states = states;
    this->quit = false;
}

State::~State()
{

}

const bool& State::getQuit() const
{
    //insert return statement here
    return this->quit;
}

void State::endState()
{
    this->quit = true;
}

void State::updateMousePosition()
{
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}