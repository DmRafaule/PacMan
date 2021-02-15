#include "pack.hpp"
#include <sstream>

Hero_pack::Hero_pack(){
    texture.loadFromFile("../texture/pacman.png");
    pack.setTexture(texture);
    pack.setPosition(sf::Vector2f(350.f,300.f));
    pack.scale(0.5,0.5);

    healthBar = new char[sizeHealthBar];//init health
    for (int i =0; i != sizeHealthBar; ++i){
        healthBar[i]='*';
    }
}
Hero_pack::~Hero_pack(){
    delete[] healthBar;
}
void Hero_pack::initStatus_Bar(sf::Event &event){
    if (event.key.code == sf::Keyboard::Tab && !isBar) {//allocate memory for status bar
        //Window stuff
        isBar=true;
        texture_bar = new sf::Texture();
        texture_bar->loadFromFile("../texture/status_bar.png");
        sprite_bar = new sf::Sprite(*texture_bar);
        //Text stuff
        font = new sf::Font();
        font->loadFromFile("../fonts/CodenameCoderFree4FBold.ttf");
        textHealth = new sf::Text(); 
        textScore = new sf::Text(); 
        textScore->setFont(*font);
        textHealth->setFont(*font);

        textScore->setCharacterSize(30);
        textHealth->setCharacterSize(50);
        textHealth->setFillColor(sf::Color::Red);

    }
    if (event.key.code == sf::Keyboard::Q && isBar){//free memory for status bar
        isBar = false;
        delete texture_bar;
        delete sprite_bar;
        delete font;
        delete textScore;
        delete textHealth;
    }
}

void Hero_pack::_render(sf::RenderTarget *window){
    window->draw(pack);
    if (isBar){
        window->draw(*sprite_bar);
        window->draw(*textScore);
        window->draw(*textHealth);
    }
}
void Hero_pack::_update(sf::Event &event, sf::RenderTarget &window,std::vector<std::vector<sf::Sprite>> &tiles, Ghost &ghost){
    updateTiles(tiles);
    updateCollisions(window,ghost);
    updateMovements(event);
    initStatus_Bar(event);
    if (isBar)
        updateStatus_Bar(window);
}

void Hero_pack::updateTiles(std::vector<std::vector<sf::Sprite>> &tiles){
    this->tiles = &tiles;
}
void Hero_pack::updateStatus_Bar(sf::RenderTarget &window){
    std::stringstream ss;
    ss << "Score: " << score << "\t\t\t\t\tHealth: ";
    textScore->setString(ss.str());
    ss.str("");//Clear stream
    ss << healthBar;
    textHealth->setString(ss.str());

    if (pack.getPosition().y >= window.getSize().y/2){//If pack on the top of window, display status bar on bottom
        sprite_bar->setPosition(window.getSize().x/2 - sprite_bar->getGlobalBounds().width/2,0);
    }
    else{  //else display on top
        sprite_bar->setPosition(window.getSize().x/2 - sprite_bar->getGlobalBounds().width/2,
                                window.getSize().y - sprite_bar->getGlobalBounds().height);
    }
    textScore->setPosition(sprite_bar->getPosition().x + 20, sprite_bar->getPosition().y + 20);
    textHealth->setPosition(sprite_bar->getPosition().x + sprite_bar->getGlobalBounds().width - textHealth->getGlobalBounds().width -30,
                            sprite_bar->getPosition().y + 7);



}


void Hero_pack::updateMovements(sf::Event &event){
    if (event.type == sf::Event::KeyPressed)
        ch_movements(event);
    pack.move(dir_x,dir_y);
}
void Hero_pack::ch_movements(sf::Event &event){
    if (event.type == sf::Event::KeyPressed && !isWall){
        //for animation in move
        if (event.key.code == sf::Keyboard::Left){
            dir_x = -1;
            dir_y = 0;
        }
        else if (event.key.code == sf::Keyboard::Right){
            dir_x = 1;
            dir_y = 0;
        }    
        if (event.key.code == sf::Keyboard::Up){
            dir_y = -1;
            dir_x = 0;
        }
        else if (event.key.code == sf::Keyboard::Down){
            dir_y = 1;
            dir_x = 0;
        }
        isWall=true;
        correct_movements(dir_x,dir_y);
    }
    else{
        isWall=false;
        //for animation in static
    }
}
void Hero_pack::correct_movements(float &dir_x, float &dir_y){
    
    int pos_x = pack.getPosition().x;
    int pos_y = pack.getPosition().y;
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
        pack.setPosition(pos_x,pos_y);
    }
    //top-down direction
    if ((dir_x == 0) && (dir_y == -1 || dir_y == 1 )){
        if (remain_x >= 12.5){
            pos_x += 25 - remain_x;
        }
        else{
            pos_x -= remain_x;
        }
        pack.setPosition(pos_x,pos_y);
    }
}


void Hero_pack::updateCollisions(sf::RenderTarget &window, Ghost &ghost){
    collisionWallsPoint(window);
    collisionBorders(window);
    collisionGhost(ghost);
}
void Hero_pack::collisionBorders(sf::RenderTarget &window){
/*left*/ if(pack.getGlobalBounds().left < 0) 
            dir_x = 1;
/*right*/else if(pack.getGlobalBounds().left + pack.getGlobalBounds().width > window.getSize().x)
            dir_x = -1;
/*top*/  if(pack.getGlobalBounds().top < 0) 
            dir_y = 1;
/*botom*/else if(pack.getGlobalBounds().top + pack.getGlobalBounds().height > window.getSize().y)
            dir_y = -1;
}
void Hero_pack::collisionWallsPoint(sf::RenderTarget &window){
    for (auto &map : *tiles){
        for (long unsigned int j = 0; j < map.size(); ++j){
            if ((pack.getGlobalBounds().intersects(map[j].getGlobalBounds())) && (map[j].getScale().x == 0.25)){
                if (dir_y == 1) dir_y = -1;
                else if (dir_y == -1) dir_y = 1;
                if (dir_x == 1) dir_x = -1;
                else if (dir_x == -1) dir_x = 1;
                isWall=true;
            }
            if ((pack.getGlobalBounds().intersects(map[j].getGlobalBounds())) &&
                (map[j].getScale().x >= 0.05) &&
                (map[j].getScale().x <= 0.15)){
                if (dir_x == 1 && pack.getPosition().x+5 >= map[j].getPosition().x){
                    map.erase(map.begin()+j);
                    score++;
                }
                else if (dir_x == -1 && pack.getPosition().x+5 <= map[j].getPosition().x){
                    map.erase(map.begin()+j);
                    score++;
                }
                if (dir_y == 1 && pack.getPosition().y+5 >= map[j].getPosition().y){
                    map.erase(map.begin()+j);
                    score++;
                }
                else if (dir_y == -1 && pack.getPosition().y+5 <= map[j].getPosition().y){
                    map.erase(map.begin()+j);
                    score++;
                }
                /*Why not here?? Because score too fast growing*/
            }
        }
    }
    
}
void Hero_pack::collisionGhost(Ghost &ghost){
    if (pack.getGlobalBounds().intersects(ghost._getGhostSprite().getGlobalBounds()) && !isGhost){//Here it's ok MAKE  a global timer in Engine
        std::cout << "It's ghost\n";
        isGhost=true;
    }
}

/*Getters*/
sf::Sprite &Hero_pack::_getPack(){
    return pack;
}
