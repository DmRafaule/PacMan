#include "ghost.hpp"
#include <iostream>

Ghost::Ghost(){
    initTexture();
    initEyes();
}
Ghost::~Ghost(){
    delete[] eyes;
}
void Ghost::__update(sf::RenderTarget &win,std::vector<std::vector<sf::Sprite>> &tiles, sf::Sprite &pack){
    updateTiles(tiles);
    updateEyes();
    collisions(win);
    movements(pack);
}
void Ghost::__render(sf::RenderTarget &win){
    win.draw(sprite);
    for (int i = 0; i != 4 ; ++i){
        win.draw(eyes[i]);
    }
}
void Ghost::initTexture(){
    texture.loadFromFile("../texture/ghost.png");
    sprite.setTexture(texture);
    sprite.setColor(sf::Color(rand()%250+0,rand()%250+0,rand()%250+0,rand()%100+150));
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
void Ghost::collisionBorders(sf::RenderTarget &win){
/*left*/ if(sprite.getGlobalBounds().left < 0) 
            dir_x = 0;
/*right*/else if(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width > win.getSize().x)
            dir_x = 0;
/*top*/  if(sprite.getGlobalBounds().top < 0) 
            dir_y = 0;
/*botom*/else if(sprite.getGlobalBounds().top + sprite.getGlobalBounds().height > win.getSize().y)
            dir_y = 0;
}
void Ghost::collisionWalls(sf::RenderTarget &win){
    for (const auto &i : tiles){
        for (const auto &j : i){
            if (sprite.getGlobalBounds().intersects(j.getGlobalBounds())){
                dir_y = 0;
                dir_x = 0;
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
        dir_x = 0.9;
    }
    else if (isLeft){
        dir_y = 0;
        dir_x = -0.9;
    }
    if (isTop){
        dir_y = -0.9;
        dir_x = 0;
    }
    else if (isBottom){
        dir_y = 0.9;
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
    if ((dir_x == 0.9 || dir_x == -0.9) && (dir_y == 0 )){
        if (remain_y >= 25){
            pos_y += 50 - remain_y;
        }
        else{
            pos_y -= remain_y;
        }
        sprite.setPosition(pos_x,pos_y);
    }
    //top-down direction
    if ((dir_x == 0) && (dir_y == -0.9 || dir_y == 0.9 )){
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
    
}

void Ghost::updateEyes(){
    for (int i = 0; i != 4 ; ++i){
        eyes[i].setPosition(sprite.getGlobalBounds().left + texture.getSize().x/2,
                            sprite.getGlobalBounds().top + texture.getSize().y/2);
    }
}
void Ghost::updateTiles(std::vector<std::vector<sf::Sprite>> &tiles){
    this->tiles = tiles;
}