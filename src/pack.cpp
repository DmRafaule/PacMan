#include "pack.hpp"
#include <sstream>

Hero_pack::Hero_pack(){
    /*INit pack texture*/
    texture     = new sf::Texture;
    texture->loadFromFile("../texture/pacman.png");
    
    pack        = new sf::Sprite(*texture);
    pack->setPosition(sf::Vector2f(350.f,300.f));
    pack->setTextureRect(sf::IntRect(0,0,50,50));
    pack->scale(0.5,0.5);

    /*Init pack health*/
    healthBar = new char[sizeHealthBar];//init health
    for (int i =0; i != sizeHealthBar; ++i){
        healthBar[i]='*';
    }

    /*Init time for pack*/
    clock       = new sf::Clock();
    localTime   = new sf::Time();
    /*Init sound effect for pack*/
    audio       = new Audio(10);
    audio->loadSound("../audio/eating.ogg");
}
Hero_pack::~Hero_pack(){
    delete      pack;
    delete      texture;
    delete[]    healthBar;
    delete      clock;
    delete      localTime;
    delete      audio;
}
void Hero_pack::initStatus_Bar(sf::Event &event){
    if (event.key.code == sf::Keyboard::Tab && !isBar) {//allocate memory for status bar
        //Window stuff
        isBar=true;
        texture_bar     = new sf::Texture();
        texture_bar->loadFromFile("../texture/status_bar.png");
        sprite_bar      = new sf::Sprite(*texture_bar);
        //Text stuff
        font            = new sf::Font();
        font->loadFromFile("../fonts/CodenameCoderFree4FBold.ttf");
        
        textScore       = new sf::Text(); 
        textScore->setFont(*font);
        textScore->setCharacterSize(30);

        textHealth      = new sf::Text(); 
        textHealth->setFont(*font);
        textHealth->setCharacterSize(45);
        textHealth->setFillColor(sf::Color::Red);

    }
    if (event.key.code == sf::Keyboard::Q && isBar){//free memory for status bar
        isBar   = false;
        delete  texture_bar;
        delete  sprite_bar;
        delete  font;
        delete  textScore;
        delete  textHealth;
    }
}

void Hero_pack::_render(sf::RenderTarget *window){
    window->draw(*pack);
    if (isBar){
        window->draw(*sprite_bar);
        window->draw(*textScore);
        window->draw(*textHealth);
    }
}
void Hero_pack::_update(sf::Event &event, sf::RenderTarget &window,std::vector<std::vector<sf::Sprite>> &tiles, Ghost &ghost, sf::Time &globalTime, short& isEndGame){
    updateTiles(tiles);
    updateMovements(event);
    updateCollisions(window,ghost);
    updateAnimation();
    updateTime();
    isEndGame = updateEndGame();
    initStatus_Bar(event);
    if (isBar)
        updateStatus_Bar(window,globalTime);
}

void Hero_pack::updateTiles(std::vector<std::vector<sf::Sprite>> &tiles){
    this->tiles = &tiles;
}
void Hero_pack::updateStatus_Bar(sf::RenderTarget &window, sf::Time &globalTime){
    std::stringstream ss;
    /*Player score and game time*/
    ss << "\nScore: " << score << "\nTime: " << static_cast<int>(globalTime.asSeconds());
    textScore->setString(ss.str());
    /*Player lives*/
    ss.str("");//Clear stream
    for (int i = 0; i != sizeHealthBar ; ++i){
        ss << healthBar[i];
    }
    textHealth->setString(ss.str());

    if (pack->getPosition().y >= window.getSize().y/2-100){//If pack on the top of window, display status bar on bottom
        sprite_bar->setPosition(window.getSize().x/2 - sprite_bar->getGlobalBounds().width/2,0);
    }
    else{                                                 //else display on top
        sprite_bar->setPosition(window.getSize().x/2 - sprite_bar->getGlobalBounds().width/2,
                                window.getSize().y - sprite_bar->getGlobalBounds().height);
    }
    
    textScore->setPosition(sprite_bar->getPosition().x + 10, sprite_bar->getPosition().y + 20);
    textHealth->setPosition(sprite_bar->getPosition().x + sprite_bar->getGlobalBounds().width - textHealth->getGlobalBounds().width -17,
                            sprite_bar->getPosition().y + 7);
}
void Hero_pack::updateTime(){
    *localTime = clock->restart();
    timer += localTime->asSeconds();
}
short Hero_pack::updateEndGame(){
    //For bad end
    if (sizeHealthBar == 0)
        return 1; 
    //For good end
    else if (score >= 600)
        return 2;
    //For not end
    return 0;
}
void Hero_pack::updateAnimation(){
    frame+=0.06;
    if (frame < 4){ 
        if      (dir_x == -1)   pack->setTextureRect(sf::IntRect(50*static_cast<int>(frame),47,50,50));   //Animation for leftward
        else if (dir_x ==  1)    pack->setTextureRect(sf::IntRect(50*static_cast<int>(frame),95,50,50));  //Animation for rightward
        if      (dir_y == -1)   pack->setTextureRect(sf::IntRect(50*static_cast<int>(frame),193,50,50));  //Animation for upward
        else if (dir_y ==  1)    pack->setTextureRect(sf::IntRect(50*static_cast<int>(frame),143,50,50)); //Animation for downward
    }
    else frame = 0;
}

