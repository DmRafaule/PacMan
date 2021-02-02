#include "ghost.hpp"

Ghost::Ghost(){
    initTexture();
    setPos(/*HERE*/);
}
Ghost::~Ghost(){

}
void Ghost::__update(){

}
void Ghost::__render(){

}
void Ghost::initTexture(){
    texture.loadFromFile("../texture/ghost.png");
    sprite.setTexture(texture);
}
void Ghost::setPos(float x, float y){

}