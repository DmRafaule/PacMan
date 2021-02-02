#include "pack.hpp"


Hero_pack::Hero_pack(){
    texture.loadFromFile("../texture/pacman.png");
    pack.setTexture(texture);
    pack.setPosition(sf::Vector2f(400.f,300.f));
    pack.setScale(0.1f,0.1f);

}

void Hero_pack::_render(sf::RenderTarget *window){
    window->draw(pack);
}
void Hero_pack::_update(sf::Event &event, sf::RenderTarget &window){
    movements(event);
    collisions(event, window);
}


void Hero_pack::movements(sf::Event &event){
    pack.move(dir_x,dir_y);
    if (event.type == sf::Event::KeyPressed)
        ch_movements(event);
}
void Hero_pack::ch_movements(sf::Event &event){
    if (event.type == sf::Event::KeyPressed){
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
        correct_movements(dir_x,dir_y);
    }
    else{
        //for animation in static
    }
}
void Hero_pack::correct_movements(float &dir_x, float &dir_y){
    
    int pos_x = pack.getPosition().x;
    int pos_y = pack.getPosition().y;
    int remain_y = pos_y%50;
    int remain_x = pos_x%50;
    
    //left-right direction
    if ((dir_x == 1 || dir_x == -1) && (dir_y == 0 )){
        if (remain_y >= 25){
            pos_y += 50 - remain_y;
        }
        else{
            pos_y -= remain_y;
        }
        pack.setPosition(pos_x,pos_y);
    }
    //top-down direction
    if ((dir_x == 0) && (dir_y == -1 || dir_y == 1 )){
        if (remain_x >= 25){
            pos_x += 50 - remain_x;
        }
        else{
            pos_x -= remain_x;
        }
        pack.setPosition(pos_x,pos_y);
    }
}
void Hero_pack::collisions(sf::Event &event, sf::RenderTarget &window){
/*left*/ if(pack.getGlobalBounds().left <= 0) 
            pack.setPosition(0.f, pack.getGlobalBounds().top);
/*right*/else if(pack.getGlobalBounds().left + pack.getGlobalBounds().width >= window.getSize().x)
            pack.setPosition(window.getSize().x - pack.getGlobalBounds().width, pack.getGlobalBounds().top);
/*top*/  if(pack.getGlobalBounds().top <= 0) 
            pack.setPosition(pack.getGlobalBounds().left, 0.f);
/*botom*/else if(pack.getGlobalBounds().top + pack.getGlobalBounds().height >= window.getSize().y)
            pack.setPosition(pack.getGlobalBounds().left, window.getSize().y - pack.getGlobalBounds().height);
}
