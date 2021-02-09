#include "ghost.hpp"
#include <iostream>

Ghost::Ghost(){
    initTexture();
    initEyes();
}
Ghost::~Ghost(){
    delete[] eyes;
}

/*update f-tion*/
void Ghost::updateEyes(){
    for (int i = 0; i != 4 ; ++i){
        eyes[i].setPosition(sprite.getGlobalBounds().left + texture.getSize().x/2,
                            sprite.getGlobalBounds().top + texture.getSize().y/2);
    }
}
void Ghost::updateTiles(std::vector<std::vector<sf::Sprite>> &tiles){
    this->tiles = &tiles;
}
void Ghost::__update(sf::RenderTarget &win,std::vector<std::vector<sf::Sprite>> &tiles, sf::Sprite &pack){
    updateTiles(tiles);
    updateEyes();
    collisions(win);
    movements(pack);
    this->win = &win;
}
/*Render f-tion*/
void Ghost::__render(sf::RenderTarget &win){
    win.draw(sprite);
    for (int i = 0; i != 4 ; ++i){
        win.draw(eyes[i]);
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
    sprite.scale(0.5,0.5);
}
void Ghost::setPos(float x, float y){
    sprite.setPosition(x,y);
    for (int i = 0; i != 4 ; ++i){
        eyes[i].setPosition(x,y);        
    }
}
void Ghost::initEyes(){
    eyes = new sf::RectangleShape[4];
    for (int i = 0; i != 4 ; ++i){
        eyes[i].setSize(sf::Vector2f(150.f, 5.f));
        eyes[i].setFillColor(sf::Color::Red);      
        eyes[i].rotate(i*90);
    }
}

/*about collisions*/
void Ghost::collisions(sf::RenderTarget &win){
    collisionBorders(win);
    collisionWalls(win);
}
void Ghost::showStat(){
    system("clear");
    std::cout << "isRight = " <<this->isRight<<std::endl;
    std::cout << "isLeft = " <<this->isLeft<<std::endl;
    std::cout << "isTop = " <<this->isTop<<std::endl;
    std::cout << "isBottom = " <<this->isBottom<<std::endl;
    std::cout << "dir_x = " <<this->dir_x<<std::endl;
    std::cout << "dir_y = " <<this->dir_y<<std::endl;
    std::cout << "pos_x = " <<this->sprite.getPosition().x<<std::endl;
    std::cout << "pos_y = " <<this->sprite.getPosition().y<<std::endl;
}
void Ghost::collisionBorders(sf::RenderTarget &win){
/*left*/if(sprite.getGlobalBounds().left < 0){
            isLeft=false;
            isRight=true;
        }
/*right*/else if(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width > win.getSize().x){
            isLeft=true;
            isRight=false;
        }
/*top*/ if(sprite.getGlobalBounds().top < 0){
            isBottom=true;
            isTop=false;
        }
/*botom*/else if(sprite.getGlobalBounds().top + sprite.getGlobalBounds().height > win.getSize().y){
            isBottom=false;
            isTop=true;
        }
}
void Ghost::collisionWalls(sf::RenderTarget &win){
    for (const auto &i : *tiles){
        for (const auto &j : i){
            if (sprite.getGlobalBounds().intersects(j.getGlobalBounds())){
                if (isRight || isLeft){
                    if (isRight) {
                        dir_x=-0.7;
                        dir_y=0;
                        isLeft=true;
                        isRight=false;
                   }
                    else if(!isRight) {
                        dir_x=0.7;
                        dir_y=0;
                        isLeft=false;
                        isRight=true;
                   }
                }
                else{
                        if (isTop){
                        dir_x=0;
                        dir_y=0.7;
                        isTop=false;
                        isBottom=true;
                    }
                    else if (!isTop){
                        dir_x=0;
                        dir_y=-0.7;
                        isTop=true;
                        isBottom=false;
                    }
                }
                
            }
        }
    }
}

/*about movements*/
void Ghost::movements(sf::Sprite &pack){
    ch_movements(pack);
    vision(pack);
    sprite.move(sf::Vector2f(dir_x,dir_y));
}
void Ghost::ch_movements(sf::Sprite &pack){
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
void Ghost::vision(sf::Sprite &pack){
    if (eyes[0].getGlobalBounds().intersects(pack.getGlobalBounds())){
        correct_movements();
        isRight=true;
        isLeft=false;
        isTop=false;
        isBottom=false;
    }
    else if (eyes[1].getGlobalBounds().intersects(pack.getGlobalBounds())){
        correct_movements();
        isRight=false;
        isLeft=false;
        isTop=false;
        isBottom=true;
    }
    else if (eyes[2].getGlobalBounds().intersects(pack.getGlobalBounds())){
        correct_movements();
        isRight=false;
        isLeft=true;
        isTop=false;
        isBottom=false;
    }
    else if (eyes[3].getGlobalBounds().intersects(pack.getGlobalBounds())){
        correct_movements();
        isRight=false;
        isLeft=false;
        isTop=true;
        isBottom=false;
    }
    else{
        isFirst=true;
    }
}
void Ghost::correct_movements(){
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