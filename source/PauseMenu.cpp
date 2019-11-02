#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font)
    : font(font) //it is reference
{
    //Init background
    this->background.setSize(
        sf::Vector2f(
            static_cast<float>(window.getSize().x),
            static_cast<float>(window.getSize().y)
        )
    );

    this->background.setFillColor(sf::Color(20, 20, 20, 100));

    //Init container
    this->container.setSize(
        sf::Vector2f(
            static_cast<float>(window.getSize().x) / 4.0f,
            static_cast<float>(window.getSize().y) - 100.0f
        )
    );
    this->container.setFillColor(sf::Color(20, 20, 20, 200));
    this->container.setPosition(
        static_cast<float>(window.getSize().x) / 2.0f - this->container.getSize().x / 2.0f, 
        30.0f
    );

    //Init text
    this->menuText.setFont(font);
    this->menuText.setFillColor(sf::Color(255,255,255,200));
    this->menuText.setCharacterSize(60);
    this->menuText.setString("PAUSED");
    this->menuText.setPosition(
        this->container.getPosition().x + this->container.getSize().x / 2.0f - this->menuText.getGlobalBounds().width / 2.0f, 
        this->container.getPosition().y +20.0f
    );
}

PauseMenu::~PauseMenu()
{
    auto it = this->buttons.begin();
    for(it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
}


//accesor
std::map<std::string, Button*>& PauseMenu::getButtons()
{
    return this->buttons;
}

//functions
const bool PauseMenu::isButtonPressed(const std::string key)
{
    //check the button is press or not
    return this->buttons[key]->isPressed();
}

void PauseMenu::addButton(const std::string key, float y, const std::string text)
{
    float width = 250.0f;
    float height = 100.0f;
    float x = this->container.getPosition().x + this->container.getSize().x / 2.0f - width / 2.0f; 

    this->buttons[key] = new Button(
        x, y, width, height,
        &this->font, text,
        sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

void PauseMenu::update(const sf::Vector2f& mousePos)
{
    for(auto &i : this->buttons)
    {
        i.second->update(mousePos);
    }
}

void PauseMenu::render(sf::RenderTarget& target)
{   
    target.draw(this->background);
    target.draw(this->container);

    for(auto &i : this->buttons)
    {
        i.second->render(target);
    }

    target.draw(this->menuText);
}