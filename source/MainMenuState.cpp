#include "MainMenuState.h"

//initializer functions
void::MainMenuState::initVariable()
{

}

void::MainMenuState::initBackground()
{
    this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));
    this->bgTexture.loadFromFile("res/Textures/Backgrounds/Sky.png");
    this->background.setTexture(&this->bgTexture);
}

void MainMenuState::initFonts()
{
    if(!this->font.loadFromFile("res/Fonts/menu_font.ttf"))
    {
        throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
    }
}

void MainMenuState::initButtons()
{
    this->buttons["GAME_STATE_BTN"] = new Button(
        500, 320, 250, 100,
        &this->font, "Play",
        sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

    this->buttons["EXIT_STATE_BTN"] = new Button(
        500, 450, 250, 100,
        &this->font, "Quit",
        sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

}

MainMenuState::MainMenuState(sf::RenderWindow *window, std::stack<State*>* states) : State(window, states)
{
    this->initVariable();
    this->initBackground();
    this->initFonts();
    this->initButtons();
}

MainMenuState::~MainMenuState()
{
    auto it = this->buttons.begin();
    for(it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
}

void MainMenuState::updateInput(const float& dt)
{
    //update player input
}

void MainMenuState::updateButtons()
{
    //Update all the buttons in the state and handles their functionality
    for(auto &it : this->buttons)
    {
        it.second->update(this->mousePosView);
    }

    //Go to game state
    if(this->buttons["GAME_STATE_BTN"]->isPressed())
    {
        this->states->push(new GameState(this->window, this->states));
    }

    //Quit game
    if(this->buttons["EXIT_STATE_BTN"]->isPressed())
    {
        this->endState();
    }
}

void MainMenuState::update(const float& dt)
{
    this->updateMousePosition();
    this->updateInput(dt);
    this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
    for(auto &it : this->buttons)
    {
        it.second->render(target);
    }
}

void MainMenuState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window; 

    target->draw(this->background);
    this->renderButtons(target);

    this->renderButtons(target);

    //remove later!!
    // sf::Text mouseText;
    // mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
    // mouseText.setFont(this->font);
    // mouseText.setCharacterSize(12);
    // std::stringstream ss;
    // ss<< this->mousePosView.x << "" <<this->mousePosView.y;
    // mouseText.setString(ss.str());

    // target->draw(mouseText);
}