#include "pack.hpp"


Hero_pack::Hero_pack(){
    texture.loadFromFile("../texture/pacman.png");
    pack.setTexture(texture);
    pack.setPosition(sf::Vector2f(350.f,300.f));
    pack.scale(0.5,0.5);
}

void Hero_pack::_render(sf::RenderTarget *window){
    window->draw(pack);
}
void Hero_pack::_update(sf::Event &event, sf::RenderTarget &window,std::vector<std::vector<sf::Sprite>> &tiles){
    updateTiles(tiles);
    collisions(event, window);
    movements(event);
}

void Hero_pack::updateTiles(std::vector<std::vector<sf::Sprite>> &tiles){
    this->tiles = &tiles;
}

/*movements f-tion*/
void Hero_pack::movements(sf::Event &event){
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

/*collisions f-tions*/
void Hero_pack::collisions(sf::Event &event, sf::RenderTarget &window){
    collisionWallsPoint(window);
    collisionBorders(window);
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
                if (dir_x == 1 && pack.getPosition().x+5 >= map[j].getPosition().x) map.erase(map.begin()+j);
                else if (dir_x == -1 && pack.getPosition().x+5 <= map[j].getPosition().x) map.erase(map.begin()+j);
                if (dir_y == 1 && pack.getPosition().y+5 >= map[j].getPosition().y) map.erase(map.begin()+j);
                else if (dir_y == -1 && pack.getPosition().y+5 <= map[j].getPosition().y) map.erase(map.begin()+j);
            }
        }
    }
    
}


sf::Sprite &Hero_pack::_getPack(){
    return pack;
}
