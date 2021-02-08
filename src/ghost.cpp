#include "ghost.hpp"

Ghost::Ghost(){
    initTexture();
    //initPos();
}
Ghost::~Ghost(){

}
void Ghost::__update(){

}
void Ghost::__render(sf::RenderTarget &win){
    win.draw(sprite);
}
void Ghost::initTexture(){
    texture.loadFromFile("../texture/ghost.png");
    sprite.setTexture(texture);
    sprite.setColor(sf::Color(rand()%250+0,rand()%250+0,rand()%250+0,rand()%100+150));
}
void Ghost::initPos(){
    sprite.setPosition((rand()%3+0)*50,
                       (rand()%10+0)*50);
}
