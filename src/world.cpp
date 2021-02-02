#include "world.hpp"
#include <iostream>

World::World(unsigned int winWidth, unsigned int winHeight){
    initVar(winWidth,winHeight);
    initTiles();
    initMap();
}
World::~World(){
    delete map;
}

/*Init f*/
void World::initVar(unsigned int winWidth, unsigned int winHeight){
    this->winHeight = winHeight;
    this->winWidth = winWidth;
}
void World::initTiles(){
    if (!textureMap.loadFromFile("../texture/mapTile.png"))
        std::cout << "error, header.cpp::game::initTiles, cann't load a texture " << std::endl;
    spriteMap.setTexture(textureMap);
    spriteMap.scale(sf::Vector2f(0.5,0.5));
}
void World::initMap(){
    map = new Map();

    tiles.clear();
    std::vector<sf::Sprite> row;
    for (size_t i = 0; i < winHeight/50; ++i){
        for (size_t j = 0; j < winWidth/50; ++j){
            if (map->get_map(i,j) == '#'){
                row.push_back(spriteMap);
            }
            spriteMap.setPosition(j*50,i*50);
        }
        tiles.push_back(row);
        row.clear();
    }
}

/*Update f*/
void World::_update(){

}

/*Render f*/
void World::_render(sf::RenderTarget &win){
    renderMap(win);
}
void World::renderMap(sf::RenderTarget &win){
    for (const auto &i : tiles){
        for (const auto &j : i){
            win.draw(j);
        }
    }
}

