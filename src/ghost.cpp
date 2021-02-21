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
        fixPos=true;
        //isFirst=true;
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
    if (isWall){
    std::cout << "it is wall"<< std::endl;
    std::cout << "options = "<<option<<std::endl;
    std::cout << "outcome = "<<outcome<<std::endl<<std::endl<<std::endl;
    std::cout << "l sensor = "<<isLeft<<std::endl;
    std::cout << "r sensor = "<<isRight<<std::endl;
    std::cout << "t sensor = "<<isTop<<std::endl;
    std::cout << "b sensor = "<<isBottom<<std::endl;

    }
}
bool Ghost::updateCollisionWalls(sf::RenderTarget &win){
    for (const auto &i : *tiles)
        for (const auto &j : i)
            if ((sprite.getGlobalBounds().intersects(j.getGlobalBounds())) && j.getScale().x == 0.25 && isFirst ){
                isFirst=false;
                return true;
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
    //INIT SENSORS FOR DETECT FREE DIRECTIONS(NEW F-TION)
    int options = 4;
    sf::FloatRect sens[4];//Declare our sensor for detecting surrounding
    for (auto &i : sens){
        i.height = 20;
        i.width = 20;
    }
    //Top sensor
    sens[0].left = sprite.getPosition().x + 2;
    sens[0].top = sprite.getPosition().y - sens[0].height;
    //Bottom sensor
    sens[1].left = sprite.getPosition().x + 2;
    sens[1].top = sprite.getPosition().y + sens[1].height * 1.25;
    //Right sensor
    sens[2].left = sprite.getPosition().x + sens[2].width * 1.25;
    sens[2].top = sprite.getPosition().y + 2;
    //Left sensor
    sens[3].left = sprite.getPosition().x - sens[3].width;
    sens[3].top = sprite.getPosition().y + 2;


    //DEFINE WHICH DIRECTION THEY COULD CHOOSE(NEW F-TION)
    if(isBottom) outcome=1;
    if(isTop)  outcome=2;
    if(isLeft) outcome=3;
    if(isRight) outcome=0;

    isLeft=isRight=isBottom=isTop=true;// We suppose that ghost can move to any directions
    for (const auto &i : *tiles){
        for (const auto &j : i){
            if (sens[0].intersects(j.getGlobalBounds()) && j.getScale().x == 0.25){
                isTop=false;
                options--;
            }
            if (sens[1].intersects(j.getGlobalBounds()) && j.getScale().x == 0.25){
                isBottom=false;
                options--;
            }
            if (sens[2].intersects(j.getGlobalBounds()) && j.getScale().x == 0.25){
                isRight=false;
                options--;
            }
            if (sens[3].intersects(j.getGlobalBounds()) && j.getScale().x == 0.25){
                isLeft=false;
                options--;
            }
        }
    }


    //DEFINE WHICH DIRECTION THEY WILL CHOOSE(NEW F-TION)
    switch (options){
        case 1:{
            if (isLeft) outcome=0;
            if (isRight) outcome=3;
            if (isTop) outcome=1;
            if (isBottom) outcome=2;
            isLeft=isRight=isBottom=isTop=false; 
            break;
        }
        case 2:{
            if (!isTop && !isRight  && outcome == 0){
                outcome = 2;
            }
            else if (!isTop && !isRight  && outcome == 2){
                outcome = 0;
            }


            if (!isBottom && !isRight && outcome == 0){ 
                outcome = 1;
            }
            else if (!isBottom && !isRight && outcome == 1){ 
                outcome = 0;
            }


            if (!isBottom && !isLeft && outcome == 1){ 
                outcome = 3;
            }
            else if (!isBottom && !isLeft && outcome == 3){ 
                outcome = 1;
            }


            if (!isTop && !isLeft && outcome == 2){
                outcome = 3;
            }
            else if (!isTop && !isLeft && outcome == 3){
                outcome = 2;
            }

            isLeft=isRight=isBottom=isTop=false; 
            break;
        }
        case 3:{
            int rand_num = rand()%2;
            if (!isTop){
                if (rand_num == 0) outcome = 0;
                else outcome = 3;
            }
            else if (!isBottom){ 
                if (rand_num == 0) outcome = 0;
                else outcome = 3;
            }
            if (!isLeft){ 
                if (rand_num == 0) outcome = 1;
                else outcome = 2;
            }
            else if (!isRight){ 
                if (rand_num == 0) outcome = 1;
                else outcome = 2;
            }
            isLeft=isRight=isBottom=isTop=false; 
            break;
        }
    }
    option=options;//DEL


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
    if ((isRight || isLeft) && (!isTop) && (fixPos)){
        if (remain_y >= 12.5){
            pos_y += 25 - remain_y;
        }
        else{
            pos_y -= remain_y;
        }
        sprite.setPosition(pos_x,pos_y);
        fixPos=false;
    }
    //top-down direction
    if ((!isRight) && (isTop || isBottom) && (fixPos)){
        if (remain_x >= 12.5){
            pos_x += 25 - remain_x;
        }
        else{
            pos_x -= remain_x;
        }
        sprite.setPosition(pos_x,pos_y);
        fixPos=false;
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