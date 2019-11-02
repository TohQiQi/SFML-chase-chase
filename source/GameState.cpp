#include "GameState.h"

//initializer funtion
void GameState::initTexture()
{
    if (!this->textures["PLAYER_IDLE"].loadFromFile("res/Textures/player.png"))
    {
        throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
    }
}

void GameState::initFonts()
{
    if(!this->font.loadFromFile("res/Fonts/menu_font.ttf"))
    {
        throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
    }
}

void GameState::initPauseMenu()
{
    this->pmenu = new PauseMenu(*this->window, this->font);

    this->pmenu->addButton("QUIT", 200.0f, "QUIT");
}

void GameState::initPlayers()
{
    this->player = new Player(0, 0, this->textures["PLAYER_IDLE"]);
}

// constructor
GameState::GameState(sf::RenderWindow *window, std::stack<State*>* states) 
    : State(window, states)
{
    this->initTexture();
    this->initFonts();
    this->initPauseMenu();
    this->initPlayers();
}

//destructor
GameState::~GameState()
{
    delete this->pmenu;
    delete this->player;
}

//function
void GameState::updateInput(const float& dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)  && this->getKeyTime())
    {
        if(!this->paused)
        {
            this->pauseState();
        }
        else
        {
            this->unPauseState();
        }     
    }
}

void GameState::updatePlayerInput(const float& dt)
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
}

void GameState::updatePauseMenuButtons()
{
    if(this->pmenu->isButtonPressed("QUIT"))
    {
        this->endState();
    }
}

void GameState::update(const float& dt)
{
    this->updateMousePosition();
    this->updateKeytime(dt);
    this->updateInput(dt);

    if(!this->paused) //unpaused state
    {
            this->updatePlayerInput(dt);

            this->player->update(dt);
    }
    else //pause state
    {
        this->pmenu->update(this->mousePosView);
        this->updatePauseMenuButtons();
    }
}

void GameState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;
    
    this->player->render(*target);
    
    if(this->paused) //pause render menu
    {
        this->pmenu->render(*target);
    }
}