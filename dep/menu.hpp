#pragma once
 
#include <SFML/Graphics.hpp>

class Menu{
private:
    sf::RenderWindow *win;
    sf::Texture *texture;
    sf::Sprite *sprite;

public:
    Menu(sf::RenderWindow &window);
    ~Menu();
    void _render(const bool &isMenu);
    void _update(const bool &isMenu, sf::RenderWindow &window);
};