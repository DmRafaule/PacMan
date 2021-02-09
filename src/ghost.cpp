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
    sprite.setColor(sf::Color(rand()%250+0,rand()%250+0,rand()%250+0,rand()%100+150));
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
    vision(pack);
    sprite.move(sf::Vector2f(dir_x,dir_y));
    ch_movements();
}
void Ghost::ch_movements(){
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

    correct_movements(dir_x,dir_y);
}
void Ghost::correct_movements(float &dir_x, float &dir_y){
    int pos_x = sprite.getPosition().x;
    int pos_y = sprite.getPosition().y;
    int remain_y = pos_y%50;
    int remain_x = pos_x%50;
    
    //left-right direction
    if ((dir_x == 0.7 || dir_x == -0.7) && (dir_y == 0 )){
        if (remain_y >= 25){
            pos_y += 50 - remain_y;
        }
        else{
            pos_y -= remain_y;
        }
        sprite.setPosition(pos_x,pos_y);
    }
    //top-down direction
    if ((dir_x == 0) && (dir_y == -0.7 || dir_y == 0.7 )){
        if (remain_x >= 25){
            pos_x += 50 - remain_x;
        }
        else{
            pos_x -= remain_x;
        }
        sprite.setPosition(pos_x,pos_y);
    }
}
void Ghost::vision(sf::Sprite &pack){
    if (eyes[0].getGlobalBounds().intersects(pack.getGlobalBounds())){
        isRight=true;
        isLeft=false;
        isTop=false;
        isBottom=false;
    }
    if (eyes[1].getGlobalBounds().intersects(pack.getGlobalBounds())){
        isRight=false;
        isLeft=false;
        isTop=false;
        isBottom=true;
    }
    if (eyes[2].getGlobalBounds().intersects(pack.getGlobalBounds())){
        isRight=false;
        isLeft=true;
        isTop=false;
        isBottom=false;
    }
    if (eyes[3].getGlobalBounds().intersects(pack.getGlobalBounds())){
        isRight=false;
        isLeft=false;
        isTop=true;
        isBottom=false;
    }
}
