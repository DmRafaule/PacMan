#include "ghost.hpp"
#include <iostream>

Ghost::Ghost(){
    initTexture();
    initVision();
}
Ghost::~Ghost(){
    delete vision;
}
sf::Sprite &Ghost::_getGhostSprite(){
    return sprite;
}

/*update f-tion*/
void Ghost::updateAnimation(){
    frame+=0.06;
    if (frame < 4){  
        if (isLeft) sprite.setTextureRect(sf::IntRect(500*static_cast<int>(frame),0,500,500));//Animation for leftward
        else if (isRight) sprite.setTextureRect(sf::IntRect(500*static_cast<int>(frame),0,500,500));//Animation for rightward
        if (isTop) sprite.setTextureRect(sf::IntRect(500*static_cast<int>(frame),0,500,500));//Animation for upward
        else if (isBottom) sprite.setTextureRect(sf::IntRect(500*static_cast<int>(frame),0,500,500));//Animation for downward
    }
    else frame = 0;
}
void Ghost::updateVision(){
    for (int i = 0; i != 4 ; ++i){
        vision->setPosition(sprite.getGlobalBounds().left - vision->getSize().x/2.5,
                            sprite.getGlobalBounds().top - vision->getSize().y/2.5);
    }
}
void Ghost::updateTiles(std::vector<std::vector<sf::Sprite>> &tiles){
    this->tiles = &tiles;
}
void Ghost::updateTime(){
    time = clock.getElapsedTime();
    if (time.asSeconds() >= 0.2){
        isFirst=true;
        clock.restart();
    }
}
void Ghost::__update(sf::RenderTarget &win,std::vector<std::vector<sf::Sprite>> &tiles, sf::Sprite &pack){
    updateTiles(tiles);
    updateVision();
    updateTime();

    updateCollisions(win);
    updateMovements(pack);
    updateAnimation();
    
    this->win = &win;
}
/*Render f-tion*/
void Ghost::__render(sf::RenderTarget &win){
    win.draw(sprite);
    for (int i = 0; i != 4 ; ++i){
        win.draw(*vision);
    }
}
/*init f-tion*/
void Ghost::initTexture(){
    texture.loadFromFile("../texture/ghost.png");
    sprite.setTexture(texture);
    int choise = rand()%4+0;
    switch (choise){//random generate types
        case red:{
            sprite.setColor(sf::Color::Red);
            break;
        }
        case blue:{
            sprite.setColor(sf::Color::Blue);
            break;
        }
        case green:{
            sprite.setColor(sf::Color::Green);
            break;
        }
        case yellow:{
            sprite.setColor(sf::Color::Yellow);
            break;
        }
    }
    sprite.scale(0.05,0.05);
    sprite.setTextureRect(sf::IntRect(0,0,500,500));
}
void Ghost::setPos(float x, float y){
    sprite.setPosition(x,y);
    vision->setPosition(x,y);        
}
void Ghost::initVision(){
    vision = new sf::RectangleShape;
    vision->setSize(sf::Vector2f(200.f, 200.f));
    vision->setFillColor(sf::Color(255,0,0,40));
}
/*Update f-tions*/
/*about collisions*/
void Ghost::updateCollisions(sf::RenderTarget &win){
    isWall = updateCollisionWalls(win);
}
void Ghost::showStat(){
}
bool Ghost::updateCollisionWalls(sf::RenderTarget &win){
    for (const auto &i : *tiles){
        for (const auto &j : i){
            if ((sprite.getGlobalBounds().intersects(j.getGlobalBounds())) && j.getScale().x == 0.25 ){
                return true;
            }
        }
    }
    return false;
}

