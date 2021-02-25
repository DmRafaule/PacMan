#include "menu.hpp"



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
    
    
}