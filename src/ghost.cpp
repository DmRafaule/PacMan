#include "ghost.hpp"
#include <iostream>

Ghost::Ghost(){
    initTexture();
    //initVision();
}
Ghost::~Ghost(){
    //delete vision;
}
sf::Sprite &Ghost::_getGhostSprite(){
    return sprite;
}
void Ghost::showStat(){
    if (isWall){
        system("clear");
        std::cout << "left \t\t" << l <<std::endl;
        std::cout << "right \t\t" << r <<std::endl;
        std::cout << "top \t\t" << t <<std::endl;
        std::cout << "bottom \t\t" << b <<std::endl<<std::endl;
        std::cout << "option \t\t" << option <<std::endl<<std::endl;
        std::cout << "outcome \t" << outcome <<std::endl;
    }
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
        clock.restart();
    }
}
void Ghost::__update(sf::RenderTarget &win,std::vector<std::vector<sf::Sprite>> &tiles, sf::Sprite &pack){
    updateTiles(tiles);
    //updateVision();
    updateTime();

    updateCollisions(win);
    updateMovements(pack);
    updateAnimation();
    
    this->win = &win;
}
/*Render f-tion*/
void Ghost::__render(sf::RenderTarget &win){
    win.draw(sprite);
    //for (int i = 0; i != 4 ; ++i){
    //    //win.draw(*vision);
    //}
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
    //vision->setPosition(x,y);        
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
    //updateVisionPack(pack);
    
    updateChangingMovements();
    sprite.move(sf::Vector2f(dir_x,dir_y));
}
void Ghost::updateMovementsNoVisionPack(sf::Sprite &pack){
    if (isWall){//HERE F-TION updateCollisionWalls
    //INSTEAD OF NUMBERS CREATE enum or unit...???
        isFirst=true;
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
    bool l_s = true,r_s = true,t_s = true,b_s = true;
    sf::FloatRect sens[4];//Declare our sensor for detecting surrounding
    for (auto &i : sens){
        i.height = 5;
        i.width = 5;
    }
    //Top sensor
    sens[0].left = sprite.getPosition().x + 10;
    sens[0].top = sprite.getPosition().y - sens[0].height;
    //Bottom sensor
    sens[1].left = sprite.getPosition().x + 10;
    sens[1].top = sprite.getPosition().y + sens[1].height * 5;
    //Right sensor
    sens[2].left = sprite.getPosition().x + sens[2].width * 5;
    sens[2].top = sprite.getPosition().y + 10;
    //Left sensor
    sens[3].left = sprite.getPosition().x - sens[3].width;
    sens[3].top = sprite.getPosition().y + 10;


    l=r=b=t=false;
    for (const auto &i : *tiles){
        for (const auto &j : i){
            if (sens[0].intersects(j.getGlobalBounds()) && j.getScale().x == 0.25){
                t=true;
                t_s=false;
                options--;
            }
            if (sens[1].intersects(j.getGlobalBounds()) && j.getScale().x == 0.25){
                b=true;
                b_s=false;
                options--;
            }
            if (sens[2].intersects(j.getGlobalBounds()) && j.getScale().x == 0.25){
                r=true;
                r_s=false;
                options--;
            }
            if (sens[3].intersects(j.getGlobalBounds()) && j.getScale().x == 0.25){
                l=true;
                l_s=false;
                options--;
            }
        }
    }
    option = options;
    //DEFINE WHICH DIRECTION THEY WILL CHOOSE(NEW F-TION)
                //sprite.setPosition(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top + 1);//Если верхний датчик
                //sprite.setPosition(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top - 1);//Если нижний датчик
                //sprite.setPosition(sprite.getGlobalBounds().left - 1, sprite.getGlobalBounds().top);//Если правый датчик
                //sprite.setPosition(sprite.getGlobalBounds().left + 1, sprite.getGlobalBounds().top);//Если левый датчик
    switch (options){
        case 1:{
            if (!l_s) outcome=3;
            if (!r_s) outcome=0;
            if (!t_s) outcome=2;
            if (!b_s) outcome=1;
            isLeft=isRight=isBottom=isTop=false; 
            break;
        }
        case 2:{
            if (!t_s && !r_s  && isRight){
                outcome = 2;
            }
            else if (!t_s && !r_s  && isTop){
                outcome = 0;
            }


            if (!b_s && !r_s && isRight){ 
                outcome = 1;
            }
            else if (!b_s && !r_s && isBottom){ 
                outcome = 0;
            }


            if (!b_s && !l_s && isBottom){ 
                outcome = 3;
            }
            else if (!b_s && !l_s && isLeft){ 
                outcome = 1;
            }


            if (!t_s && !l_s && isTop){
                outcome = 3;
            }
            else if (!t_s && !l_s && isLeft){
                outcome = 2;
            }
            isLeft=isRight=isBottom=isTop=false; 
            break;
        }
        case 3:{
            int rand_num = rand()%2;
            if (!t_s){
                if (rand_num == 0) outcome = 0;
                else outcome = 3;
            }
            else if (!b_s){ 
                if (rand_num == 0) outcome = 0;
                else outcome = 3;
            }
            if (!l_s){ 
                if (rand_num == 0) outcome = 1;
                else outcome = 2;
            }
            else if (!r_s){ 
                if (rand_num == 0) outcome = 1;
                else outcome = 2;
            }
            isLeft=isRight=isBottom=isTop=false; 
            break;
        }
    }
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