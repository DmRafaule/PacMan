#include "menu.hpp"

Menu::Menu(sf::RenderWindow &window){
    win = new sf::RenderWindow(sf::VideoMode(400,200),"Menu",sf::Style::None);
    win->setPosition(sf::Vector2i(window.getPosition().x + window.getSize().x/2-win->getSize().x/2,
                                   window.getPosition().y+ window.getSize().y/2-win->getSize().y/2));

    texture = new sf::Texture();
    texture->loadFromFile("../texture/menu.png");
    sprite = new sf::Sprite(*texture);
}
Menu::~Menu(){
    delete texture;
    delete sprite;
    delete win;
}


void Menu::_render(const bool &isMenu){
    if (isMenu){
        win->clear();
        win->draw(*sprite);
        win->display();
    }
}
void Menu::_update(const bool &isMenu, sf::RenderWindow &window){
    if (isMenu){
    win->setPosition(sf::Vector2i(window.getPosition().x + window.getSize().x/2-win->getSize().x/2,
                                 window.getPosition().y+ window.getSize().y/2-win->getSize().y/2));
    }
}