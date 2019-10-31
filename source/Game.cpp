#include "Game.h"

//static function
 
//initializer function
void Game::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(1280, 700), "WillPower");
}

void Game::initStates()
{
    this->states.push(new MainMenuState(this->window, &this->states));
    // this->states.push(new GameState(this->window));
}

//constructor 
Game::Game()
{
    this->initWindow();
    this->initStates();
}

// destructor use for clear data
Game::~Game()
{
    delete this->window;
    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
}

//function
void Game::updateDt()
{
    //update the dt variable with the time it takes to update and render one frame
    this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateSFMLEvents()
{
    while (this->window->pollEvent(this->sfEvent))
    {
        if(this->sfEvent.type == sf::Event::Closed)
            this->window->close();
    }
    
}

void Game::update()
{
    this->updateSFMLEvents();

    if(!this->states.empty())
    {
        this->states.top()->update(this->dt);
        if(this->states.top()->getQuit())
        {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }
    else
    {
        //application end
        this->window->close();
    }
    
}

void Game::render()
{
    this->window->clear();

    //Render Items
    if(!this->states.empty())
        this->states.top()->render();

    this->window->display();
}

void Game::run()
{
    while (this->window->isOpen())
    {
        this->updateDt(); // reset the clock
        this->update();
        this->render();
    } 
}