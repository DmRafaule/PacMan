#pragma once
 
#include <SFML/Graphics.hpp>
#include <sstream>

class Menu{
private:
    sf::Sprite *sprite;
    std::stringstream *ss;
    sf::Text *text;
    sf::Vector2f *posOnScreen;
public:
    Menu(sf::Sprite&,std::stringstream&,sf::Vector2f&,sf::Text&);
    ~Menu();
    void _render(sf::RenderTarget &win);
    void _update(sf::RenderTarget &win);
};