void Hero_pack::updateMovements(sf::Event &event){
    if (event.type == sf::Event::KeyPressed)
        updateCh_movements(event);
    if (localTime->asSeconds()*150 < 2){//This is for save long jump
        pack->move(static_cast<int>(dir_x*localTime->asSeconds()*150),
                   static_cast<int>(dir_y*localTime->asSeconds()*150));//Make dependense from time
    }
}
void Hero_pack::updateCh_movements(sf::Event &event){
    if (event.type == sf::Event::KeyPressed && !isWall){
        if (event.key.code == sf::Keyboard::Left){
            dir_x = -1 ;
            dir_y = 0;
        }
        if (event.key.code == sf::Keyboard::Right){
            dir_x = 1;
            dir_y = 0;
        }    
        if (event.key.code == sf::Keyboard::Up){
            dir_y = -1;
            dir_x = 0;
        }
        if (event.key.code == sf::Keyboard::Down){
            dir_y = 1;
            dir_x = 0;
        }
        isWall=true;
        updateCorrect_movements(dir_x,dir_y);
    }
    else{
        isWall=false;
    }
}
void Hero_pack::updateCorrect_movements(float &dir_x, float &dir_y){
    
    int pos_x = pack->getPosition().x;
    int pos_y = pack->getPosition().y;
    int remain_y = pos_y%25;
    int remain_x = pos_x%25;
    
    //left-right direction
    if ((dir_x == 1 || dir_x == -1) && (dir_y == 0 )){
        if (remain_y >= 12.5){
            pos_y += 25 - remain_y;
        }
        else{
            pos_y -= remain_y;
        }
        pack->setPosition(pos_x,pos_y);
    }
    //top-down direction
    if ((dir_x == 0) && (dir_y == -1 || dir_y == 1 )){
        if (remain_x >= 12.5){
            pos_x += 25 - remain_x;
        }
        else{
            pos_x -= remain_x;
        }
        pack->setPosition(pos_x,pos_y);
    }
}


void Hero_pack::updateCollisions(sf::RenderTarget &window, Ghost &ghost){
    updateCollisionWallsPoint(window);
    updateCollisionGhost(ghost);
}
void Hero_pack::updateCollisionWallsPoint(sf::RenderTarget &window){
    for (auto &map : *tiles){
        for (long unsigned int j = 0; j < map.size(); ++j){
            if ((pack->getGlobalBounds().intersects(map[j].getGlobalBounds())) && (map[j].getScale().x == 0.25)){
                if      (dir_y == 1)    dir_y = -1;
                else if (dir_y == -1)   dir_y = 1;
                if      (dir_x == 1)    dir_x = -1;
                else if (dir_x == -1)   dir_x = 1;
            }
            if ((pack->getGlobalBounds().intersects(map[j].getGlobalBounds())) &&
                (map[j].getScale().x >= 0.05) &&
                (map[j].getScale().x <= 0.15)){
                if      (dir_x == 1 && pack->getPosition().x+5 >= map[j].getPosition().x){
                    map.erase(map.begin()+j);
                    audio->loadSound("../audio/eating.ogg");
                    audio->playSound();
                    score++;
                }
                else if (dir_x == -1 && pack->getPosition().x+5 <= map[j].getPosition().x){
                    map.erase(map.begin()+j);
                    audio->loadSound("../audio/eating.ogg");
                    audio->playSound();
                    score++;
                }
                if      (dir_y == 1 && pack->getPosition().y+5 >= map[j].getPosition().y){
                    map.erase(map.begin()+j);
                    audio->loadSound("../audio/eating.ogg");
                    audio->playSound();
                    score++;
                }
                else if (dir_y == -1 && pack->getPosition().y+5 <= map[j].getPosition().y){
                    map.erase(map.begin()+j);
                    audio->loadSound("../audio/eating.ogg");
                    audio->playSound();
                    score++;
                }
                
                if (map[j].getTextureRect().left == 500){//Collisions with health point
                        audio->loadSound("../audio/eatpill.ogg");
                        audio->playSound();
                        if (sizeHealthBar < 6) 
                            sizeHealthBar++;
                }
                if (map[j].getTextureRect().left == 1000){//In this case multihit so you will get much more then 1
                    audio->loadSound("../audio/eatpill.ogg");
                    audio->playSound();
                    score+=1;
                }
            }           
        }
    }   
}
void Hero_pack::updateCollisionGhost(Ghost &ghost){
    for (int i = 0; i != 4 ; ++i){
        if (pack->getGlobalBounds().intersects((&ghost + i)->_getGhostSprite().getGlobalBounds()) && !isGhost && static_cast<int>(timer) > 3){
            timer = 0;
            isGhost=true;
            sizeHealthBar--;
            audio->stopSound();
            audio->loadSound("../audio/damage.wav");
            audio->playSound();
        }
        if (isGhost){
            isGhost=false;
        }
    }
}

/*Getters*/
sf::Sprite &Hero_pack::_getPack(){
    return *pack;
}
