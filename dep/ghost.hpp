#pragma once 

#include <SFML/Graphics.hpp>

class Ghost{
public:
    Ghost();
    ~Ghost();
    void __update();
    void __render(sf::RenderTarget &win);
    void setPos(float x, float y);
private:
    void initTexture();
    void initPos();
private:
    sf::Texture texture;
    sf::Sprite sprite;
};