/*about movements and visions*/
void Ghost::updateMovements(sf::Sprite &pack){
    updateMovementsNoVisionPack(pack);
    updateMovementsYesVisionPack();

    updateCorrectMovements();
    updateVisionPack(pack);
    
    updateChangingMovements();
    sprite.move(sf::Vector2f(dir_x,dir_y));
}
void Ghost::updateMovementsNoVisionPack(sf::Sprite &pack){
    if (isWall){
        switch (updateDecision()){
        case 0:
            isLeft = true;
            break;
        
        case 1:
            isTop = true;
            break;
        
        case 2:
            isBottom = true;
            break;
        
        case 3:
            isRight = true;
            break;
        }
    }
}
int Ghost::updateDecision(){
    int outcome  = 2;
    ghostPos.x = sprite.getPosition().x;
    ghostPos.y = sprite.getPosition().y;
    ghostSize.x = sprite.getGlobalBounds().width;
    ghostSize.y = sprite.getGlobalBounds().height;
    sf::Vector2f tmpPos;

    for (const auto &i : *tiles){
        for (const auto &j : i){
            //top sensor
            tmpPos.y = ghostPos.y - ghostSize.y;
            tmpPos.x = ghostPos.x - 0;
            if (j.getGlobalBounds().intersects(sf::FloatRect(tmpPos,ghostSize)) && j.getScale().x == 0.25){
                //HERE SENSORS ARE WORK
            }
            //bottom sensor
            tmpPos.y = ghostPos.y + ghostSize.y;
            tmpPos.x = ghostPos.x - 0;
            if (j.getGlobalBounds().intersects(sf::FloatRect(tmpPos,ghostSize)) && j.getScale().x == 0.25){
                
            }
            //right sensor
            tmpPos.y = ghostPos.y + 0;
            tmpPos.x = ghostPos.x + ghostSize.x;
            if (j.getGlobalBounds().intersects(sf::FloatRect(tmpPos,ghostSize)) && j.getScale().x == 0.25){
                
            }
            //left sensor
            tmpPos.y = ghostPos.y + 0;
            tmpPos.x = ghostPos.x - ghostSize.x;
            if (j.getGlobalBounds().intersects(sf::FloatRect(tmpPos,ghostSize)) && j.getScale().x == 0.25){
                
            }
        }
    }
    isRight = isLeft = isBottom = isTop = false;//"just stop and thinking"
    return outcome;
}
void Ghost::updateMovementsYesVisionPack(){

}
void Ghost::updateCorrectMovements(){
    int pos_x = sprite.getPosition().x;
    int pos_y = sprite.getPosition().y;
    int remain_y = pos_y%25;
    int remain_x = pos_x%25;
    
    //left-right direction
    if ((isRight || isLeft) && (!isTop) && (isFirst)){
        if (remain_y >= 12.5){
            pos_y += 25 - remain_y;
        }
        else{
            pos_y -= remain_y;
        }
        sprite.setPosition(pos_x,pos_y);
        isFirst=false;
    }
    //top-down direction
    if ((!isRight) && (isTop || isBottom) && (isFirst)){
        if (remain_x >= 12.5){
            pos_x += 25 - remain_x;
        }
        else{
            pos_x -= remain_x;
        }
        sprite.setPosition(pos_x,pos_y);
        isFirst=false;
    }
    
}
void Ghost::updateVisionPack(sf::Sprite &pack){
    if (vision->getGlobalBounds().intersects(pack.getGlobalBounds())){
        packPos.x = pack.getPosition().x;
        packPos.y = pack.getPosition().y;
        if (packPos.y < sprite.getGlobalBounds().top){//If  pack on the top
            wherePack[0] = true;
        }
        else if (packPos.y > sprite.getGlobalBounds().top +sprite.getGlobalBounds().height){//If  pack on the bottom
            wherePack[1] = true;
        }
        if (packPos.x < sprite.getGlobalBounds().left){//if pack on the left
            wherePack[2] = true;
        }
        else if (packPos.x > sprite.getGlobalBounds().left + sprite.getGlobalBounds().width){//if pack on the right
            wherePack[3] = true;
        }
    }
    else {
        for (int i = 0 ; i != 4 ; ++i)
            wherePack[i] = false;    
    }
    
}
void Ghost::updateChangingMovements(){
    if (isRight){
        dir_y = 0;
        dir_x = 0.7;
    }
    else if (isLeft){
        dir_y = 0;
        dir_x = -0.7;
    }
    if (isTop){
        dir_y = -0.7;
        dir_x = 0;
    }
    else if (isBottom){
        dir_y = 0.7;
        dir_x = 0;
    }
}