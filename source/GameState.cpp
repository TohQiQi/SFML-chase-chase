#include "GameState.h"

//initializer funtion
void GameState::initTexture()
{
    if (!this->textures["IDLE"].loadFromFile("res/Textures/Idle__000.png"))
    {
        throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
    }
    // sf::Texture temp;
    // temp.loadFromFile("res/Textures/Idle__000.png");
    // this->textures["IDLE"] = temp;
}

void GameState::initPlayers()
{
    this->player = new Player(0, 0, this->textures["IDLE"]);
}

// constructor
GameState::GameState(sf::RenderWindow *window, std::stack<State*>* states) : State(window, states)
{
    this->initTexture();
    this->initPlayers();
}

//destructor
GameState::~GameState()
{
    delete this->player;
}

//function
void GameState::updateInput(const float& dt)
{
    // update player input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        this->player->move(-1.0f, 0.0f, dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        this->player->move(1.0f, 0.0f, dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        this->player->move(0.0f, -1.0f, dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        this->player->move(0.0f, 1.0f, dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
       this->endState();
    }
}

void GameState::update(const float& dt)
{
    this->updateMousePosition();
    this->updateInput(dt);
    this->player->update(dt);
}

void GameState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;
    
    this->player->render(target);
    
    
}