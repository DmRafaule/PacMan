#pragma once 

#include <SFML/Graphics.hpp>

class Ghost{
public:
    Ghost();
    ~Ghost();
    void __update();
    void __render();
    
private:
    void initTexture();
    void setPos(float x, float y);/*HERE*/
private:
    sf::Texture texture;
    sf::Sprite sprite;
};