#include "menu.hpp"

Menu::Menu(sf::Sprite &sprite,std::stringstream &ss,sf::Vector2f &posOnScreen,sf::Text &text){
    this->sprite = &sprite;
    this->ss = &ss;
    this->posOnScreen = &posOnScreen;
    this->text = &text;
}
Menu::~Menu(){
}


void Menu::_render(sf::RenderTarget &win){
    win.draw(*sprite);
    win.draw(*text);
}
void Menu::_update(sf::RenderTarget &window){
    posOnScreen->x = window.getSize().x/2 - sprite->getGlobalBounds().width/2;
    posOnScreen->y = window.getSize().y/2 - sprite->getGlobalBounds().height/2;
    
    *ss << "Menu\t\tHelp\n\nSettings\tQuit";
    text->setString(ss->str());
    ss->str("");
    
    sprite->setPosition(*posOnScreen);
    text->setPosition(posOnScreen->x + 30,
                      posOnScreen->y + 30);
}