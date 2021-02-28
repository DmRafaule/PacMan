#include "world.hpp"
#include <iostream>

World::World(unsigned int winWidth, unsigned int winHeight, int optionMap){
    initVar(winWidth,winHeight);
    initTiles();
    initMap(optionMap);
    initGhost();
}
World::~World(){
    delete map;
    delete[] ghost;
}

/*Init f*/
void World::initVar(unsigned int winWidth, unsigned int winHeight){
    this->winHeight = winHeight;
    this->winWidth = winWidth;
}
void World::initTiles(){
    if (!textureMap.loadFromFile("../texture/mapTile.png"))
        std::cout << "error, header.cpp::game::initTiles, cann't load a texture " << std::endl;
    if (!textureP.loadFromFile("../texture/point.png")){
        std::cout << "error, header.cpp::game::initTiles, cann't load a texture " << std::endl;
    }
    spriteP.setTexture(textureP);
    spriteMap.setTexture(textureMap);
    spriteP.setScale(0.05,0.05);
    spriteMap.setScale(0.25,0.25);
}
void World::initMap(int optionMap){
    map = new Map(optionMap);

    tiles.clear();
    std::vector<sf::Sprite> row;
    for (size_t i = 0; i < winHeight/25; ++i){
        for (size_t j = 0; j < winWidth/25; ++j){
            if (map->get_map(i,j) == '#'){//Just walls
                row.push_back(spriteMap);
            }
            if (map->get_map(i,j) == '_'){//Usual points
                spriteP.setTextureRect(sf::IntRect(0,0,500,500));
                row.push_back(spriteP);
            }
            if (map->get_map(i,j) == '*'){//Unusual points(just bigger)
                spriteP.setTextureRect(sf::IntRect(1000,0,500,500));
                row.push_back(spriteP);
            }
            if (map->get_map(i,j) == '+'){//health points
                spriteP.setTextureRect(sf::IntRect(500,0,500,500));
                row.push_back(spriteP);
            }
            spriteMap.setPosition(j*25,i*25);
            spriteP.setPosition(j*25,i*25);
        }
        tiles.push_back(row);
        row.clear();
    }
}
void World::initGhost(){
    ghost = new Ghost[4];

    ghost[0].setPos(25,25);
    ghost[1].setPos(675,50);
    ghost[2].setPos(725,550);
    ghost[3].setPos(25,550);
}

/*Update f*/
void World::_update(sf::RenderTarget &win, std::vector<std::vector<sf::Sprite>> &tiles, sf::Sprite &pack){
    updateMap();
    updateGhost(win,tiles,pack);
}
void World::updateGhost(sf::RenderTarget &win, std::vector<std::vector<sf::Sprite>> &tiles, sf::Sprite &pack){
    for (int i = 0; i != 4; ++i){
        ghost[i].__update(win,tiles,pack);
    }
    //ghost[0].showStat();//TEMP REMOVE 
}
void World::updateMap(){
    
}
/*Render f*/
void World::_render(sf::RenderTarget &win){
    renderMap(win);
    renderGhost(win);
}
void World::renderMap(sf::RenderTarget &win){
    for (auto &i : tiles){
        for (auto &j : i){
            win.draw(j);
        }
    }
}
void World::renderGhost(sf::RenderTarget &win){
    for (int i = 0; i != 4; ++i){
        ghost[i].__render();
    }
}
std::vector<std::vector<sf::Sprite>> &World::_getTiles(){
    return tiles;
}
Ghost &World::_getGhost(){
    return *ghost;
}